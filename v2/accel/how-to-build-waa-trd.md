# How to build WAA-TRD (Whole Application Acceleration - Target Reference Design)

- Prerequisite:
  - Vitis platform
  - PetaLinux SDK

## 1. Get source

```shell-session
$ git clone https://github.com/Xilinx/Vitis-AI.git -b v1.3.2
```

## 2. Build HW

- First, export some environment variables so that Vitis can locate the generated custom platform:

```shell-session
$ export PLATFORM_REPO_PATHS=<directory containing generated platform>
$ export SDX_PLATFORM=u96v2_vai
$ . <Vitis installation path>/Vitis/2020.2/settings64.sh
```

- Do some preparation:

```shell-session
# Copy DPU configuration files
$ cp prj_config Vitis-AI/dsa/WAA-TRD/proj/build/classification-pre_DPUv2/config_file
$ cp dpu_conf.vh Vitis-AI/dsa/WAA-TRD/proj/build/classification-pre_DPUv2/

$ cd Vitis-AI/dsa/WAA-TRD/proj/build/classification-pre_DPUv2/
```

- Replace ``DEVICE=zcu102`` as ``DEVICE=u96v2_vai`` in __build_classification_pre.sh__ & start building HW

```shell-session
$ ./build_classification_pre.sh
```

- SD card image will be generated in ``Vitis-AI/dsa/WAA-TRD/proj/build/classification-pre_DPUv2/binary_container_1/sd_card``

## 3. Build application

```shell-session
$ . <path to extracted PetaLinux SDK>/environment-setup-aarch64-xilinx-linux

$ cd ../../../app/resnet50_waa
$ ./build.sh
```

- __resnet50_waa__ will be generated

## 4. Deploy ResNet50 model for Ultra96

```shell-session
# Get ResNet50 model (Caffe version)
$ wget https://www.xilinx.com/bin/public/openDownload?filename=cf_resnet50_imagenet_224_224_7.7G_1.3.zip -O cf_resnet50_imagenet_224_224_7.7G_1.3.zip
$ unzip cf_resnet50_imagenet_224_224_7.7G_1.3.zip

# Deploy model (generate .xmodel file)
$ cd cf_resnet50_imagenet_224_224_7.7G_1.3
$ vai_c_caffe -p quantized/deploy.prototxt \
-c quantized/deploy.caffemodel -n resnet50 -o deploy \
-a <path to cloned Vitis-AI repo>/dsa/WAA-TRD/proj/build/classification-pre_DPUv2/binary_container_1/sd_card/arch.json
```

- __resnet50.xmodel__ will be generated in __deploy__

## 5. Run

- Download sample images from [old Vitis-AI repo](https://github.com/Xilinx/Vitis-AI/tree/v1.2.1/DPU-TRD/app/img)

- Copy the following files to micro SD card:
  - sd_card/*
  - resnet50_waa
  - words.txt
  - resnet50.xmodel
  - img/*

- Then run on Ultra96:

```shell-session
root@u96v2_vai:~# ./resnet50_waa resnet50.xmodel 
WARNING: Logging before InitGoogleLogging() is written to STDERR
I0127 17:04:58.812940  1159 main.cc:305] create running for subgraph: subgraph_conv1
Found Platform
Platform Name: Xilinx
INFO: Reading /usr/lib/dpu.xclbin
Loading: '/usr/lib/dpu.xclbin'

Image : ./img/jinrikisha-911722.JPEG
top[0] prob = 0.569061  name = tricycle, trike, velocipede
top[1] prob = 0.345153  name = jinrikisha, ricksha, rickshaw
top[2] prob = 0.028332  name = bicycle-built-for-two, tandem bicycle, tandem
top[3] prob = 0.004923  name = Model T
top[4] prob = 0.004923  name = cornet, horn, trumpet, trump

Image : ./img/irishterrier-696543.JPEG
top[0] prob = 0.529367  name = Border terrier
top[1] prob = 0.250055  name = Brabancon griffon
top[2] prob = 0.118118  name = Irish terrier
top[3] prob = 0.033841  name = cairn, cairn terrier
top[4] prob = 0.015986  name = affenpinscher, monkey pinscher, monkey dog

Image : ./img/greyfox-672194.JPEG
top[0] prob = 0.453187  name = grey fox, gray fox, Urocyon cinereoargenteus
top[1] prob = 0.453187  name = red fox, Vulpes vulpes
top[2] prob = 0.028971  name = kit fox, Vulpes macrotis
top[3] prob = 0.013685  name = coyote, prairie wolf, brush wolf, Canis latrans
top[4] prob = 0.013685  name = red wolf, maned wolf, Canis rufus, Canis niger

Image : ./img/bellpeppe-994958.JPEG
top[0] prob = 0.990457  name = bell pepper
top[1] prob = 0.004048  name = acorn squash
top[2] prob = 0.002455  name = cucumber, cuke
top[3] prob = 0.000903  name = zucchini, courgette
top[4] prob = 0.000703  name = strawberry
```
