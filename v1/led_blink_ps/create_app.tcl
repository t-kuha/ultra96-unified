# Create standalone application & SD card data
# 
# Usage: xsct create_app.tcl
# 

set PRJ_NAME    led_blink_ps
set PFM_NAME    u96_led
set SRC_DIR     src

set SCRIPT_DIR [ file dirname [ file normalize [ info script ] ] ]

set WORKSPACE   "${SCRIPT_DIR}/_app"

# Remove existing directory
file delete -force ${WORKSPACE}

setws ${WORKSPACE}

# Register the custom platform
repo -set ${WORKSPACE}
repo -add-platforms "${SCRIPT_DIR}/_pfm/${PFM_NAME}/export/${PFM_NAME}"

# Use command below to check if the target platform is added to the repo
# repo -platforms

app create -name ${PRJ_NAME} -platform ${PFM_NAME} -domain standalone_domain

# Replace source
exec rm ${WORKSPACE}/${PRJ_NAME}/src/helloworld.c
exec cp ${SRC_DIR}/helloworld.c ${WORKSPACE}/${PRJ_NAME}/src/helloworld.c

# Build .elf
app config -name ${PRJ_NAME} -set build-config release
app build -name "${PRJ_NAME}"

# Create SD card data
sysproj build -name "${PRJ_NAME}_system"
