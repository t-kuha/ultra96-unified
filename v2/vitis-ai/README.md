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

## Build reference design

```shell-session
# download reference design source
$ wget https://www.xilinx.com/bin/public/openDownload?filename=DPUCZDX8G.tar.gz -O DPUCZDX8G.tar.gz
$ tar xf DPUCZDX8G.tar.gz
```

- modify source

  - line 37 (change config file name to "prj_config_1dpu"):

  ```makefile
  XOCC_OPTS = -t ${TARGET} --platform ${SDX_PLATFORM} --save-temps --config ${DIR_PRJ}/config_file/prj_config_1dpu
  ```

  - line 113 (use "--package.no_image" option):
  ```
  v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p $(BUILD_DIR)/$(BUILD_DIR).xclbin -o $(BUILD_DIR)/dpu.xclbin --package.no_image
  ```

- start building HW

```shell-session
$ export SDX_PLATFORM=$(pwd)/_pfm/u96v2_vai/export/u96v2_vai/u96v2_vai.xpfm
$ cd DPUCZDX8G/prj/Vitis/
$ make all KERNEL=DPU DEVICE=u96v2
# copy the contents of "sd_card" into SD card
```

- build SW app

```shell-session
$ . <SDK installation path>/environment-setup-cortexa72-cortexa53-xilinx-linux
$ cd DPUCZDX8G/app/samples/
$ . ./build.sh
# copy a.out into SD card
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

# Build project
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk
```

***

## References

- [How to shut down the Ultra96 V1 or V2 boards directly](https://www.xilinx.com/support/answers/76583.html)

- [Why do U-boot and the Kernel not show the current build timestamp](https://www.xilinx.com/support/answers/76559.html)
