# Blinking LEDs connected to PL

- Basic baremetal (standalone) application

***

## How to build

```shell-session
# Generate HW
$ vivado -mode batch -source create_xsa.tcl

# Generate Pplatform
$ vitis -s create_platform.py

# Build application & generate BOOT.bin
$ vitis -s create_app.py
$ bootgen -image ./bootbin.bif -arch zynqmp -o BOOT.bin -w on
```

## Run

- Copy ``BOOT.bin`` to SD Card and power up the board
  - LED D9 & D10 will blink
