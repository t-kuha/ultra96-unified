# Linux platform

***

## How to build

### Generate HW

```shell-session
$ vivado -mode batch -source create_vivado_project.tcl
```

### Build PetaLinux project

```shell-session
$ export PRJ=petalinux

# Create project
$ petalinux-config -p ${PRJ} --get-hw-description=.

# Build
$ petalinux-build -p ${PRJ}
```


***

## How to create PetaLinux project from scratch

```shell-session
$ export PRJ=petalinux

# Create project
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.

# Kernel config
$ petalinux-create -p ${PRJ} -t modules --name dpu --enable

# u-boot config
$ petalinux-config -p ${PRJ} -c u-boot

# rootfs config
$ petalinux-config -p ${PRJ} -c rootfs

# 
$ petalinux-create -p ${PRJ} -t modules --name led-brightness --enable
$ petalinux-create -p ${PRJ} -t modules --name wilc --enable

# Build
$ petalinux-build -p ${PRJ}
```
