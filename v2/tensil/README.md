# tensil

## 1. set up environment

- Get ZULU JDK (v11.0.17) & mill

```shell
$ wget https://cdn.azul.com/zulu/bin/zulu11.60.19-ca-jdk11.0.17-linux_x64.tar.gz
$ tar xf zulu11.60.19-ca-jdk11.0.17-linux_x64.tar.gz
$ export JAVA_HOME=$(pwd)/zulu11.60.19-ca-jdk11.0.17-linux_x64
$ export PATH=$(pwd)/zulu11.60.19-ca-jdk11.0.17-linux_x64/bin:${PATH}
$ sudo sh -c "curl -L https://github.com/com-lihaoyi/mill/releases/download/0.10.9/0.10.9 > /usr/local/bin/mill && chmod +x /usr/local/bin/mill"
```

- Get model data

```shell
# $ git clone https://github.com/tensil-ai/tensil-models.git
$ wget https://github.com/tensil-ai/tensil-models/archive/main.tar.gz
$ tar xf main.tar.gz
$ mv tensil-models-main models
```

- Get tensil source

```bash
$ git clone https://github.com/tensil-ai/tensil.git -b v1.0.15
$ pushd tensil
$ ./mill 'rtl.assembly'
$ ./mill 'compiler.assembly'
$ ./mill 'emulator.assembly'
$ ./mill 'web.assembly'

$ sudo mkdir /opt/tensil
$ sudo cp out/rtl/assembly.dest/out.jar /opt/tensil/rtl.jar
$ sudo cp out/compiler/assembly.dest/out.jar /opt/tensil/compiler.jar
$ sudo cp out/emulator/assembly.dest/out.jar /opt/tensil/emulator.jar
$ sudo cp out/web/assembly.dest/out.jar /opt/tensil/web.jar
$ popd

$ export PATH=${PATH}:$(pwd)/tensil/docker/bin
```

## 2. Build HW


```shell
$ tensil rtl -a tensil/arch/ultra96v2.tarch -s true -d 128
```

- result:

```shell-session
-----------------------------------------------------------------------
RTL SUMMARY
-----------------------------------------------------------------------
Data type:                                      FP16BP8   
Array size:                                     16        
DRAM0 memory size (vectors/scalars/bits):       2,097,152 33,554,432 21
DRAM1 memory size (vectors/scalars/bits):       2,097,152 33,554,432 21
Local memory size (vectors/scalars/bits):       20,480    327,680    15
Accumulator memory size (vectors/scalars/bits): 4,096     65,536     12
Stride #0 size (bits):                          3         
Stride #1 size (bits):                          3         
Operand #0 size (bits):                         24        
Operand #1 size (bits):                         24        
Operand #2 size (bits):                         16        
Instruction size (bytes):                       9         
-----------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------
ARTIFACTS
------------------------------------------------------------------------------------------------------------
Verilog bram_dp_256x4096:   /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/bram_dp_256x4096.v
Verilog bram_dp_256x20480:  /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/bram_dp_256x20480.v
Verilog top_ultra96v2:      /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/top_ultra96v2.v
Driver parameters C header: /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/architecture_params.h
```

```shell
$ mkdir rtl
$ mv bram_dp_* rtl/
$ mv architecture_params.h rtl/
$ mv top_* rtl/
$ mv firrtl_black_box_resource_files.f rtl/
```

- Generate bitstream

```shell
$ vivado -notrace -nojournal -mode batch -source create_xsa.tcl
```

## 3. Generate model

```bash
$ tensil compile \
-a tensil/arch/ultra96v2.tarch \
-m models/yolov4_tiny_192.onnx \
-o "model/conv2d_17/BiasAdd:0,model/conv2d_20/BiasAdd:0" \
-s true
```

- result:

```shell-session
--------------------------------------------------------------------------------------------------
COMPILER SUMMARY
--------------------------------------------------------------------------------------------------
Model:                                                yolov4_tiny_192_onnx_ultra96v2 
Data type:                                            FP16BP8                        
Array size:                                           16                             
DRAM0 memory size (vectors/scalars/bits):             2,097,152                      33,554,432 21
DRAM1 memory size (vectors/scalars/bits):             2,097,152                      33,554,432 21
Local memory size (vectors/scalars/bits):             20,480                         327,680    15
Accumulator memory size (vectors/scalars/bits):       4,096                          65,536     12
Stride #0 size (bits):                                3                              
Stride #1 size (bits):                                3                              
Operand #0 size (bits):                               24                             
Operand #1 size (bits):                               24                             
Operand #2 size (bits):                               16                             
Instruction size (bytes):                             9                              
DRAM0 maximum usage (vectors/scalars):                55,296                         884,736    
DRAM0 aggregate usage (vectors/scalars):              130,464                        2,087,424  
DRAM1 maximum usage (vectors/scalars):                378,669                        6,058,704  
DRAM1 aggregate usage (vectors/scalars):              378,669                        6,058,704  
Local memory maximum usage (vectors/scalars):         19,733                         315,728    
Local memory aggregate usage (vectors/scalars):       841,914                        13,470,624 
Accumumator memory maximum usage (vectors/scalars):   4,095                          65,520     
Accumumator memory aggregate usage (vectors/scalars): 207,752                        3,324,032  
Number of layers:                                     25                             
Maximum number of stages:                             8                              
Maximum number of partitions:                         10                             
Execution latency (MCycles):                          5.051                          
Aggregate latency (MCycles):                          5.056                          
Execution energy (MUnits):                            864.097                        
Aggregate energy (MUnits):                            864.424                        
MAC efficiency (%):                                   51.841                         
Total number of instructions:                         691,677                        
Compilation time (seconds):                           173.278                        
True consts scalar size:                              6,054,190                      
Consts utilization (%):                               98.706                         
True MACs (MMAC):                                     670.349                        
MAC efficiency (%):                                   51.841                         
--------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
ARTIFACTS
-----------------------------------------------------------------------------------------------------------
Manifest:  /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/yolov4_tiny_192_onnx_ultra96v2.tmodel
Program:   /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/yolov4_tiny_192_onnx_ultra96v2.tprog
Constants: /media/imagingtechnerd/SSD_180GB/ultra96-unified/v2/tensil/yolov4_tiny_192_onnx_ultra96v2.tdata
-----------------------------------------------------------------------------------------------------------
```
