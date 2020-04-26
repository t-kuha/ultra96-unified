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

# Copy the product for platform generation
$ mkdir _image
$ cp ${PRJ}/images/linux/image.ub _image/
```

## Generate platform

```shell-session
$ xsct create_pfm.tcl
```

- Now, the platform is in ``_pfm/u96v2_accel/export``

***

## Vector Add application

- Run

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
