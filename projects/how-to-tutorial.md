# Building Vitis Tutorial for Ultra96

***

## My First Program

```shell-session
# You can add "PROFILE=yes" to profile the application
$ make all TARGET=hw DEVICE=u96_accel VER=host_cpp CXX=aarch64-linux-gnu-g++ \
opencl_CXXFLAGS="-I/opt/xilinx/sysroot/mpsoc/sysroots/aarch64-xilinx-linux/usr/include" \
opencl_LDFLAGS="--sysroot=/opt/xilinx/sysroot/mpsoc/sysroots/aarch64-xilinx-linux -lOpenCL -lpthread"
```
