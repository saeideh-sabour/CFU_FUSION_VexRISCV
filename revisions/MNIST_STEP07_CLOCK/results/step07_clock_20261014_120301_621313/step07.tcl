create_project -in_memory -part xc7a200tsbg484-1
read_verilog cfu.v
read_verilog VexRiscv_FullCfu.v
read_verilog digilent_nexys_video.v
read_xdc digilent_nexys_video.xdc
synth_design -top digilent_nexys_video -part xc7a200tsbg484-1
write_checkpoint step07_synth.dcp
opt_design
place_design
phys_opt_design
route_design
phys_opt_design
write_checkpoint step07_route.dcp
report_route_status -file step07_route_status.rpt
report_utilization -hierarchical -file step07_utilization.rpt
report_timing_summary -delay_type min_max -report_unconstrained -max_paths 10 -file step07_timing.rpt
report_clock_interaction -file step07_clock_interaction.rpt
report_clocks -file step07_clocks.rpt
report_drc -file step07_drc.rpt
report_methodology -file step07_methodology.rpt
puts "STEP07_REPORTS_READY_NOT_BOARD_PASS"
quit
