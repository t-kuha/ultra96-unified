FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " file://bsp.cfg"
KERNEL_FEATURES:append = " bsp.cfg"
SRC_URI += "file://user_2022-06-19-11-27-00.cfg \
            file://user_2022-06-19-11-32-00.cfg \
            "

