# 
# DNNDK from source
# Vitis AI v1.2

SUMMARY = "DNNDK"
DESCRIPTION = "Vitis AI DNNDK runtime"

LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LICENSE;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Caffe version to use
PV = "1.2"
PR = "r0"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = "\
	git://github.com/Xilinx/Vitis-AI.git;protocol=https;tag=v${PV} \
	"

S = "${WORKDIR}/git/"

SRC_DNNDK = 'vitis_ai_dnndk_src'

# Dependencies
DEPENDS = "xrt "


do_unpack_append(){
    # Move vitis_ai_dnndk_src to top
    import os
    import shutil
    shutil.rmtree(os.path.join(d.getVar('WORKDIR'), d.getVar('SRC_DNNDK')))
    shutil.move(os.path.join(d.getVar('S'), 'mpsoc', d.getVar('SRC_DNNDK')), os.path.join(d.getVar('WORKDIR')))
}


do_compile () {
    cd ${WORKDIR}/${SRC_DNNDK}
    oe_runmake
}

# do_install () {
#     rm -rf ${D}
#     mkdir -p ${D}
#     cp -R ${S}/distribute/* ${D}
# }
