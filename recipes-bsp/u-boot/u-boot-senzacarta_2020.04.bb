# Copyright (C) 2020 Senzacarta

SUMMARY = "U-Boot bootloader with support for SenzaCarta Board"

DESCRIPTION = "U-Boot bootloader with support for SenzaCarta Board. \
               Contact MAINTAINER for more support."

require u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc
inherit pythonnative

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PROVIDES += "u-boot"
DEPENDS_append = " dtc-native"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"

UBOOT_SRC ?= "git://github.com/econote/u-boot-senzacarta.git;protocol=https"
SRCBRANCH = "zeus"
SRC_URI = "${UBOOT_SRC};branch=${SRCBRANCH}"
SRCREV = "b518c602f7ebef38ad79b8f895af1e8eb37e8998"

S = "${WORKDIR}/git"

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-5.4.24-2.1.0"

BOOT_TOOLS = "imx-boot-tools"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(mx7|imx7dsenzacarta)"

UBOOT_NAME_mx7 = "u-boot-${MACHINE}.bin-${UBOOT_CONFIG}"
UBOOT_NAME_imx7dsenzacarta = "u-boot-${MACHINE}.bin-${UBOOT_CONFIG}"
