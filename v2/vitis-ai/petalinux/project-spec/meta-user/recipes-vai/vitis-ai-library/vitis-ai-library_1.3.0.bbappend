FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-vitis-ai-library-fix-cmake-error.patch"

FILES_SOLIBSDEV = "\
    ${base_libdir}/lib*${SOLIBSDEV} \
    ${libdir}/libvitis_ai_library-*.so \
    ${libdir}/libxnnpp-xnnpp.so \
"
FILES_${PN} += " \
    ${libdir}/libvart_op_imp_fix2float.so \
    ${libdir}/libvart_op_imp_fix.so \
    ${libdir}/libvart_op_imp_softmax.so \
"
