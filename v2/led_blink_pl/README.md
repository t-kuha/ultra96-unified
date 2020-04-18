# Blinking LEDs connected to PL

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# HW - Launch Vivado shell
$ vivado -mode batch -source create_vivado_project.tcl

# SW - Launch xsct that is part of SDK
$ xsct create_boot_bin.tcl
```

## Run

- Copy BOOT.bin to SD Card and power up the board
  - LED D9 & D10 will blink
