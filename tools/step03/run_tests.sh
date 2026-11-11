#!/usr/bin/env bash
set -euo pipefail
project="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$project"
mkdir -p results/rtl_step03
python3 tools/step03/build_rtl.py
command -v verilator >/dev/null
command -v g++ >/dev/null
verilator --version | tee results/rtl_step03/verilator_version.txt
mkdir -p results/rtl_step03/obj
if ! verilator --cc --exe --build -j 4 --top-module Cfu \
  --Mdir "$project/results/rtl_step03/obj" \
  "$project/rtl/step03/cfu.v" "$project/simulation/tb_step03.cpp" \
  > results/rtl_step03/build.log 2>&1; then
  tail -100 results/rtl_step03/build.log
  exit 1
fi
./results/rtl_step03/obj/VCfu | tee results/rtl_step03/run.log
python3 - <<'PY'
from pathlib import Path
p=Path('results/rtl_step03/run.log')
assert 'RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0' in p.read_text()
s=Path('PROJECT_STATE.md')
with s.open('a') as f:
 f.write('''\n## STEP03 LOCAL RTL TEST PASS — supersedes earlier pending RTL status\n- CPU Q31 reference passed on user WSL (reported 2026-10-13).\n- Local Verilator test now passed: 10 samples, 3 modes, zero mismatches.\n- UNFUSED, FUSED, BOTH; Conv/Pool computed in RTL, FC on host CPU.\n- Source: rtl/step03; driver: software/step03/cfu_driver.h.\n- Evidence: results/rtl_step03/run.log and build.log.\n- Not yet RISC-V/FPGA execution; no hardware cycles/resources measured.\n- NEXT: tools/step03/setup_integration.py; then isolated project software build.\n- Never invoke the old shared Vivado bridge for this project: it deletes its shared directory.\n''')
print('PROJECT_STATE.md updated after actual local RTL PASS.')
PY
