# Building Vitis Application Acceleration Platform

***

## Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
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

# Generate SDK (optional)
$ petalinux-build -p ${PRJ} --sdk
```

## Generate platform

```shell-session
$ xsct create_pfm.tcl
```

***

## How to create PetaLinux project from scratch

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.

# Do some configuration
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c rootfs

# Show actual build time of Kernel & u-boot
$ petalinux-build -p ${PRJ} -c linux-xlnx -x cleansstate
$ petalinux-build -p ${PRJ} -c u-boot-xlnx -x cleansstate

# Build project
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk
```

***

## References

- [How to shut down the Ultra96 V1 or V2 boards directly](https://www.xilinx.com/support/answers/76583.html)

- [Why does the PS DisplayPort not work on Ultra96 boards?](https://www.xilinx.com/support/answers/76568.html)

- [Why do U-boot and the Kernel not show the current build timestamp](https://www.xilinx.com/support/answers/76559.html)

- [PetaLinux does not mount full rootfs when boot INITRD images are built using the template method](https://www.xilinx.com/support/answers/76842.html)
