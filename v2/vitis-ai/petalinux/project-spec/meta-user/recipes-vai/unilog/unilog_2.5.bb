SUMMARY = "Vitis AI UNILOG"
DESCRIPTION = "Xilinx Vitis AI components - a wrapper for glog. Define unified log formats for vitis ai tools."

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "\
	git://github.com/Xilinx/Vitis-AI.git;protocol=https;nobranch=1;subpath=src/Vitis-AI-Runtime/VART/unilog \
"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRCREV = "c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8"
S = "${WORKDIR}/unilog"

DEPENDS = "glog boost"

PACKAGECONFIG[test] = "-DBUILD_TEST=ON,-DBUILD_TEST=OFF,,"
PACKAGECONFIG[python] = ",,,"

inherit cmake

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"

# unilog contains only one shared lib and will therefore become subject to renaming
# by debian.bbclass. Prevent renaming in order to keep the package name consistent 
AUTO_LIBNAME_PKGS = ""

FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so"
FILES:${PN} += "${libdir}/*.so"
