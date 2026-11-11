
set chain [get_cells {FDCE FDCE_1 FDCE_2 FDCE_3 FDCE_4 FDCE_5 FDCE_6 FDCE_7}]
if {[llength $chain] != 8} {
    error "Reset chain does not match the audited design"
}
set entry [get_pins FDCE/D]
set launch [get_cells {soc_basesoc_reset_re_reg soc_basesoc_reset_storage_reg[0]}]
if {[llength $entry] != 1 || [llength $launch] != 2} {
    error "Reset endpoints do not match the audited design"
}

# Reset sampling may take an additional destination-clock cycle.
# Preserve timing checks between every pair of synchronizer stages.
set_property ASYNC_REG TRUE $chain
set_max_delay 2.000 -datapath_only -from $launch -to $entry

# External pushbutton is asynchronous, only to the first sampling stage.
set_false_path -from [get_ports cpu_reset] -to $entry
