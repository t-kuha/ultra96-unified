# Building Vitis Application Acceleration Platform

***

## Create hardware

```shell
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl
```

## Create PetaLinux project

```shell
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

```shell
$ vitis -s create_vitis_platform.py
```

## Build vector addition app

```shell
$ IDE_ZYNQMP_SYSROOT=<path to sysroot> vitis -s create_vadd_app.py
```

- copy the contents of ``_vitis-ws/vadd/build/hw/package/package/sd_card`` into SD card

***

## How to create PetaLinux project from scratch

```shell
$ export PRJ=petalinux
$ petalinux-create project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=hw.xsa

# Do some configuration
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c rootfs

# Build project
$ petalinux-build -p ${PRJ}
```

***

## References

- [Avnet Ultra96-PYNQ repo](https://github.com/Avnet/Ultra96-PYNQ)
