# Create embedded/standalone platform
# 
# Usage: xsct create_pfm.tcl
# 

set PFM_NAME    u96v2_led
set OUT_DIR     _pfm
set HW_NAME     ultra96v2

set SCRIPT_DIR [ file dirname [ file normalize [ info script ] ] ]

# Remove existing directory
file delete -force ${OUT_DIR}

# Start generating platform
platform create -name ${PFM_NAME} -hw "${SCRIPT_DIR}/${HW_NAME}.xsa" -out "${SCRIPT_DIR}/${OUT_DIR}" -arch {64-bit} -proc {psu_cortexa53_0} -os {standalone}
platform write

platform read "${SCRIPT_DIR}/${OUT_DIR}/${PFM_NAME}/platform.spr"
platform active ${PFM_NAME}

domain active standalone_domain
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1

domain active zynqmp_fsbl
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1

domain active zynqmp_pmufw
bsp config stdin psu_uart_1
bsp config stdout psu_uart_1

# Generate platform
platform write
platform generate
