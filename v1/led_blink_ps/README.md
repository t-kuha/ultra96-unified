# Blinking LEDs connected to PS

- Basic baremetal (standalone) application

***

## How to build

```shell-session
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl

# platform & application
$ vitis -s create_platform.py
$ vitis -s create_app.py
$ bootgen -image ./bootbin.bif -arch zynqmp -o BOOT.bin -w on
```

## Run

- Copy the contents of  ``BOOT.bin`` into SD card and power up the board
- Check if LED0 - LED3 will blink
