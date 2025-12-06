# Blinking LEDs connected to PS

- Basic baremetal (standalone) application

***

## How to build

```shell
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl

# platform & application
$ vitis -s create_platform.py
$ vitis -s create_app.py
```

## Run

- Copy the contents of ``BOOT.bin`` into SD card and power up the board
- Check if LED0 - LED3 will blink

```shell-session
Zynq MP First Stage Boot Loader 
Release 2025.2   Dec  6 2025  -  06:51:56
PMU-FW is not running, certain applications may not be supported.
..... LED Blink .....
```
