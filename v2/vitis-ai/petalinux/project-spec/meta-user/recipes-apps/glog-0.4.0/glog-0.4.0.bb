#
# This file is the glog-0.4.0 recipe.
#

DESCRIPTION = "The glog library implements application-level logging. This \
library provides logging APIs based on C++-style streams and various helper \
macros."
HOMEPAGE = "https://github.com/google/glog"

SECTION = "PETALINUX/apps"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://COPYING;md5=dc9db360e0bbd4e46672f3fd91dd6c4b"

SRC_URI = "https://github.com/google/glog/archive/v0.4.0.tar.gz"
SRC_URI[md5sum] = "0daea8785e6df922d7887755c3d100d0"
SRC_URI[sha256sum] = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c"

LIBV = "0.4.0"

S = "${WORKDIR}/${PN}"

inherit cmake

EXTRA_OECMAKE += "-DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF"
