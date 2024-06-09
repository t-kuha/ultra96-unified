#
# Update wpa_supplicant.conf
#

inherit systemd

FILESEXTRAPATHS:append := "${THISDIR}/files:"

SRC_URI:append = " \
    file://wpa_supplicant-wlan0.conf \
    file://wlan.network \
    file://dropbear_rsa_host_key \
"

do_install:append () {
    install -d ${D}${sysconfdir}/wpa_supplicant
    install -m 600 ${WORKDIR}/wpa_supplicant-wlan0.conf ${D}${sysconfdir}/wpa_supplicant/wpa_supplicant-wlan0.conf

    install -d ${D}${sysconfdir}/systemd/network
    install -m 600 ${WORKDIR}/wlan.network ${D}${sysconfdir}/systemd/network/wlan.network

    install -d ${D}${sysconfdir}/dropbear
    install -m 600 ${WORKDIR}/dropbear_rsa_host_key ${D}${sysconfdir}/dropbear/dropbear_rsa_host_key

    install -d ${D}${sysconfdir}/systemd/system/multi-user.target.wants
    ln -s ../../../../lib/systemd/system/wpa_supplicant@.service ${D}${sysconfdir}/systemd/system/multi-user.target.wants/wpa_supplicant@wlan0.service
}
