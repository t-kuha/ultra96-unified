SUMMARY = "Vitis AI LIBRARY"
DESCRIPTION = "Xilinx Vitis AI components - VITIS AI LIBRARY"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=git;branch=${SRCBRANCH};subpath=${SUBPATH}"
SRCREV = "${@ "eeafe77e2112cdd91531d5d39cd42a3e0a444ff6" if bb.utils.to_boolean(d.getVar('BB_NO_NETWORK')) else d.getVar('AUTOREV') }"
SRCBRANCH ?= "v1.3"
SUBPATH = "tools/Vitis-AI-Library"
S = "${WORKDIR}/Vitis-AI-Library"

DEPENDS = "protobuf-native vart opencv googletest"
RDEPENDS_${PN} = "python3-core"

inherit cmake

EXTRA_OECMAKE += "-DENABLE_OVERVIEW=ON -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST=ON -DBUILD_SHARED_LIBS=ON"

FILES_${PN} += " \
	${datadir} \
	${prefix}/settings.sh \
"
