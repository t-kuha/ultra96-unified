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

# Show actual build time of Kernel & u-boot
$ petalinux-build -p ${PRJ} -c linux-xlnx -x cleansstate
$ petalinux-build -p ${PRJ} -c u-boot-xlnx -x cleansstate

# Build project
$ petalinux-build -p ${PRJ}
```

***

## References

- [Avnet Ultra96-PYNQ repo](https://github.com/Avnet/Ultra96-PYNQ)
