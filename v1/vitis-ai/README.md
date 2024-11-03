# Building Vitis Application Acceleration Platform for Vitis AI

***

## Create hardware

```shell
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl
```

## Create PetaLinux project

```shell
$ export PRJ=petalinux
$ petalinux-config -p ${PRJ} --get-hw-description=hw.xsa

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

## Build reference design

```shell
# download reference design source
$ wget https://www.xilinx.com/bin/public/openDownload?filename=DPUCZDX8G.tar.gz -O DPUCZDX8G.tar.gz
$ tar xf DPUCZDX8G.tar.gz
```

- modify ``DPUCZDX8G/prj/Vitis/Makefile``

  - line 113 (use "--package.no_image" option):
  ```makefile
  v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p $(BUILD_DIR)/$(BUILD_DIR).xclbin -o $(BUILD_DIR)/dpu.xclbin --package.no_image
  cp ./binary_*/link/vivado/vpl/prj/prj*/sources_1/bd/*/hw_handoff/*.hwh ./sd_card
	cp ./binary_*/link/vivado/vpl/prj/prj.gen/sources_1/bd/*/ip/*_DPUCZDX8G_1_0/arch.json ./sd_card
  ```

- start building HW

```shell
$ export SDX_PLATFORM=$(pwd)/_pfm/u96_vai/export/u96_vai/u96_vai.xpfm
$ pushd DPUCZDX8G/prj/Vitis/
$ make all KERNEL=DPU DEVICE=u96
# copy the contents of "sd_card" into SD card
$ popd
```

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
