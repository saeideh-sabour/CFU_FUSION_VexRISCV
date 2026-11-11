
set launch [get_cells -quiet step09_request_reg]
set sw0 [get_pins -quiet {step09_sw_sync_reg[0]/D}]
set button0 [get_pins -quiet {step09_button_sync_reg[0]/D}]
if {[llength $launch] != 1 || [llength $sw0] != 1 ||
    [llength $button0] != 1} {
    error "Expected STEP09 synchronizer endpoints not found"
}
set_max_delay 2.000 -datapath_only -from $launch -to $sw0
set_false_path -from [get_ports cpu_reset] -to $button0
