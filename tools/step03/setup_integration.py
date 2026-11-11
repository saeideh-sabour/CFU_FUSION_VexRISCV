"""Create independent CFU Playground project + private Windows bridge.
Refuses to replace different existing contents. Does not run Vivado or delete anything.
"""
from pathlib import Path
import hashlib,json,os,re
root=Path(__file__).resolve().parents[2]
home=Path.home(); repo=home/'CFU-Playground'
project=repo/'proj/mnist_cfu_fusion_20261013_v1'
if not (root/'results/rtl_step03/run.log').is_file() or 'RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0' not in (root/'results/rtl_step03/run.log').read_text():
 raise SystemExit('Run tools/step03/run_tests.sh successfully first.')
bridge_source=home/'bin/vivado'
s=bridge_source.read_text()
old='BRIDGE="/mnt/f/k/CFU_Vivado_Bridge/digilent_nexys4ddr"\nWIN_BRIDGE=\'F:\\k\\CFU_Vivado_Bridge\\digilent_nexys4ddr\''
new='''BRIDGE_ROOT="/mnt/f/k/CFU_Vivado_Bridge/MNIST_CFU_FUSION_20261013_V1"
BUILD_TAG="${MNIST_BUILD_TAG:-digilent_nexys_video_cfu}"
if [[ ! "$BUILD_TAG" =~ ^[A-Za-z0-9_-]+$ ]]; then
    echo "Invalid MNIST_BUILD_TAG" >&2
    exit 2
fi
mkdir -p "$BRIDGE_ROOT"
BRIDGE="$(mktemp -d "$BRIDGE_ROOT/${BUILD_TAG}_XXXXXXXX")"
WIN_BRIDGE="$(wslpath -w "$BRIDGE")"'''
if s.count(old)!=1:raise SystemExit('Bridge source differs from inspected version; no files changed.')
s=s.replace(old,new)
if s.count('rm -rf "$BRIDGE"')!=1:raise SystemExit('Unexpected bridge cleanup block; no files changed.')
s=s.replace('rm -rf "$BRIDGE"','echo "INFO: New isolated bridge directory; previous builds retained."')
oldline=next((l for l in s.splitlines() if l.startswith('WIN_TCL=')),None)
if not oldline:raise SystemExit('Missing WIN_TCL; no files changed.')
s=s.replace(oldline,'WIN_TCL="$(wslpath -w "$BRIDGE/$TCL_NAME")"')
s=s.replace('TCL_NAME="$TCL"','TCL_NAME="$(basename "$TCL")"')
# Normalize line endings in generated scripts and stamp provenance.
s='# Private copy for MNIST_CFU_FUSION_20261013_V1; original wrapper preserved.\n'+s
s=s.replace('# Private copy for MNIST_CFU_FUSION_20261013_V1; original wrapper preserved.\n#!/usr/bin/env bash','#!/usr/bin/env bash\n# Private copy for MNIST_CFU_FUSION_20261013_V1; original wrapper preserved.')
source_c=(root/'software/cpu_reference.c').read_text().replace('#include "../model/model_data.h"','#include "model_data.h"')
items={
 project/'Makefile':b'export DEFINES := NDEBUG\nexport SKIP_TFLM := 1\nexport USE_VIVADO := 1\ninclude ../proj.mk\n',
 project/'cfu.v':(root/'rtl/step03/cfu.v').read_bytes(),
 project/'src/proj_menu.cc':(root/'software/step03/proj_menu.cc').read_bytes(),
 project/'src/cpu_reference.c':source_c.replace('int main(void){','int scalar_reference_main(void){').encode(),
 project/'src/cfu_driver.h':(root/'software/step03/cfu_driver.h').read_bytes(),
 project/'src/model_data.h':(root/'model/model_data.h').read_bytes(),
 root/'tools/step03/bin/vivado':s.encode(),
}
# Include reference implementation as a header to avoid duplicate separately compiled symbols.
items[project/'src/cpu_reference_impl.h']=items.pop(project/'src/cpu_reference.c')
items[project/'src/proj_menu.cc']=items[project/'src/proj_menu.cc'].replace(b'#include "cpu_reference.c"',b'#include "cpu_reference_impl.h"')
for path,content in items.items():
 if path.exists() and path.read_bytes()!=content:
  raise SystemExit(f'Existing different file; stopped before writing: {path}')
for path,content in items.items():
 path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(content)
os.chmod(root/'tools/step03/bin/vivado',0o755)
manifest={str(p):hashlib.sha256(b).hexdigest() for p,b in items.items()}
(root/'results/step03_integration_manifest.json').write_text(json.dumps(manifest,indent=2))
with (root/'PROJECT_STATE.md').open('a') as f:
 f.write('\n## STEP03 Integration files prepared (build/run not yet verified)\n')
 f.write(f'- CFU Playground project: {project}\n- Source workspace remains: {root}\n')
 f.write('- Private Vivado wrapper: tools/step03/bin/vivado; new Windows directory per build.\n')
 f.write('- NEXT: build software in independent project; inspect errors before board synthesis.\n')
print('Independent project:',project)
print('Private bridge:',root/'tools/step03/bin/vivado')
print('Files prepared; no Vivado, FPGA programming or shared-directory cleanup executed.')
