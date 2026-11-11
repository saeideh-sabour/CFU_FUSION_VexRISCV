
create_project -in_memory -part xc7a200tsbg484-1
read_verilog cfu.v
read_verilog VexRiscv_FullCfu.v
read_verilog digilent_nexys_video.v
read_xdc digilent_nexys_video.xdc
synth_design -top digilent_nexys_video -part xc7a200tsbg484-1
source step09_reset_constraints.xdc
write_checkpoint step09_synth.dcp
opt_design
place_design
phys_opt_design
route_design
phys_opt_design

report_timing_summary -delay_type min_max -report_unconstrained \
    -max_paths 10 -file step09_timing.rpt
report_route_status -file step09_route_status.rpt
report_utilization -hierarchical -file step09_utilization.rpt
report_cdc -details -file step09_cdc.rpt
report_methodology -file step09_methodology.rpt
report_drc -file step09_drc.rpt
report_exceptions -file step09_exceptions.rpt
write_checkpoint step09_route.dcp

# Stop before bitstream if CDC still has a Critical finding.
set f [open step09_cdc.rpt r]
set cdc [read $f]
close $f
if {[regexp -nocase {Critical} $cdc]} {
    error "Critical CDC finding remains; inspect step09_cdc.rpt"
}

foreach kind {max min} {
    set p [get_timing_paths -delay_type $kind -max_paths 1]
    if {[llength $p] == 0} {
        error "Missing timing paths for $kind"
    }
    set slack [get_property SLACK $p]
    puts "STEP09_${kind}_SLACK_NS=$slack"
    if {$slack < 0} {
        error "Timing violation remains; bitstream not generated"
    }
}

write_bitstream step09_nexys_video.bit
puts "STEP09_BITSTREAM_CREATED_NOT_BOARD_TESTED"
quit
