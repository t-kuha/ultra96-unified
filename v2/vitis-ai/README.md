# Building Vitis AI platform

- Vitis AI version: 1.1

***

## Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
```

## Create Linux

- Create PetaLinux project

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

## Create Vitis-AI platform

```shell-session
$ git clone https://github.com/Xilinx/Vitis-AI.git
$ cd Vitis-AI
$ git checkout v1.1
$ cd ..
$ cp -R Vitis-AI/DPU-TRD/ . 
```

- Copy config files

```shell-session
$ cp prj_config  DPU-TRD/prj/Vitis/config_file/
$ cp dpu_conf.vh DPU-TRD/prj/Vitis/
```

- Edit _DPU-TRD/prj/Vitis/Makefile_: Add ``--jobs $(shell nproc)`` to ``XOCC_OPTS = ...`` to speedup synthesis.

- Build

```shell-session
$ export SDX_PLATFORM=$(pwd)/_pfm/u96v2_vai/export/u96v2_vai/u96v2_vai.xpfm

$ cd DPU-TRD/prj/Vitis/
$ make KERNEL=DPU DEVICE=u96
# or to build with the SoftMax core...
$ make KERNEL=DPU_SM DEVICE=u96
```
