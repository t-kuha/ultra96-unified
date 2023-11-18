set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

# ----------------------------------------------------------------------------
# Bluetooth
# ---------------------------------------------------------------------------- 
# Bank 26
#set_property PACKAGE_PIN C8   [get_ports {BT_AUD_CLK              }];  # "C8.BT_AUD_CLK"
#set_property PACKAGE_PIN A8   [get_ports {BT_AUD_FSYNC            }];  # "A8.BT_AUD_FSYNC"
#set_property PACKAGE_PIN A9   [get_ports {BT_AUD_IN               }];  # "A9.BT_AUD_IN"
#set_property PACKAGE_PIN B9   [get_ports {BT_AUD_OUT              }];  # "B9.BT_AUD_OUT"
set_property PACKAGE_PIN B5   [get_ports {BT_HCI_CTS              }];  # "B5.BT_HCI_CTS"
set_property PACKAGE_PIN B7   [get_ports {BT_HCI_RTS              }];  # "B7.BT_HCI_RTS"

# ----------------------------------------------------------------------------
# Fan control
# ---------------------------------------------------------------------------- 
# Bank 65
set_property PACKAGE_PIN F4   [get_ports {fan_en_b[0]             }];  # "F4.FAN_PWM"

# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];

# Set the bank voltage for IO Bank 65 to 1.2V
set_property IOSTANDARD LVCMOS12 [get_ports -of_objects [get_iobanks 65]];
