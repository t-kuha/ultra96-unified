SRC_URI += "file://bsp.cfg"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://fix_uart_drv.patch \
    "
