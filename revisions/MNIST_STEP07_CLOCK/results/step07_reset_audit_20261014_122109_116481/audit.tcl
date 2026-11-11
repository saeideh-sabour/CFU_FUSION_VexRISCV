open_checkpoint {F:/k/CFU_Vivado_Bridge/MNIST_CFU_FUSION_20261013_V1/step07_clock_20261014_120301_621313/step07_route.dcp}

set names {FDCE FDCE_1 FDCE_2 FDCE_3 FDCE_4 FDCE_5 FDCE_6 FDCE_7}
set f [open reset_chain.txt w]
foreach n $names {
    set c [get_cells -quiet $n]
    if {[llength $c] != 1} {
        error "Expected exactly one reset register: $n"
    }
    puts $f "\nREGISTER: $n"
    puts $f "TYPE: [get_property REF_NAME $c]"
    puts $f "ASYNC_REG: [get_property ASYNC_REG $c]"
    foreach p {C D Q CE CLR} {
        set pin [get_pins ${n}/${p}]
        set nets [get_nets -of_objects $pin]
        puts $f "$p NET: $nets"
        puts $f "$p CONNECTED PINS: [get_pins -of_objects $nets]"
    }
}
close $f

report_cdc -details -file reset_cdc.rpt
report_timing -to [get_pins FDCE/D] -delay_type max \
    -max_paths 20 -path_type full_clock_expanded -file reset_entry_setup.rpt
report_timing -to [get_pins FDCE/D] -delay_type min \
    -max_paths 20 -path_type full_clock_expanded -file reset_entry_hold.rpt

set chain_d [get_pins {FDCE_1/D FDCE_2/D FDCE_3/D FDCE_4/D FDCE_5/D FDCE_6/D FDCE_7/D}]
report_timing -to $chain_d -delay_type max \
    -max_paths 20 -file reset_chain_setup.rpt
report_timing -to $chain_d -delay_type min \
    -max_paths 20 -file reset_chain_hold.rpt

report_exceptions -file reset_exceptions.rpt
puts "RESET_AUDIT_COMPLETE_NO_DESIGN_CHANGES"
quit
