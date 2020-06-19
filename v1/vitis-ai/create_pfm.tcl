#
# Create acceleration platform
#

set OUT_DIR     _pfm
set IMG_DIR     _img

# Remove existing directory
file delete -force ${OUT_DIR}
file delete -force ${IMG_DIR}

# Copy necessary files
file mkdir ${IMG_DIR}
file copy petalinux/images/linux/boot.scr ${IMG_DIR}
file copy petalinux/images/linux/image.ub ${IMG_DIR}

platform create -name {u96_vai} -hw {ultra96.xsa} -no-boot-bsp -out ${OUT_DIR}
platform write
platform active {u96_vai}

domain create -name xrt -os linux -proc psu_cortexa53
domain active xrt
domain config -bif {src/linux.bif}
domain config -boot {petalinux/images/linux}
domain config -image ${IMG_DIR}
domain config -qemu-data {petalinux/images/linux}
domain config -qemu-args {src/qemu_args.txt}
domain config -pmuqemu-args {src/pmu_args.txt}
platform write

platform generate

