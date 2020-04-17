#base-files_%.bbappend content

dirs755 += "/media/card"

do_install_append() {
	# Auto-mount boot directory of SD card 
	sed -i '/mmcblk0p1/s/^#//g' ${D}${sysconfdir}/fstab
}
