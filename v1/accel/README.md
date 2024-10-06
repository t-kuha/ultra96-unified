# Building Vitis Application Acceleration Platform

***

## Create hardware

```shell-session
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl
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
```

## Generate platform

```shell-session
$ vitis -s create_vitis_platform.py
```

## Create vector addition app

```shell-session
$ IDE_ZYNQMP_SYSROOT=<path to sysroot directory> vitis -s create_vadd_app.py
```

- Copy the contents of ``_vitis-ws/vadd/build/hw/package/package/sd_card/`` into SD card

- Run

```shell-session
u96-accel:~$ ./vadd_host ./binary_container_1.xclbin                                                                   
[  168.487337] zocl-drm zyxclmm_drm: zocl_create_client: created KDS client for pid(759), ret: 0
[  168.496098] zocl-drm zyxclmm_drm: zocl_destroy_client: client exits pid(759)
INFO: Reading ./binary_container_1.xclbin
Loading: './binary_container_1.xclbin'
[  168.510813] zocl-drm zyxclmm_drm: zocl_create_client: created KDS client for pid(759), ret: 0
[  168.519448] zocl-drm zyxclmm_drm: zocl_destroy_client: client exits pid(759)
[  168.526768] zocl-drm zyxclmm_drm: zocl_create_client: created KDS client for pid(759), ret: 0
Trying to program device[0]: edge
[  168.555500] [drm] Loading xclbin a0719fee-1999-9a0b-a99f-2b36e95cbc42 to slot 0
[  168.555535] [drm] skip kind 29(AIE_RESOURCES) return code: -22
[  168.562907] [drm] found kind 8(IP_LAYOUT)
[  168.568748] [drm] skip kind 9(DEBUG_IP_LAYOUT) return code: -22
[  168.572759] [drm] skip kind 25(AIE_METADATA) return code: -22
[  168.578696] [drm] found kind 7(CONNECTIVITY)
[  168.584463] [drm] found kind 6(MEM_TOPOLOGY)
[  168.588943] [drm] Memory 0 is not reserved in device tree. Will allocate memory from CMA
[  168.601334] [drm] Memory 1 is not reserved in device tree. Will allocate memory from CMA
[  168.609459] [drm] Memory 2 is not reserved in device tree. Will allocate memory from CMA
[  168.617584] [drm] Memory 3 is not reserved in device tree. Will allocate memory from CMA
[  168.625707] [drm] Memory 4 is not reserved in device tree. Will allocate memory from CMA
[  168.633831] [drm] Memory 5 is not reserved in device tree. Will allocate memory from CMA
[  168.642065] cu_drv CU.7.auto:  ffff00000336f010 xrt_cu_intr_thread: CU[0] thread end, bad state 0
[  168.651203] cu_drv CU.7.auto: cu_remove: CU[0] removed
[  168.657036] zocl_irq_intc ZOCL_CU_INTC.6.auto: zocl_irq_intc_add: managing IRQ 64
[  168.664746] cu_drv CU.7.auto: cu_probe: CU[0] created
[  168.670130] cu_drv CU.7.auto:  ffff000007c6d010 xrt_cu_intr_thread: CU[0] start
[  168.670141] [drm] zocl_xclbin_read_axlf a0719fee-1999-9a0b-a99f-2b36e95cbc42 ret: 0
[  168.681161] [drm] bitstream a0719fee-1999-9a0b-a99f-2b36e95cbc42 locked, ref=1
[  168.688913] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_add_context: Client pid(759) add context Domain(65535) CU(0xffff)
 shared(true)
[  168.708276] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_del_context: Client pid(759) del context Domain(65535) CU(0xffff)
[  168.719254] [drm] bitstream a0719fee-1999-9a0b-a99f-2b36e95cbc42 unlocked, ref=0
[  168.725606] [drm] bitstream a0719fee-1999-9a0b-a99f-2b36e95cbc42 locked, ref=1
[  168.733050] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_add_context: Client pid(759) add context Domain(65535) CU(0xffff)
 shared(true)
Device[0]: program successful!
[  168.755628] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_add_context: Client pid(759) add context Domain(0) CU(0x0) shared
(true)
TEST PASSED
[  168.773830] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_del_context: Client pid(759) del context Domain(0) CU(0x0)
[  168.785475] zocl-drm zyxclmm_drm:  ffff000001e54410 kds_del_context: Client pid(759) del context Domain(65535) CU(0xffff)
[  168.796491] [drm] bitstream a0719fee-1999-9a0b-a99f-2b36e95cbc42 unlocked, ref=0
[  168.800996] zocl-drm zyxclmm_drm: zocl_destroy_client: client exits pid(759)
```

***

## Optional: how to create PetaLinux project from scratch

```shell-session
$ export PRJ=petalinux
$ petalinux-create -t project -n ${PRJ} --template zynqMP
$ petalinux-config -p ${PRJ} --get-hw-description=hw.xsa

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

- [Why do U-boot and the Kernel not show the current build timestamp](https://www.xilinx.com/support/answers/76559.html)

- [Debian/Ubuntu でKV260 で冷却ファンを制御する (その２)](https://qiita.com/ikwzm/items/f94748f5353271aab5ee)

- Wi-Fi firmware
  - wl18xx-fw-4.bin: [processor-firmware/ti-linux-firmware](https://git.ti.com/cgit/processor-firmware/ti-linux-firmware/log/ti-connectivity/wl18xx-fw-4.bin?h=ti-linux-firmware)
