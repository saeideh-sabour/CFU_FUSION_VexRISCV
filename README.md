# MNIST CFU Fusion — audit and verified CPU baseline V1

Start with PROJECT_STATE.md, then docs/AUDIT_FA.md.
This package is NOT completed RTL, an FPGA bitstream, or a benchmark result.

## Reproduce host C validation (gcc only)
```bash
mkdir -p results/host
cc -O2 -Wall -Wextra -Werror -std=c11 software/cpu_reference.c -o results/host/cpu_reference
./results/host/cpu_reference
```
The input is already quantized; this validates inference, not runtime image preprocessing. Production timing must omit the golden arrays/checks and state whether preprocessing is included. The current header includes golden arrays for host validation and is not the final embedded memory layout.

## Reproduce source audit (Python + NumPy)
```bash
python3 -m zipfile -e source_original.zip source_original
python3 tools/audit_model.py source_original/MNIST_CNN --out verification
python3 tools/export_c.py
```
Decoder supports only the supplied tensor state_dict format. No arbitrary uploaded model code is executed. Only the first 10 test samples are checked; full-dataset testing is pending.

## Inspect WSL before integration
```bash
bash tools/inspect_wsl.sh
```
This reads installed configuration. It does not build, clean, install dependencies, modify previous projects, or invoke Windows Vivado.
