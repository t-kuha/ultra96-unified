# Create BOOT.bin (for standalone)
# 
# Usage: xsct create_boot_bin.tcl
# 
# Need to install board files in <SDK Installation Path>/data/boards/board_files
#
# Reference: UG1208
# 

set XSDK_DIR    _sdk
set HW_NAME     ultra96v2
set SRC_DIR     src
set PRJ_NAME    led_blink_pl

set SCRIPT_DIR [ file dirname [ file normalize [ info script ] ] ]

cd ${SCRIPT_DIR}

setws ${SCRIPT_DIR}/${XSDK_DIR}

# Create BSP
createhw -name bsp -hwspec ${XSDK_DIR}/${HW_NAME}_wrapper.hdf

# Create FSBL
createapp -name fsbl -app {Zynq MP FSBL} -hwproject bsp -proc psu_cortexa53_0 -os standalone

# Create PMU FW
createapp -name pmufw -app {ZynqMP PMU Firmware} -hwproject bsp -proc psu_pmu_0 -os standalone

# Create application
createapp -name ${PRJ_NAME} -app {Hello World} -hwproject bsp -proc psu_cortexa53_0 -os standalone

# Use UART1 as stdin & stdout 
configbsp -bsp fsbl_bsp stdin  "psu_uart_1"
configbsp -bsp fsbl_bsp stdout "psu_uart_1"
updatemss -mss ${XSDK_DIR}/fsbl_bsp/system.mss
regenbsp -bsp fsbl_bsp

configbsp -bsp pmufw_bsp stdin  "psu_uart_1"
configbsp -bsp pmufw_bsp stdout "psu_uart_1"
updatemss -mss ${XSDK_DIR}/pmufw_bsp/system.mss
regenbsp -bsp pmufw_bsp

configbsp -bsp ${PRJ_NAME}_bsp stdin  "psu_uart_1"
configbsp -bsp ${PRJ_NAME}_bsp stdout "psu_uart_1"
updatemss -mss ${XSDK_DIR}/${PRJ_NAME}_bsp/system.mss
regenbsp -bsp ${PRJ_NAME}_bsp

# Replace helloworld.c with led_blink.c
exec rm ${XSDK_DIR}/${PRJ_NAME}/${SRC_DIR}/helloworld.c
exec cp ${SRC_DIR}/helloworld.c ${XSDK_DIR}/${PRJ_NAME}/${SRC_DIR}/helloworld.c

# Build in release mode
configapp -app fsbl build-config release
configapp -app pmufw build-config release
configapp -app ${PRJ_NAME} build-config release

projects -build

# Generate BOOT.bin
exec bootgen -arch zynqmp -image ${SRC_DIR}/boot_bin_standalone.bif -w -o BOOT.bin
