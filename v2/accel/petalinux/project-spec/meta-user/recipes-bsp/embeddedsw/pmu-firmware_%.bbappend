FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://0001-update-shutdown-state.patch \
"

# pmu-firmware_%.bbappend content
ULTRA96_VERSION = "2"

YAML_COMPILER_FLAGS_append_ultra96 = " -DENABLE_MOD_ULTRA96 -DENABLE_SCHEDULER -DENABLE_DIRECT_POWEROFF_ULTRA96"
