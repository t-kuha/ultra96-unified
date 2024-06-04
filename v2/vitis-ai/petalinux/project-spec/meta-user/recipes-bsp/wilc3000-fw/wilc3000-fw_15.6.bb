HOMEPAGE = "https://github.com/linux4wilc/firmware"
DESCRIPTION = "Firmware files for use with Microchip wilc3000"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = "file://LICENSE.wilc_fw;md5=89ed0ff0e98ce1c58747e9a39183cc9f"

FILESEXTRAPATHS:append := "${THISDIR}/files:"

SRC_URI = " \
    git://github.com/linux4wilc/firmware.git;protocol=https;branch=${BRANCH} \
    file://wilc.conf"

# Tag: wilc_linux_15_6
SRCREV = "1c04e63ded9ca7265e7132dcae8ba3060d8cdd38"
BRANCH = "master"

S = "${WORKDIR}/git"

DEPENDS += "wilc"

do_install() {
    install -d ${D}${base_libdir}/firmware/mchp
    install -m 0755 ${S}/wilc* ${D}${base_libdir}/firmware/mchp

    install -d ${D}${sysconfdir}/modules-load.d
    cp ${WORKDIR}/wilc.conf ${D}${sysconfdir}/modules-load.d/
}

FILES:${PN} = " \
    ${base_libdir}/firmware/mchp/* \
    ${sysconfdir}/modules-load.d/wilc.conf \
"
