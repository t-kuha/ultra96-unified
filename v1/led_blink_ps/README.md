# Blinking LEDs connected to PS

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# HW - Launch Vivado shell
$ vivado -mode batch -source create_xsa.tcl

# SW
$ xsct create_pfm.tcl
$ xsct create_app.tcl
```

## Run

- Copy the contents of  ``_app/led_blink_ps_system/Debug/sd_card/`` into SD card and power up the board
