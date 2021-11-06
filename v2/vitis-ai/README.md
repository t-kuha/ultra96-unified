# Building Vitis AI platform

- Vitis AI version: 1.3

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
$ git clone https://github.com/Xilinx/Vitis-AI.git -b v1.3
$ cp -R Vitis-AI/dsa/DPU-TRD/ . 
```

- Copy config files

```shell-session
$ cp prj_config  DPU-TRD/prj/Vitis/config_file/
$ cp dpu_conf.vh DPU-TRD/prj/Vitis/
```

- Edit ``DPU-TRD/prj/Vitis/Makefile`` as follows:

  ```diff
  @@ -70,9 +70,9 @@ binary_container_1/dpu.xclbin: $(kernel_xo)
          v++ $(XOCC_OPTS) -l --temp_dir binary_container_1 --log_dir binary_container_1/logs --remote_ip_cache binary_container_1/ip_cache -o "$@" $(+)
   
   package:
  -       v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p binary_container_1/dpu.xclbin  -o dpu.xclbin --package.out_dir binary_container_1 --package.rootfs $(EDGE_COMMON_SW)/rootfs.ext4 --package.sd_file $(EDGE_COMMON_SW)/Image 
  -       cp ./binary_*/link/vivado/vpl/prj/prj*/sources_1/bd/*/hw_handoff/*.hwh ./binary_*/sd_card
  -       cp ./binary_*/link/vivado/vpl/prj/prj.gen/sources_1/bd/*/ip/*_DPUCZDX8G_1_0/arch.json ./binary_*/sd_card
  +       v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p binary_container_1/dpu.xclbin  -o dpu.xclbin --package.no_image
  +       cp ./binary_*/link/vivado/vpl/prj/prj*/sources_1/bd/*/hw_handoff/*.hwh ./sd_card
  +       cp ./binary_*/link/vivado/vpl/prj/prj.gen/sources_1/bd/*/ip/*_DPUCZDX8G_1_0/arch.json ./sd_card
   
   clean:
          ${RM} *.o *.elf *.log *.jou sample* v++* *.xclbin *.xclbin*
  ```

- Build

```shell-session
$ export SDX_PLATFORM=$(pwd)/_pfm/u96v2_vai/export/u96v2_vai/u96v2_vai.xpfm

$ cd DPU-TRD/prj/Vitis/
$ make KERNEL=DPU DEVICE=u96
# or to build with the SoftMax core...
$ make KERNEL=DPU_SM DEVICE=u96
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

# Show actual build time of Kernel & u-boot
$ petalinux-build -p ${PRJ} -c linux-xlnx -x cleansstate
$ petalinux-build -p ${PRJ} -c u-boot-xlnx -x cleansstate

# Build project
$ petalinux-build -p ${PRJ}

# Generate SDK
$ petalinux-build -p ${PRJ} --sdk
```
