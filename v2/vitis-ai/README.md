# Building Vitis AI platform

- Vitis AI v1.1

***

- Clone Vitis AI repo:

```shell-session
$ git clone https://github.com/Xilinx/Vitis-AI.git
$ cd Vitis-AI
$ git checkout v1.1
$ cd ..
$ cp -R Vitis-AI/DPU-TRD/ . 
```

- Copy config files

```shell-session
$ cp prj_config  DPU-TRD/prj/Vitis/config_file/
$ cp dpu_conf.vh DPU-TRD/prj/Vitis/
```

- Edit _DPU-TRD/prj/Vitis/Makefile_: Add ``--jobs $(shell nproc)`` to ``XOCC_OPTS = ...`` to speedup synthesis.

- Build

```shell-session
$ export SDX_PLATFORM=<path to .xpfm>

$ cd DPU-TRD/prj/Vitis/
$ make KERNEL=DPU DEVICE=u96
# or...
$ make KERNEL=DPU_SM DEVICE=u96
```
