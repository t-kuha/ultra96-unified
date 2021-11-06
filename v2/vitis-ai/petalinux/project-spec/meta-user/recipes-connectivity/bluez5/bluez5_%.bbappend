#
# Update /etc/dbus-1/system.d/bluetooth.conf & input.conf
#

FILESEXTRAPATHS_append := "${THISDIR}/files:"

SRC_URI_append = " \
    file://my_bluetooth.conf \
"

do_install_append () {
	install -d ${D}${sysconfdir}/dbus-1/system.d/
	install -m 644 ${WORKDIR}/my_bluetooth.conf ${D}${sysconfdir}/dbus-1/system.d/bluetooth.conf
    sed -i "s/"#UserspaceHID"/"UserspaceHID"/g" ${D}${sysconfdir}/bluetooth/input.conf
}
