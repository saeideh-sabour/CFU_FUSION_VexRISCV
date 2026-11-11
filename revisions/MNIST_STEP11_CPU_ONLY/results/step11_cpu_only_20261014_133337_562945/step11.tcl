
create_project -in_memory -part xc7a200tsbg484-1

read_verilog VexRiscv_Full.v
read_verilog digilent_nexys_video.v
read_xdc digilent_nexys_video.xdc
synth_design -top digilent_nexys_video -part xc7a200tsbg484-1
source step09_reset_constraints.xdc
write_checkpoint step11_synth.dcp
opt_design
place_design
phys_opt_design
route_design
phys_opt_design

report_timing_summary -delay_type min_max -report_unconstrained \
    -max_paths 10 -file step11_timing.rpt
report_route_status -file step11_route_status.rpt
report_utilization -hierarchical -file step11_utilization.rpt
report_cdc -details -file step11_cdc.rpt
report_methodology -file step11_methodology.rpt
report_drc -file step11_drc.rpt
report_exceptions -file step11_exceptions.rpt
write_checkpoint step11_route.dcp

# Stop before bitstream if CDC still has a Critical finding.
set f [open step11_cdc.rpt r]
set cdc [read $f]
close $f
if {[regexp -nocase {Critical} $cdc]} {
    error "Critical CDC finding remains; inspect step11_cdc.rpt"
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

# Resource comparison only; no bitstream requested.
puts "STEP11_CPU_ONLY_REPORTS_READY_NOT_BOARD_TESTED"
quit
