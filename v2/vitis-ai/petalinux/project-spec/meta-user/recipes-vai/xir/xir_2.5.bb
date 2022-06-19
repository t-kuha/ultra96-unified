SUMMARY = "Vitis AI XIR"
DESCRIPTION = "Xilinx Intermediate Representation for deep learning algorithm. Define a graph based represention, provide APIs to serialize or deserialize a model and APIs for basic graph operations."

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=https;subpath=src/Vitis-AI-Runtime/VART/xir"
SRCREV = "c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8"
S = "${WORKDIR}/xir"

DEPENDS = "protobuf-native protobuf-c boost unilog"

PACKAGECONFIG[test] = "-DBUILD_TEST=ON,-DBUILD_TEST=OFF,,"
PACKAGECONFIG[python] = "-DBUILD_PYTHON=ON -DPYTHON_INSTALL_DIR=${PYTHON_DIR},-DBUILD_PYTHON=OFF,python3-pybind11,"

inherit cmake python3-dir

EXTRA_OECMAKE += "-DBUILD_SHARED_LIBS:BOOL=TRUE -DCMAKE_BUILD_TYPE=Release -DBUILD_CONTRIB=OFF -DBUILD_DOC=OFF -DINSTALL_USER=OFF -DCMAKE_SYSROOT=${STAGING_DIR_HOST}"

FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so"
FILES:${PN} += " \
	${libdir}/*.so \
	${PYTHON_SITEPACKAGES_DIR} \
"
