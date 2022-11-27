# NOTE: .patch not accepted? / modify source directly before configuration
# FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
# SRC_URI += " \
#     file://0001-update-shutdown-state.patch \
# "

do_configure:prepend() {
    sed -i 's/^\(#define\s\+PMU_MIO_INPUT_PIN_VAL\).*/\1 (1U)/' ${S}/lib/sw_apps/zynqmp_pmufw/src/xpfw_config.h
    sed -i 's/^\(#define\s\+BOARD_SHUTDOWN_PIN_VAL\).*/\1 (1U)/' ${S}/lib/sw_apps/zynqmp_pmufw/src/xpfw_config.h
    sed -i 's/^\(#define\s\+BOARD_SHUTDOWN_PIN_STATE_VAL\).*/\1 (1U)/' ${S}/lib/sw_apps/zynqmp_pmufw/src/xpfw_config.h
}

# pmu-firmware_%.bbappend content
ULTRA96_VERSION = "2"
YAML_COMPILER_FLAGS:append:ultra96-zynqmp = "-DENABLE_MOD_ULTRA96 -DENABLE_SCHEDULER -DENABLE_DIRECT_POWEROFF_ULTRA96"
YAML_COMPILER_FLAGS:append:ultra96-zynqmp = "${@bb.utils.contains('ULTRA96_VERSION', '2', ' -DULTRA96_VERSION=2', ' -DULTRA96_VERSION=1', d)}"
