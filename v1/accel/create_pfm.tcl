#
# Create acceleration platform
#

set OUT_DIR     _pfm
set BOOT_DIR    _boot
set IMG_DIR     _img

# Remove existing directory
file delete -force ${OUT_DIR}
file delete -force ${BOOT_DIR}
file delete -force ${IMG_DIR}

# Copy necessary files
file mkdir ${BOOT_DIR}
file copy petalinux/images/linux/bl31.elf        ${BOOT_DIR}
file copy petalinux/images/linux/pmufw.elf       ${BOOT_DIR}
file copy petalinux/images/linux/system.dtb      ${BOOT_DIR}
file copy petalinux/images/linux/u-boot-dtb.elf  ${BOOT_DIR}/u-boot.elf
file copy petalinux/images/linux/zynqmp_fsbl.elf ${BOOT_DIR}

file mkdir ${IMG_DIR}
file copy petalinux/images/linux/boot.scr ${IMG_DIR}
file copy petalinux/images/linux/image.ub ${IMG_DIR}

platform create -name {u96_accel} -hw {ultra96.xsa} -no-boot-bsp -out ${OUT_DIR}
platform write
platform active {u96_accel}

domain create -name xrt -os linux -proc psu_cortexa53
domain active xrt
domain config -generate-bif
domain config -boot ${BOOT_DIR}
domain config -sd-dir ${IMG_DIR}
domain config -qemu-data {petalinux/images/linux}
platform write

platform generate
