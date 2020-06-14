# Application Acceleration Platform

- Vitis Application Acceleration Platform

***

## Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
```

## Create Linux

- Create PetaLinux project

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.
$ petalinux-config -p ${PRJ} -c u-boot
```

- Add following content to _petalinux/project-spec/meta-user/conf/user-rootfsconfig_

```text
CONFIG_xrt
CONFIG_xrt-dev
CONFIG_zocl
CONFIG_opencl-clhpp-dev
CONFIG_opencl-headers-dev
CONFIG_packagegroup-petalinux-opencv
```

- Edit device tree (_petalinux/project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi_)

```text
&amba {
    zyxclmm_drm {
        compatible = "xlnx,zocl";
        status = "okay";
    };
};
```

- Build

```shell-session
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c rootfs
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk
```

## Generate platform

```shell-session
$ xsct create_pfm.tcl
```

- Now, the platform is in ``_pfm/u96_accel/export/``

***

## Build hello world application

- Get source

```shells-session
$ git clone https://github.com/Xilinx/Vitis_Accel_Examples.git
$ cd Vitis_Accel_Examples/hello_world/
```

- Build for HW

```shell-session
$ export XILINX_XRT=/opt/xilinx/xrt
$ make sd_card TARGET=hw DEVICE=u96_accel HOST_ARCH=aarch64 SYSROOT=~/ultra96-vitis/_sdk/sysroots/aarch64-xilinx-linux/
```

- Run

```shell-session
root@ultra96:/media/card# XILINX_XRT=/usr ./init.sh 
[  391.103730] [drm] Pid 2476 opened device
[  391.107701] [drm] Pid 2476 closed device
[  391.111803] [drm] Pid 2476 opened device
Found Platform
Platform Name: Xilinx
INFO: Reading ./build_dir.hw.u96_accel/vadd.xclbin
Loading: './build_dir.hw.u96_accel/vadd.xclbin'
Trying to program device[0]: edge
[  391.162020] [drm] The XCLBIN already loaded. Don't need to reload.
[  391.163483] [drm] Reconfiguration not supported
Device[0]: program successful!
[  391.181867] [drm] User buffer is not physical contiguous
[  391.187189] [drm] zocl_free_userptr_bo: obj 0x0000000022a5a553
[  391.188519] [drm] User buffer is not physical contiguous
[  391.199656] [drm] zocl_free_userptr_bo: obj 0x00000000fa96b8cb
[  391.199990] [drm] User buffer is not physical contiguous
TEST PASSED
[  391.211122] [drm] zocl_free_userptr_bo: obj 0x0000000061161219
[  391.312841] [drm] Pid 2476 closed device
```

***

## Reference

- UG1393: Vitis Unified Software Platform Documentation - Application Acceleration Development (v2019.2)
