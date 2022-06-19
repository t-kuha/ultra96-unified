SUMMARY = "Vitis AI LIBRARY"
DESCRIPTION = "Xilinx Vitis AI components - VITIS AI LIBRARY"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=https;subpath=src/Vitis-AI-Library"
SRCREV = "c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8"
S = "${WORKDIR}/Vitis-AI-Library"

DEPENDS = "protobuf-native vart opencv googletest libeigen libeigen-native"

PACKAGECONFIG[test] = ",,,"
PACKAGECONFIG[python] = "-DBUILD_PYTHON=ON -DPYTHON_INSTALL_DIR=${PYTHON_DIR},-DBUILD_PYTHON=OFF,, bash"

inherit cmake python3-dir

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSROOT=${STAGING_DIR_HOST} -DBUILD_SHARED_LIBS=ON"

FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so"

FILES:${PN} += " \
	${datadir} \
	${libdir}/*.so \
	${prefix}/settings.sh \
	${PYTHON_SITEPACKAGES_DIR} \
"
