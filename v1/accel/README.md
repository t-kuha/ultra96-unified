# Application Acceleration Platform

- Vitis Application Acceleration Platform

***

## Clock settings

- Default clock is No.2 (200 MHz)

| No. | Speed [MHz] |
|----:|------------:|
|   0 |         100 |
|   1 |         150 |
|   2 |         200 |
|   3 |         250 |
|   4 |         300 |

***

## Create hardware

```shell-session
$ vivado -mode batch -source create_xsa.tcl
```

## Create Linux

- Build PetaLinux project

```shell-session
$ export PRJ=petalinux

# Make necessary configuration
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
$ make sd_card TARGET=hw DEVICE=u96_accel HOST_ARCH=aarch64 SYSROOT=<path to sysroot>
```

- Run

```shell-session
root@u96_accel:~# /media/card/host /media/card/build_dir.hw.u96_accel/vadd.xclbin
[  356.846207] [drm] Pid 2382 opened device
[  356.850226] [drm] Pid 2382 closed device
[  356.854501] [drm] Pid 2382 opened device
Found Platform
Platform Name: Xilinx
INFO: Reading /media/card/build_dir.hw.u96_accel/vadd.xclbin
Loading: '/media/card/build_dir.hw.u96_accel/vadd.xclbin'
Trying to program device[0]: edge
[  356.899701] [drm] The XCLBIN already loaded. Don't need to reload.
[  356.901205] [drm] Reconfiguration not supported
Device[0]: program successful!
[  356.919410] [drm] User buffer is not physical contiguous
[  356.924738] [drm] zocl_free_userptr_bo: obj 0x00000000f3633429
[  356.925842] [drm] User buffer is not physical contiguous
[  356.936985] [drm] zocl_free_userptr_bo: obj 0x00000000abbc9701
[  356.937312] [drm] User buffer is not physical contiguous
TEST PASSED
[  356.948459] [drm] zocl_free_userptr_bo: obj 0x000000000c5a6304
[  356.962986] [drm] Pid 2382 closed device
```

***

## Reference

- UG1393: Vitis Unified Software Platform Documentation - Application Acceleration Development (v2019.2)
