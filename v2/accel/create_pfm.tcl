# Create acceleration platform

platform create -name {u96v2_accel} -hw {ultra96v2.xsa} -no-boot-bsp -out {_pfm}
platform write
platform active {u96v2_accel}

# Add sysroot??
domain create -name xrt -os linux -proc psu_cortexa53
domain active xrt
domain config -bif {src/linux.bif}
domain config -boot {petalinux/images/linux}
domain config -image {_image}
domain config -qemu-data {petalinux/images/linux}
domain config -qemu-args {src/qemu_args.txt}
domain config -pmuqemu-args {src/pmu_args.txt}
platform write

platform generate

