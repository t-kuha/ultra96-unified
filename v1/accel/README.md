# Building Vitis Application Acceleration Platform

***

## Create hardware

```shell-session
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl
```

## Create PetaLinux project

```shell-session
$ export PRJ=petalinux
$ petalinux-config -p ${PRJ}

# Make additional configuration if necessary
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c rootfs

# Start build
$ petalinux-build -p ${PRJ}
```

## Generate platform

```shell-session
$ vitis -s create_vitis_platform.py
```

***

## How to create PetaLinux project from scratch

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=hw.xsa

# Do some configuration
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c rootfs

# Build project
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk
```

***

## References

- [Why do U-boot and the Kernel not show the current build timestamp](https://www.xilinx.com/support/answers/76559.html)

- [PetaLinux does not mount full rootfs when boot INITRD images are built using the template method](https://www.xilinx.com/support/answers/76842.html)

- [Debian/Ubuntu でKV260 で冷却ファンを制御する (その２)](https://qiita.com/ikwzm/items/f94748f5353271aab5ee)

- Wi-Fi firmware
  - wl18xx-fw-4.bin: [processor-firmware/ti-linux-firmware](https://git.ti.com/cgit/processor-firmware/ti-linux-firmware/log/ti-connectivity/wl18xx-fw-4.bin?h=ti-linux-firmware)
