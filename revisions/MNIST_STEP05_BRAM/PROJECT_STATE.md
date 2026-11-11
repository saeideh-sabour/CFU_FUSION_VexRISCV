# Handoff — 2026-10-13 STEP05 BRAM candidate

- Goal: reusable Conv+requant+ReLU instruction family op0; independently callable Pool op1; capture, internal stream, both. FC CPU. Compare outputs/cycles/resources CPU-only, CFU unfused/fused on Nexys Video then Nexys A7-100T.
- Do NOT modify historical projects or framework/global Vivado bridge.
- Original project: ~/MNIST_CFU_FUSION_20261013_V1
- Original integration: ~/CFU-Playground/proj/mnist_cfu_fusion_20261013_v1
- CPU host reference: 10 samples PASS. RISC-V software compile/link: PASS (do_proj_menu C linkage fixed on user machine).
- STEP03 actual Nexys Video placement: whole SoC120171 LUT/54036 FF/23.5 BRAM/22 DSP; CFU59271 LUT/49614 FF/0 BRAM/18 DSP; VexRiscv58935 LUT/2130 FF. NOT CPU-only resource baseline.
- Old synth log explicitly dissolved inputs_reg and weights_reg into FFs; memories total49152 bits. Conv/Pool output banks LUTRAM. Critical kernel_index->lx path39.693ns,50levels,WNS-26.546ns at75MHz, pre-route only. Routing congestion.
- Exact uploaded snapshot inspected, CPU unchanged. Cross-boundary attribution is a possibility, NOT a proven explanation for VexRiscv LUT count.
- STEP05 standalone candidate: packed32 input/weight BRAM-style banks; synchronous Conv/Pool output read; serial 4-operand gather then MAC4; counter address generation replacing /%; internal stream preserved; same ISA and driver.
- More operand gather cycles are a deliberate resource tradeoff; no speedup claim.
- Constraints unchanged: Conv3x3/s1/p1/no bias; Pool2/s2; UINT8 activations, INT8 weights, Q31 ties-even; capacity limits remain.
- Candidate Verilator: see evidence/run.log. Hardware synthesis of candidate is PENDING.
- User next: local run_tests.sh then synth_only.py --stop-old-build. Flag preserves old evidence then stops only exact old project Vivado process. Fresh Windows directory each run, no old source overwrites. Needs original .init files retained in old bridge.
- NO automatic placement/routing. Inspect hierarchical resources and timing after synthesis before proceeding.
- NOT done: new Vivado resource/timing results, new integration software build, board run/bit correctness, cycles and fair CPU-only SoC resources, second board.
- Retain new version independently; do not replace old sources until reviewed.

Assistant verification COMPLETE: RTL_CORNER_TESTS PASS; RTL_ADDRESS_TESTS PASS shapes=8; RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0. Verilator build had no suppressed warning gate. Candidate Vivado synthesis still PENDING.

Local synthesis completed; inspect reports before implementation: /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/revisions/MNIST_STEP05_BRAM/results/synth_20261014_000707_670869
