# Embedded platform

- Vitis Embedded Platform

***

## Standalone application

### Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
```

### Create BOOT.bin

```shell-session
$ xsct create_app.tcl
$ sdcard_gen \
--xpfm _application/ultra96/export/ultra96/ultra96.xpfm \
--sys_config ultra96 \
--bif _application/system.bif \
--bitstream _application/hello_world/_ide/bitstream/ultra96.bit \
--elf _application/hello_world/Release/hello_world.elf,psu_cortexa53_0 \
--output _application
```

### Run

- Copy the contents of __\_application/sd\_card__ directory to SD card

***

## Create Linux platform

### Build PetaLinux project

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c rootfs
$ petalinux-build -p ${PRJ}

# Generate BOOT.bin
$ petalinux-package -p ${PRJ} --boot --format BIN \
--fsbl ${PRJ}/images/linux/zynqmp_fsbl.elf \
--u-boot ${PRJ}/images/linux/u-boot.elf \
--pmufw ${PRJ}/images/linux/pmufw.elf \
--fpga ${PRJ}/project-spec/hw-description/ultra96.bit \
--atf ${PRJ}/images/linux/bl31.elf
```

### Generate platform

```shell-session
$ xsct create_pfm.tcl
```

- Now, the platform is in __\_pfm/u96_emb/export/__
