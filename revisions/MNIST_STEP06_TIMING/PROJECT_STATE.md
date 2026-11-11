# Current handoff — STEP06 — 2026-10-14

Goal: reusable op0 Conv+requant+ReLU; op1 Pool; capture/internal stream/both; FC CPU. CPU vs CFU outputs, cycles, resources. Nexys Video first, Nexys A7-100T second.
Original root ~/MNIST_CFU_FUSION_20261013_V1; original integration ~/CFU-Playground/proj/mnist_cfu_fusion_20261013_v1. Never overwrite historical projects.
CPU host reference PASS; original RISC-V software build PASS, do_proj_menu C linkage fixed on user's integration.
STEP03: input/weight banks dissolved into registers, whole SoC120171 placed LUT, CFU49614 FF, no CFU BRAM; congestion; old routing stopped deliberately.
STEP05 local user RTL tests PASS. Successful synthesis bridge: step05_bram_synth_20261014_000707_670869.
STEP05 synthesis whole5999 LUT/4154 FF/28 BRAM36-equivalent/17 DSP; CFU974 LUT/397 FF/4.5 BRAM/13 DSP; VexRiscv2972 LUT. CPU source unchanged. WNS=-3.918ns at75MHz. These are synthesis, not final implementation resources.
Critical path evidence uploaded as text: height_reg -> valid_conv arithmetic/control -> product DSP CEB2/CEA2;16.522ns delay,16 logic levels.
STEP06 changes only configuration derived dimension/validation pipeline: CFG1 plane/kernel length, CFG2 total/input/weight sizes, CFG3 registered valid flags and CONFIG response. Added3 cycles per CONFIG. Keep data path and ISA, internal Fusion, CPU and clock constraints unchanged.
STEP06 assistant Verilator PASS: corner tests,8 shape/capacity tests,10 samples x3 modes zero mismatches. evidence/run.log is actual new execution.
NEXT USER: extract separate revisions/MNIST_STEP06_TIMING, run tools/run_tests.sh then python3 tools/synth_only.py (no stop flag). Uses original memory init files retained in old bridge.
Windows command quoting fix included. Each synthesis isolated. No automatic placement/routing.
PENDING: STEP06 user simulation/synthesis/WNS/resources; route/bitstream; integration with firmware; actual board output and cycles; CPU-only hardware resource baseline; second board.
Do not assume functional simulation proves timing or speedup. Inspect synthesis before implementation. Keep all versions distinct.

Local synthesis completed; inspect reports before implementation: /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/revisions/MNIST_STEP06_TIMING/results/synth_20261014_113206_785103
