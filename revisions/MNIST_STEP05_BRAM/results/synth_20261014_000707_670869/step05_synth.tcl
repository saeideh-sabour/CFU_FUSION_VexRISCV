create_project -force -name step05_synth -part xc7a200t-sbg484-1
set_msg_config -id {Common 17-55} -new_severity {Warning}
read_verilog {cfu.v}
read_verilog {VexRiscv_FullCfu.v}
read_verilog {digilent_nexys_video.v}
read_xdc {digilent_nexys_video.xdc}
set_property PROCESSING_ORDER EARLY [get_files digilent_nexys_video.xdc]
synth_design -directive default -top digilent_nexys_video -part xc7a200t-sbg484-1
report_utilization -hierarchical -file step05_utilization_hierarchical_synth.rpt
report_utilization -file step05_utilization_synth.rpt
report_timing_summary -max_paths 10 -file step05_timing_synth.rpt
write_checkpoint -force step05_synth.dcp
puts "STEP05_SYNTH_ONLY_COMPLETE_NO_ROUTING"
quit
