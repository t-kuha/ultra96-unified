set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

# ----------------------------------------------------------------------------
# Bluetooth
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN B5   [get_ports {BT_HCI_CTS             }];  # "B5.BT_HCI_CTS"
set_property PACKAGE_PIN B7   [get_ports {BT_HCI_RTS             }];  # "B7.BT_HCI_RTS"
#set_property PACKAGE_PIN A9   [get_ports {RADIO_LED0             }];  # "A9.RADIO_LED0"
#set_property PACKAGE_PIN B9   [get_ports {RADIO_LED1             }];  # "B9.RADIO_LED1"

# ----------------------------------------------------------------------------
# Fan control
# ---------------------------------------------------------------------------- 
# Bank 65
set_property PACKAGE_PIN F4   [get_ports {fan_en_b[0]            }];  # "F4.fan_en_b"

# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];

# Set the bank voltage for IO Bank 65 to 1.2V
set_property IOSTANDARD LVCMOS12 [get_ports -of_objects [get_iobanks 65]];

# Set the bank voltage for IO Bank 66 to 1.2V
set_property IOSTANDARD LVCMOS12 [get_ports -of_objects [get_iobanks 66]];

# Fan Speed Enable
#set_property PACKAGE_PIN F4 [get_ports {fan_en_b[0]}]
#set_property IOSTANDARD LVCMOS18 [get_ports {fan_en_b[0]}]
#set_property SLEW SLOW [get_ports {fan_en_b[0]}]
#set_property DRIVE 4 [get_ports {fan_en_b[0]}]
