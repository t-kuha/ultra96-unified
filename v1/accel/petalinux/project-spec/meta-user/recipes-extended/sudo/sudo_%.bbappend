do_install:append () {
    echo "Defaults  timestamp_timeout=1440" >> ${D}${sysconfdir}/sudoers
}