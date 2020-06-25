# Blinking LEDs connected to PL

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# HW
$ vivado -mode batch -source create_xsa.tcl

# SW
$ xsct create_pfm.tcl
$ xsct create_app.tcl
```

## Run

- Copy BOOT.bin to SD Card and power up the board
  - LED D9 & D10 will blink
