#base-files_%.bbappend content

dirs755 += "/media/card"

do_install:append() {
	# Auto-mount boot directory of SD card
	sed -i '/mmcblk0p1/s/^#//g' ${D}${sysconfdir}/fstab
	sed -i 's/\/media\/card/\/run\/media\/mmcblk0p1/g' ${D}${sysconfdir}/fstab
}
