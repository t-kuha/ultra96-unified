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

- Now, the platform is in ``_pfm/u96v2_accel/export``

***

## Vector Add application

- Run result

```shell-session
root@ultra96-v2-acc:~# export XILINX_XRT=/usr
root@ultra96-v2-acc:~# ./vadd.exe binary_container_1.xclbin 
[   95.604947] [drm] Pid 2435 opened device
[   95.608905] [drm] Pid 2435 closed device
[   95.613015] [drm] Pid 2435 opened device
Loading: 'binary_container_1.xclbin'
[   95.652075] [drm] The XCLBIN already loaded. Don't need to reload.
[   95.653538] [drm] Reconfiguration not supported
TEST PASSED
[   95.675023] [drm] Pid 2435 closed device
```

***

## Reference

- UG1393: Vitis Unified Software Platform Documentation - Application Acceleration Development (v2019.2)
