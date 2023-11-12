set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

# Fan Speed Enable
set_property PACKAGE_PIN F4 [get_ports {fan_en_b[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {fan_en_b[0]}]
set_property SLEW SLOW [get_ports {fan_en_b[0]}]
set_property DRIVE 4 [get_ports {fan_en_b[0]}]
