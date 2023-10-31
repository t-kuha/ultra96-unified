# Blinking LEDs connected to PS

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# HW - Launch Vivado shell
$ vivado -mode batch -source create_xsa.tcl

# SW - Platform
$ xsct create_pfm.tcl

# SW - Application
$ export PLATFORM_REPO_PATHS=$(pwd)/_pfm/u96_led/export/
$ xsct create_app.tcl
```

## Run

- Copy the contents of  ``_app/led_blink_ps_system/Release/sd_card/`` into SD card and power up the board
- Check if LED0 - LED3 will blink
