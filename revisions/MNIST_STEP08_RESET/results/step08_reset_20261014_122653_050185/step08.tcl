open_checkpoint {F:/k/CFU_Vivado_Bridge/MNIST_CFU_FUSION_20261013_V1/step07_clock_20261014_120301_621313/step07_route.dcp}

source step08_reset_constraints.xdc

report_timing_summary -delay_type min_max -report_unconstrained \
    -max_paths 10 -file step08_timing.rpt
report_timing -to [get_pins FDCE/D] -delay_type max \
    -max_paths 10 -file step08_reset_entry.rpt
report_cdc -details -file step08_cdc.rpt
report_exceptions -file step08_exceptions.rpt
report_methodology -file step08_methodology.rpt
report_drc -file step08_drc.rpt
report_route_status -file step08_route_status.rpt
report_utilization -hierarchical -file step08_utilization.rpt

foreach kind {max min} {
    set worst [get_timing_paths -delay_type $kind -max_paths 1]
    if {[llength $worst] == 0} {
        error "No timing path returned for $kind; stopping"
    }
    set slack [get_property SLACK $worst]
    puts "STEP08_${kind}_SLACK_NS=$slack"
    if {$slack < 0} {
        error "Timing violation remains; bitstream not generated"
    }
}

write_checkpoint step08_route.dcp
write_bitstream step08_nexys_video.bit
puts "STEP08_BITSTREAM_CREATED_NOT_BOARD_TESTED"
quit
