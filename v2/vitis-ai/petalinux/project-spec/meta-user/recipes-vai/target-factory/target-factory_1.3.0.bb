SUMMARY = "Target Factory"
DESCRIPTION = "A factory to manage DPU target description infos. Register targets and then you can get infos by name or fingerprint."

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=git;branch=${SRCBRANCH};subpath=${SUBPATH}"
SRCREV = "${@ "eeafe77e2112cdd91531d5d39cd42a3e0a444ff6" if bb.utils.to_boolean(d.getVar('BB_NO_NETWORK')) else d.getVar('AUTOREV') }"
SRCBRANCH ?= "v1.3"
SUBPATH = "tools/Vitis-AI-Runtime/VART/target_factory"
S = "${WORKDIR}/target_factory"

DEPENDS = "unilog protobuf-native protobuf-c"

PACKAGECONFIG_append = " test"
PACKAGECONFIG[test] = "-DBUILD_TEST=ON,-DBUILD_TEST=OFF,,"

inherit cmake

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"

# target-factory contains only one shared lib and will therefore become subject to renaming
# by debian.bbclass. Prevent renaming in order to keep the package name consistent 
AUTO_LIBNAME_PKGS = ""
