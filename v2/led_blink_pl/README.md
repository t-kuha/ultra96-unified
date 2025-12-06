# Blinking LEDs connected to PL

- Basic baremetal (standalone) application

***

## How to build

```shell
# Generate HW
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl

# Generate Pplatform
$ vitis -s create_platform.py

# Build application & generate BOOT.bin
$ vitis -s create_app.py
```

## Run

- Copy ``BOOT.bin`` to SD Card and power up the board
  - LED D9 & D10 will blink

```shell
Zynq MP First Stage Boot Loader 
Release 2025.2   Dec  6 2025  -  07:25:17
PMU-FW is not running, certain applications may not be supported.
..... Blinking PL LEDs .....
```