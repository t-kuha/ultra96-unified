SUMMARY = "Target Factory"
DESCRIPTION = "A factory to manage DPU target description infos. Register targets and then you can get infos by name or fingerprint."

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "git://github.com/Xilinx/Vitis-AI.git;protocol=https;subpath=src/Vitis-AI-Runtime/VART/target_factory"
SRCREV = "c26eae36f034d5a2f9b2a7bfe816b8c43311a4f8"
S = "${WORKDIR}/target_factory"

DEPENDS = "unilog protobuf-native protobuf-c"

PACKAGECONFIG[test] = "-DBUILD_TEST=ON,-DBUILD_TEST=OFF,,"
PACKAGECONFIG[python] = ",,,"

inherit cmake

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"

# target-factory contains only one shared lib and will therefore become subject to renaming
# by debian.bbclass. Prevent renaming in order to keep the package name consistent 
AUTO_LIBNAME_PKGS = ""

FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so"
FILES:${PN} += "${libdir}/*.so"
