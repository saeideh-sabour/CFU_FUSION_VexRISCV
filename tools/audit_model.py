"""Read only the supplied tensor state_dict using a restricted decoder; no torch needed.
Run: python3 tools/audit_model.py /path/to/MNIST_CNN --out verification
This is a numerical reference audit, NOT hardware execution or cycle simulation.
"""
import argparse, ast, collections, hashlib, io, json, pickle, re, zipfile
from pathlib import Path
import numpy as np

class Tensor:
    def __init__(self,a,q=None): self.a,self.q=a,q

def rebuild(storage,offset,size,stride,*unused):
    return np.lib.stride_tricks.as_strided(storage[offset:],shape=size,strides=tuple(s*storage.itemsize for s in stride)).copy()
def rebuild_q(storage,offset,size,stride,q,*unused):
    return Tensor(rebuild(storage,offset,size,stride),q)
class Decoder(pickle.Unpickler):
    def __init__(self,z,key):
        self.z,self.root=z,key.rsplit('/',1)[0];super().__init__(io.BytesIO(z.read(key)))
    def find_class(self,module,name):
        allowed={('collections','OrderedDict'):collections.OrderedDict,
                 ('torch._utils','_rebuild_tensor_v2'):rebuild,
                 ('torch._utils','_rebuild_qtensor'):rebuild_q}
        if (module,name) in allowed:return allowed[module,name]
        if module=='torch' and name in ['FloatStorage','LongStorage','QInt8Storage','DoubleStorage','qint8','per_channel_affine']:
            return name
        raise ValueError(f'Unsupported pickle global {module}.{name}')
    def persistent_load(self,pid):
        tag,typ,key,location,count=pid
        assert tag=='storage'
        dtype={'FloatStorage':'<f4','LongStorage':'<i8','QInt8Storage':'i1','DoubleStorage':'<f8'}[typ]
        a=np.frombuffer(self.z.read(self.root+'/data/'+key),dtype=dtype)
        assert len(a)==count
        return a

def load_state(path):
    with zipfile.ZipFile(path) as z:
        key=next(k for k in z.namelist() if k.endswith('/data.pkl'))
        return Decoder(z,key).load()

def golden(text,title):
    section=text.split('\n'+title+'\n',1)[1]
    body=re.split(r',\s*dtype=',section.split('tensor(',1)[1],maxsplit=1)[0]
    return np.array(ast.literal_eval(body),dtype=np.int64)

def conv(x,w):
    x=np.pad(x,((0,0),(0,0),(1,1),(1,1)))
    windows=np.lib.stride_tricks.sliding_window_view(x,(3,3),axis=(2,3))
    return np.einsum('nchwij,ocij->nohw',windows,w,dtype=np.int64,optimize=True)

def pool(x):
    n,c,h,w=x.shape
    return x.reshape(n,c,h//2,2,w//2,2).max(axis=(3,5))

def main():
    ap=argparse.ArgumentParser();ap.add_argument('source',type=Path);ap.add_argument('--out',type=Path,default=Path('verification'));args=ap.parse_args()
    p=args.source;out=args.out;out.mkdir(parents=True,exist_ok=True)
    s=load_state(p/'mnist_cnn_int8.pth')
    logs=(p/'layer_outputs.txt').read_text()
    with (p/'mnist_test.csv').open() as f:
        next(f); rows=np.array([[int(t) for t in next(f).strip().split(',')] for _ in range(10)])
    sx=float(s['quant.scale'][0]);zx=int(s['quant.zero_point'][0])
    x=np.clip(np.rint((rows[:,1:].astype(np.float32)/255)/np.float32(sx))+zx,0,255).astype(np.int64).reshape(-1,1,28,28)
    arrays={'input':x};report={'kind':'NumPy reconstruction of supplied checkpoint; comparison against supplied logs','files':{},'checks':{},'layers':{}}
    for f in sorted(p.iterdir()):
        if f.is_file():report['files'][f.name]={'bytes':f.stat().st_size,'sha256':hashlib.sha256(f.read_bytes()).hexdigest()}
    def check(name,a,title):
        g=golden(logs,title); d=np.abs(a-g)
        report['checks'][name]={'shape':list(a.shape),'mismatches':int(np.count_nonzero(d)),'max_abs_error':int(d.max())}
    check('input',x,'Input after Quantization')
    exports={}
    for name in ['conv1','conv2','fc1','fc2']:
        wt=s[name+'.weight'] if name.startswith('conv') else s[name+'._packed_params._packed_params'][0]
        bias=s[name+'.bias'] if name.startswith('conv') else s[name+'._packed_params._packed_params'][1]
        assert bias is None
        _,sw,zw,axis=wt.q
        assert axis==0 and np.all(zw==0)
        sy=float(s[name+'.scale']);zy=int(s[name+'.zero_point'])
        m=sx*sw/sy
        w=wt.a.astype(np.int64)
        report['layers'][name]={'weight_shape':list(w.shape),'input_scale':sx,'input_zero_point':zx,'output_scale':sy,'output_zero_point':zy,'weight_zero_points':zw.tolist(),'multiplier':m.tolist(),'bias':None}
        exports[name+'_weights']=wt.a;exports[name+'_multiplier']=m
        # Match backend-style single-precision multiplier; this is an explicit candidate to verify.
        acc=conv(x-zx,w) if name.startswith('conv') else (x-zx)@w.T
        scale=m.astype(np.float32).reshape(1,-1,1,1) if name.startswith('conv') else m.astype(np.float32)
        y=np.clip(np.rint(acc.astype(np.float32)*scale)+zy,zy if name.startswith('conv') else 0,255).astype(np.int64)
        q31=np.rint(m*(1<<31)).astype(np.int64)
        qscale=q31.reshape(1,-1,1,1) if name.startswith('conv') else q31
        prod=acc*qscale; base=prod//(1<<31); rem=prod%(1<<31)
        rounded=base+((rem>(1<<30))|((rem==(1<<30))&((base&1)!=0)))
        fixed=np.clip(rounded+zy,zy if name.startswith('conv') else 0,255).astype(np.int64)
        report['layers'][name]['q31_local_mismatches']=int(np.count_nonzero(fixed!=y))
        exports[name+'_q31']=q31
        title={'conv1':'Output of Conv1','conv2':'Output of Conv2','fc1':'Output of FC1','fc2':'Output of FC2'}[name]
        check(name,y,title);arrays[name]=y.copy()
        if name.startswith('conv'):
            y=pool(y);check(name+'_pool',y,'Output of '+name.capitalize()+' + ReLU + MaxPool');arrays[name+'_pool']=y.copy()
        if name=='conv2':y=y.reshape(len(y),-1)
        if name=='fc1':
            y=np.maximum(y,zy);check('fc1_relu',y,'Output of FC1 + ReLU');arrays['fc1_relu']=y.copy()
        x,sx,zx=y,sy,zy
    report['labels']=rows[:,0].tolist();report['predictions']=x.argmax(axis=1).tolist()
    report['all_logged_elements_equal']=all(c['mismatches']==0 for c in report['checks'].values())
    # Compare the matrix export to checkpoint, in its documented noncanonical layout.
    for filename in ['weights_int8(bias_int8)_matrix_conv_sd.txt','weights_int8(bias_int8)_matrix_conv.txt']:
        text=(p/filename).read_text();matches={}
        for name in ['conv1','conv2','fc1','fc2']:
            match=re.search(r'int8_t\s+'+name.upper()+r'[^=]*=\s*\{(.*?)\};',text,re.S)
            if not match:continue
            got=np.array([int(v) for v in re.findall(r'-?\d+',match.group(1))])
            w=exports[name+'_weights'];expected=w.transpose(1,2,3,0).ravel() if name.startswith('conv') else w.T.ravel()
            matches[name]={'count':len(got),'mismatches':int(np.count_nonzero(got!=expected)) if got.shape==expected.shape else 'shape mismatch'}
        report[filename]=matches
    np.savez(out/'reference_arrays.npz',**arrays,**exports,labels=rows[:,0],pixels=rows[:,1:])
    (out/'audit.json').write_text(json.dumps(report,indent=2))
    print(json.dumps({k:v for k,v in report.items() if k not in ['files','layers']},indent=2))
if __name__=='__main__':main()
