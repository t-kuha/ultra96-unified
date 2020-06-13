FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://fix_u96v2_pwrseq_simple.patch \
    file://fix_uart_drv.patch \
    file://bsp.cfg \
    "
