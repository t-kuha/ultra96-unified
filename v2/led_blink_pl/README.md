# Blinking LEDs connected to PL

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# Generate HW
$ vivado -mode batch -source create_xsa.tcl

# Generate Pplatform
$ xsct create_pfm.tcl

# Build application
$ export PLATFORM_REPO_PATHS=$(pwd)/_pfm/u96v2_led/export/
$ xsct create_app.tcl
```

## Run

- Copy ``_app/led_blink_pl_system/Release/sd_card/BOOT.bin`` to SD Card and power up the board
  - LED D9 & D10 will blink
