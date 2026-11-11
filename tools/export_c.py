"""Export the audited 10-image bundle; run from project root after audit_model.py."""
from pathlib import Path
import json,numpy as np
r=json.loads(Path('verification/audit.json').read_text());a=np.load('verification/reference_arrays.npz')
out=Path('model/model_data.h')
with out.open('w') as f:
 f.write('#ifndef MODEL_DATA_H\n#define MODEL_DATA_H\n#include <stdint.h>\n')
 for name in ['conv1_weights','conv2_weights','fc1_weights','fc2_weights','conv1_q31','conv2_q31','fc1_q31','fc2_q31','input','conv1','conv1_pool','conv2','conv2_pool','fc1','fc1_relu','fc2','labels']:
  v=a[name].ravel();typ='int8_t' if name.endswith('weights') else ('int32_t' if name.endswith('q31') else 'uint8_t')
  f.write(f'static const {typ} data_{name}[{v.size}] = {{\n')
  for start in range(0,len(v),32): f.write(','.join(str(int(x)) for x in v[start:start+32])+',\n')
  f.write('};\n')
 f.write('#endif\n')
print(out)
