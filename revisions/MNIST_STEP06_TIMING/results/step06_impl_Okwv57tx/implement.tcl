open_checkpoint step06_synth.dcp

opt_design
place_design
phys_opt_design

report_utilization -hierarchical -file step06_utilization_place.rpt
report_timing_summary -file step06_timing_place.rpt
write_checkpoint step06_place.dcp

route_design
phys_opt_design

write_checkpoint step06_route.dcp
report_route_status -file step06_route_status.rpt
report_utilization -hierarchical -file step06_utilization_route.rpt
report_utilization -file step06_utilization_route_full.rpt
report_timing_summary -delay_type min_max -max_paths 10 -report_unconstrained -file step06_timing_route.rpt
report_drc -file step06_drc.rpt
report_methodology -file step06_methodology.rpt

puts "STEP06_IMPLEMENTATION_FINISHED_REVIEW_REPORTS"
quit
