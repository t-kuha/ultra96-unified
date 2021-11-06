HOMEPAGE = "https://github.com/linux4wilc/firmware"
DESCRIPTION = "Firmware files for use with Microchip wilc3000"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = "file://LICENSE.wilc_fw;md5=89ed0ff0e98ce1c58747e9a39183cc9f"

SRC_URI = "git://github.com/linux4wilc/firmware.git;protocol=git;branch=${BRANCH}"

# Tag: wilc_linux_15_5
SRCREV = "f7bd693c5c1161c5e1701d8058f0a1523a5465c7"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI += " \
    file://wilc.conf \
"

# Depends on Wilc driver https://github.com/Avnet/u96v2-wilc-driver
#DEPENDS += "wilc"

do_install() {
    install -d ${D}${base_libdir}/firmware/mchp
    install -m 0755 ${S}/wilc3000* ${D}${base_libdir}/firmware/mchp

    install -d ${D}${sysconfdir}/modules-load.d
    cp ${WORKDIR}/wilc.conf ${D}${sysconfdir}/modules-load.d/
}

FILES_${PN} = " \
    ${base_libdir}/firmware/mchp/* \
    ${sysconfdir}/modules-load.d/wilc.conf \
"
