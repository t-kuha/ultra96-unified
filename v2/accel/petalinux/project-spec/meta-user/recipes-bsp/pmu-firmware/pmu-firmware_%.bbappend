# pmu-firmware_%.bbappend content

# For Ultra96-V1 boards
# ULTRA96_VERSION = "1"

# For Ultra96-V2 boards
ULTRA96_VERSION = "2"

YAML_COMPILER_FLAGS:append:ultra96 = " -DENABLE_MOD_ULTRA96 -DENABLE_SCHEDULER -DENABLE_DIRECT_POWEROFF_ULTRA96"
