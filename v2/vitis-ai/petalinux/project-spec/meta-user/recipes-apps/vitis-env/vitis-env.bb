#
# This file is the vitis-env recipe.
#

SUMMARY = "Simple vitis-env application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://vitis.sh \
	"

S = "${WORKDIR}"

do_install() {
	     install -d ${D}${sysconfdir}/profile.d/
	     install -m 0755 ${S}/vitis.sh ${D}${sysconfdir}/profile.d/
}
