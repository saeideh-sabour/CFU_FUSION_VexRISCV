# STEP03 implemented interface and validation

This update supersedes the initial audit-only RTL status. RTL lives in rtl/step03 and is concatenated into cfu.v by tools/step03/build_rtl.py. This avoids external Verilog source paths during the Windows bridge build.

## Implemented scope
- One reusable full-layer Conv3x3 stride1 padding1 engine, bias-free, UINT8 activations, signed INT8 weights with zero point zero.
- Four products per MAC step, INT32 accumulator, signed INT64 Q31 product, round nearest ties-even, output zero point, UINT8 clamp and ReLU.
- MaxPool2x2 stride2, independent CPU input or internal Conv stream. CHW raster order.
- Capacity defaults: input 2048 bytes; weights 4096 bytes; Conv result 8192 bytes; Pool result 4096 bytes. Width/height <=32, channels <=32, plus capacity checks. Parameters are intended to use power-of-two bank sizes >=2. These limits support both supplied Conv layers, not arbitrary CNNs.
- Internal stream uses a registered Conv result and valid/ready link into a horizontal-max line buffer; no external RAM or bus-master port exists. There is no separate FIFO in this revision. It satisfies the allowed register/stream path.
- Route 1=CAPTURE, 2=STREAM, 3=BOTH. CAPTURE becomes memory write-back only when the CPU drains and stores results. Fused mode does not drain/store/reload Conv results.
- Pool must ARM before fused START. START rejects unarmed, partially used or shape-mismatched Pool state.
- START is blocking until the full Conv completes; Pool runs concurrently. No asynchronous software task or interrupts are needed.
- Input/weights/multipliers are loaded by software before START. Reset resets control/counters, not data banks. Calling START without initializing all required data is a software contract violation, not detected by per-byte validity bits.

## ISA
funct3 is family 0 or 1; funct7 is sub-operation. Actual RTL function_id = (funct7 << 3) | funct3.

| Family | funct7 | Operation | rs1 | rs2 | result |
|---|---:|---|---|---|---|
| op0 | 0 | CONFIG | index | value | 0 or error |
| op0 | 1 | INPUT4 | aligned byte offset | 4 little-endian UINT8 bytes | 0 or error |
| op0 | 2 | WEIGHT4 | aligned byte offset | 4 little-endian INT8 bytes | 0 or error |
| op0 | 3 | MULTIPLIER | output channel | nonnegative Q31 | 0 or error |
| op0 | 4 | START_CONV | ignored | ignored | full Conv output count |
| op0 | 5 | READ_CONV | index | ignored | byte or error |
| op0 | 6 | CAPTURE_COUNT | ignored | ignored | count |
| op0 | 7 | ID | ignored | ignored | 0x43465531 |
| op1 | 0 | ARM_POOL | ignored | ignored | 0 or error |
| op1 | 1 | PUSH_BYTE | UINT8 value | ignored | 0 or error |
| op1 | 2 | READ_POOL | index | ignored | byte or error |
| op1 | 3 | POOL_STATUS | ignored | ignored | done bit16, count bits15:0 |

CONFIG indices: 0 width, 1 height, 2 input channels, 3 output channels, 4 input zero point, 5 output zero point, 6 route. Pool ARM snapshots width, height and output channels. Invalid results have bit31 set: 1 bad config; 2 bad load; 3 invalid start/arm; 4 unreadable result; 5 unknown instruction; 6 invalid Pool push. Empty Pool reads and unknown operations respond with an error rather than hanging the CPU.

## Tests actually completed in assistant environment
Verilator compiled without suppressing warnings. The C++ harness exercises the RTL clock/handshake and changes operands immediately after handshake. Responses were stalled for 0–3 cycles and checked for stability.

10 images × UNFUSED/FUSED/BOTH: zero tensor mismatches at all exposed checkpoints. Conv1, Conv2 and MaxPool execute in RTL; FC executes on host CPU. FUSED checks Pool outputs and FC outputs without reading Conv tensors. UNFUSED/BOTH additionally compare Conv outputs. Predictions in each mode: 7,2,1,0,4,1,4,9,5,9.

Corner tests: ties-to-even, centered signed activations, nonzero zero point, signed weights, UINT8 saturation, odd Pool width rejection, invalid byte rejection without consuming input, unknown opcode, out-of-range load, unconfigured START, unarmed fused START, read rejection in stream-only mode, Pool overflow push rejection and control reset.

Evidence: verification/step03_assistant_run.log. Local rerun produces results/rtl_step03/run.log. Test results establish functional correctness for these cases, not exhaustive proof.

## Limitations and next gates
No Vivado synthesis/place-and-route has run. Memory banking, address-generation arithmetic and multiport reads/writes have not been optimized or proven to map efficiently to BRAM. Do not infer DSP count, LUT count, timing closure or FPGA speedup from this revision. The driver currently reloads input/weights and drains bytes per layer; transfer cost is included by the RISC-V harness. Optimization must follow measured results.

The integer Q31 contract matches supplied golden outputs for the 10 samples, not yet validated over all 10,000 test images.

Integration files are provided but not yet compiled against the user's installed LiteX build. `do_proj_menu()` runs CPU_ONLY, CFU_UNFUSED, CFU_FUSED and CFU_BOTH. In that harness CPU_ONLY runs on the same SoC containing the CFU; a separate SoC without CFU is required for total-resource baseline. `rdcycle` 32-bit differences require each timed case to finish within one wrap. One untimed warm-up precedes each mode. The stage values group Conv+Pool together because fused Conv START overlaps Pool.

No full CPU emulation occurred in the local RTL test. RISC-V cycle results in Renode are not automatically physical-FPGA results. Final comparisons need actual board logs, clock, compiler flags, cache policy and timing closure.

## Reproduce on user WSL
1. `bash tools/step03/run_tests.sh`
2. `python3 tools/step03/setup_integration.py`
3. Build software in `~/CFU-Playground/proj/mnist_cfu_fusion_20261013_v1`; use the private bridge directory first in PATH whenever building gateware.

Private wrapper uses a new unique directory under F:\k\CFU_Vivado_Bridge\MNIST_CFU_FUSION_20261013_V1 on every actual build. Original ~/bin/vivado is preserved. The wrapper is prepared by strict transformation of the inspected source; it refuses an unexpected original version.
