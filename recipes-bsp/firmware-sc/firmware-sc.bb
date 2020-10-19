# Copyright (C) 2020 SenzaCarta

SUMMARY = "SenzaCarta i.MX firmware"
DESCRIPTION = "SenzaCarta i.MX firmware for EPDC"
# FIXME - add proper license below
LICENSE = "CLOSED"

SRC_URI = " file://epdc_ES103TC1C1.fw"

PV = "1.0"

S = "${WORKDIR}"

inherit allarch

do_install() {
	install -d ${D}${base_libdir}/firmware/imx/epdc

	install -m 0755 ${WORKDIR}/epdc_ES103TC1C1.fw ${D}${base_libdir}/firmware/imx/epdc/
}

FILES_${PN} += "${base_libdir}/firmware/imx/epdc/epdc_ES103TC1C1.fw"
