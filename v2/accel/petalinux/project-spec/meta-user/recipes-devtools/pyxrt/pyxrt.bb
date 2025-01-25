# 
# 
# 
SUMMARY = "Run Time for AIE and FPGA based platforms"
HOMEPAGE = "https://xilinx.github.io/XRT/"
# DESCRIPTION = "NumPy is the fundamental package needed for scientific computing with Python."
SECTION = "devel/python"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=de2c993ac479f02575bcbfb14ef9b485"

SRCREV = "44be12a574e82a5eea2589f25be45ac88a5cc591"
PV = "2024.2"
PR = "r0"
SRC_URI = "git://github.com/Xilinx/XRT.git;protocol=https;branch=${PV}"

DEPENDS = " python3-pybind11 xrt"
RDEPENDS:${PN} = " python3"

S = "${WORKDIR}/git"

inherit python3-dir

do_compile () {
    ${CXX} -Wall -shared -std=c++14 -fPIC -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/${PYTHON_DIR} -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/xrt -I${PKG_CONFIG_SYSROOT_DIR}/${PYTHON_SITEPACKAGES_DIR}/pybind11/include ${S}/src/python/pybind11/src/pyxrt.cpp -o ${PN}.so ${LDFLAGS} -lxrt_coreutil -lxrt_core
}

do_install () {
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}/${PN}
    oe_libinstall -so ${PN} ${D}${PYTHON_SITEPACKAGES_DIR}/${PN}
}

FILES_SOLIBSDEV = ""
FILES:${PN} += "\
    ${PYTHON_SITEPACKAGES_DIR}/${PN}/${PN}.so \
"
INSANE_SKIP:${PN} += "dev-so"
