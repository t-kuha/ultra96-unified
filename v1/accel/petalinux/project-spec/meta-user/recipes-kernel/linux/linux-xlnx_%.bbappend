FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " file://bsp.cfg"
KERNEL_FEATURES:append = " bsp.cfg"
SRC_URI += "file://user_2023-11-02-12-38-00.cfg \
            file://user_2023-11-12-05-00-00.cfg \
            file://user_2023-11-17-13-35-00.cfg \
            "
