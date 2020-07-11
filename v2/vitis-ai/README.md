# Building Vitis AI platform

- Vitis AI version: 1.2

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
$ git checkout v1.2
$ cd ..
$ cp -R Vitis-AI/DPU-TRD/ . 
```

- Copy config files

```shell-session
$ cp prj_config  DPU-TRD/prj/Vitis/config_file/
$ cp dpu_conf.vh DPU-TRD/prj/Vitis/
```

- Edit ``DPU-TRD/prj/Vitis/Makefile`` as follows: 

  ```diff
  #EDGE_COMMON_SW:= /proj/rdi/staff/jiaz/scout/platfrom201/xilinx_zcu102_base_202010_1/sw/xilinx_zcu102_base_202010_1/xrt/image
  #SDX_PLATFORM = /proj/xcdhdstaff2/tianfang/2020.1/0518/102/platform_repo/xilinx_zcu102_base_202010_1/export/xilinx_zcu102_base_202010_1/xilinx_zcu102_base_202010_1.xpfm
 
  -XOCC_OPTS = -t ${TARGET} --platform ${SDX_PLATFORM} --save-temps --config ${DIR_PRJ}/config_file/prj_config_102_3dpu_LPD --xp param:compiler.userPostSysLinkOverlayTcl=${DIR_PRJ}/syslink/strip_interconnects.tcl 
  +XOCC_OPTS = -t ${TARGET} --platform ${SDX_PLATFORM} --save-temps --config ${DIR_PRJ}/config_file/prj_config --xp param:compiler.userPostSysLinkOverlayTcl=${DIR_PRJ}/syslink/strip_interconnects.tcl 
  dpu_HDLSRCS=kernel_xml/dpu/kernel.xml\
             scripts/package_dpu_kernel.tcl\
             scripts/gen_dpu_xo.tcl\
  ```

  ```diff
        v++ $(XOCC_OPTS) -l --temp_dir binary_container_1 --log_dir binary_container_1/logs --remote_ip_cache binary_container_1/ip_cache -o "$@" $(+)
 
  package:
  -       v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p binary_container_1/dpu.xclbin --package.out_dir binary_container_1 --package.rootfs $(EDGE_COMMON_SW)/rootfs.ext4 --package.sd_file $(EDGE_COMMON_SW)/Image 
  +       v++ -t ${TARGET} --platform ${SDX_PLATFORM} -p binary_container_1/dpu.xclbin --package.out_dir binary_container_1 --package.no_image 
        cp ./binary_*/link/vivado/vpl/prj/prj.srcs/sources_1/bd/*/hw_handoff/*.hwh ./binary_*/sd_card
 
  clean:
  ```

- Build

```shell-session
$ export SDX_PLATFORM=$(pwd)/_pfm/u96v2_vai/export/u96v2_vai/u96v2_vai.xpfm

$ cd DPU-TRD/prj/Vitis/
$ make KERNEL=DPU DEVICE=u96
# or to build with the SoftMax core...
$ make KERNEL=DPU_SM DEVICE=u96
```
