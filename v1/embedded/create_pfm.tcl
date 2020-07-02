# 
# Create embedded platform for Ultra96
# 

set OUT_DIR     _pfm
set IMG_DIR     _img

# Remove existing directory
file delete -force ${OUT_DIR}
file delete -force ${IMG_DIR}
# # Remove existing directory
# file delete -force ${OUT_DIR}

# Copy necessary files
file mkdir ${IMG_DIR}
file copy petalinux/images/linux/boot.scr ${IMG_DIR}
file copy petalinux/images/linux/image.ub ${IMG_DIR}

platform create -name u96_emb -hw ultra96.xsa -out ${OUT_DIR} -proc psu_cortexa53 -os linux
platform write

# Domain - Linux
domain active linux_domain

domain config -bif {src/linux.bif}
domain config -boot {petalinux/images/linux/}
domain config -image ${IMG_DIR}
platform write

# Domain - standalone (APU)
domain create -name {apu_standalone} -os {standalone} -proc {psu_cortexa53_0} -display-name {standalone on psu_cortexa53_0} -desc {standalone_domain} -runtime {cpp}
platform write

domain active apu_standalone
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1
bsp regenerate

domain active zynqmp_fsbl
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1
bsp regenerate

domain active zynqmp_pmufw
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1
bsp regenerate

# Domain - standalone (RPU)
domain create -name {rpu_standalone} -os {standalone} -proc {psu_cortexr5_0} -display-name {standalone on psu_cortexr5_0} -desc {rpu_domain} -runtime {cpp}
platform write

domain active rpu_standalone
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1
bsp regenerate

# Generate platform
platform generate -domains linux_domain,apu_standalone,rpu_standalone
