#!/usr/bin/env bash
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"
mkdir -p results/local_rtl/obj
verilator --version > results/local_rtl/verilator_version.txt
if ! verilator --cc --exe --build -j 4 --top-module Cfu \
 --Mdir "$root/results/local_rtl/obj" "$root/rtl/cfu.v" \
 "$root/simulation/tb_step05.cpp" > results/local_rtl/build.log 2>&1; then
 tail -80 results/local_rtl/build.log
 exit 1
fi
"$root/results/local_rtl/obj/VCfu" | tee results/local_rtl/run.log
