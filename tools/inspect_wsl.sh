#!/usr/bin/env bash
# Read-only inspection of existing tools/repository. No build, clean, checkout or writes there.
set -u
printf '\n=== HOST ===\n'
uname -a
printf '\n=== TOOLS ===\n'
for tool in python3 gcc make git verilator iverilog yosys riscv64-unknown-elf-gcc riscv32-unknown-elf-gcc vivado vivado.bat; do
  command -v "$tool" || true
done
python3 - <<'PY'
import importlib.util,sys
print('python:',sys.executable)
for n in ('numpy','torch','amaranth','litex','migen'):
 try: print(n, bool(importlib.util.find_spec(n)))
 except (ImportError,ValueError): print(n,False)
PY
repo="$HOME/CFU-Playground"
printf '\n=== CFU PLAYGROUND ===\n'
if [ -d "$repo" ]; then
 git -C "$repo" rev-parse HEAD 2>/dev/null || true
 git -C "$repo" diff --stat 2>/dev/null || true
 for f in "$repo/common/src/cfu.h" "$repo/proj/proj.mk" "$repo/proj/example_cfu/Makefile"; do
  if [ -f "$f" ]; then
   printf '\nFILE %s\n' "$f"
   sed -n '1,180p' "$f"
  fi
 done
 printf '\n=== RELEVANT TARGET/BRIDGE FILE NAMES ===\n'
 if command -v rg >/dev/null; then
  rg --files "$repo/soc" "$repo/proj" -g '*nexys*' -g '*bridge*' -g '*vivado*.sh' -g '*vivado*.py' -g '!build/**' 2>/dev/null | head -60 || true
 fi
else
 printf 'CFU-Playground not found at %s\n' "$repo"
fi
printf '\n=== KNOWN WINDOWS BRIDGE DIRECTORY ===\n'
if [ -d /mnt/f/k/CFU_Vivado_Bridge ]; then
 ls -1 /mnt/f/k/CFU_Vivado_Bridge
else
 printf 'Not present at /mnt/f/k/CFU_Vivado_Bridge; existing bridge path must be identified before build.\n'
fi
printf '\nInspection complete. Existing projects were not modified.\n'
