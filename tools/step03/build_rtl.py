from pathlib import Path
p=Path(__file__).resolve().parents[2]/'rtl/step03'
names=['mac4.v','requant_q31.v','pool2x2_stream.v','cfu_top.v']
(p/'cfu.v').write_text('// Generated from '+', '.join(names)+'\n'+'\n'.join((p/n).read_text() for n in names))
print(p/'cfu.v')
