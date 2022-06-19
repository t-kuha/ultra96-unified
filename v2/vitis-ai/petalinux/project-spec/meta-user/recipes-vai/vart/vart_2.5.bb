SUMMARY = "Vitis AI RunTime"
DESCRIPTION = "Runner is an application level runtime interface for DPU IPs based on XRT. It use XIR subgraph as input, and run it on different targets. There are also emulators implemented with same interface to make debuging eaiser."

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=https;subpath=src/Vitis-AI-Runtime/VART/vart"
SRCREV = "c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8"
S = "${WORKDIR}/vart"


DEPENDS = "json-c xir target-factory"

# By default, Vart enables vitis-flow which depends on xrt. Please remove this line if use vivado-flow
PACKAGECONFIG:append = " vitis"

PACKAGECONFIG[test] = "-DBUILD_TEST=ON,-DBUILD_TEST=OFF,opencv,"
PACKAGECONFIG[python] = "-DBUILD_PYTHON=ON -DPYTHON_INSTALL_DIR=${PYTHON_DIR},-DBUILD_PYTHON=OFF,,python3-core"
PACKAGECONFIG[vitis] = ",,xrt,"

inherit cmake python3-dir

EXTRA_OECMAKE += "-DENABLE_CPU_RUNNER=OFF -DENABLE_SIM_RUNNER=OFF -DENABLE_DPU_RUNNER=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSROOT=${STAGING_DIR_HOST}"

do_configure:prepend() {

	rm -rf ${STAGING_DIR_HOST}/usr/share/cmake/XRT/
}

# Vart uses dl_open, so package the .so files in the runtime package
FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so"
FILES:${PN} += " \
	${libdir}/*.so \
	${PYTHON_SITEPACKAGES_DIR} \
"

SYSROOT_DIRS += "${bindir}"
