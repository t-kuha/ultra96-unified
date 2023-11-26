FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " file://bsp.cfg"
KERNEL_FEATURES:append = " bsp.cfg"
SRC_URI += "file://user_2023-11-12-11-45-00.cfg \
            file://user_2023-11-23-06-53-00.cfg \
            "

