FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " file://bsp.cfg"
KERNEL_FEATURES:append = " bsp.cfg"
SRC_URI += "file://user_2022-05-07-05-58-00.cfg \
            file://user_2022-05-07-07-05-00.cfg \
            "

