# How to create PetaLinux project

## Create PetaLinux project

```shell-session
$ export PRJ=petalinux

# Create initial project
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=.

# Make necessary configuration
$ petalinux-config -p ${PRJ} -c u-boot
$ petalinux-config -p ${PRJ} -c kernel
$ petalinux-config -p ${PRJ} -c rootfs
```

## For acceleration platform

- Add following content to ``petalinux/project-spec/meta-user/conf/user-rootfsconfig``

```text
CONFIG_xrt
CONFIG_xrt-dev
CONFIG_zocl
CONFIG_opencl-clhpp-dev
CONFIG_opencl-headers-dev
CONFIG_packagegroup-petalinux-opencv
```

- Edit device tree ``petalinux/project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi``

```text
&amba {
    zyxclmm_drm {
        compatible = "xlnx,zocl";
        status = "okay";
    };
};
```

## Start build

```shell-session
$ petalinux-build -p ${PRJ}

# Generate SDK (optional)
$ petalinux-build -p ${PRJ} --sdk
```