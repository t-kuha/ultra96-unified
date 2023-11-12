#
# Update /etc/fancontrol
#

inherit systemd

FILESEXTRAPATHS:append := "${THISDIR}/files:"

SRC_URI:append = "file://my-fancontrol"

do_install:append () {
    # Install fancontrol configuration file
    install -d ${D}${sysconfdir}/sysconfig
    install -m 0644 ${WORKDIR}/my-fancontrol ${D}${sysconfdir}/fancontrol 
}