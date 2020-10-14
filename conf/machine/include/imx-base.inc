# Provides the i.MX common settings

include conf/machine/include/fsl-default-settings.inc
include conf/machine/include/fsl-default-versions.inc

require conf/machine/include/utilities.inc

# Set specific make target and binary suffix
IMX_DEFAULT_BOOTLOADER = "u-boot-fslc"

PREFERRED_PROVIDER_u-boot ??= "${IMX_DEFAULT_BOOTLOADER}"
PREFERRED_PROVIDER_virtual/bootloader ??= "${IMX_DEFAULT_BOOTLOADER}"

PREFERRED_PROVIDER_u-boot-mxsboot-native ??= "u-boot-fslc-mxsboot-native"

UBOOT_SUFFIX ?= "imx"
UBOOT_BINARY ?= "u-boot.${UBOOT_SUFFIX}"
UBOOT_MAKE_TARGET ?= "u-boot.${UBOOT_SUFFIX}"

UBOOT_ENTRYPOINT_mx7 = "0x80008000"

PREFERRED_PROVIDER_virtual/xserver = "xserver-xorg"
XSERVER_DRIVER                  = "xf86-video-fbdev"
XSERVER_DRIVER_imxgpu2d         = "xf86-video-imx-vivante"
XSERVER_DRIVER_vf               = "xf86-video-modesetting"
XSERVER_DRIVER_use-mainline-bsp = "xf86-video-armada"
XSERVER = "xserver-xorg \
           xf86-input-evdev \
           ${XSERVER_DRIVER}"

# Ship kernel modules
MACHINE_EXTRA_RRECOMMENDS = "kernel-modules"

# Tunes for hard/soft float-point selection. Note that we allow building for
# thumb support giving distros the chance to enable thumb by setting
# ARM_INSTRUCTION_SET = "thumb"
#
# handled by software
# DEFAULTTUNE_mx6 ?= "cortexa9t-neon"
# handled by hardware
DEFAULTTUNE_mx7    ?= "cortexa7thf-neon"

INHERIT += "machine-overrides-extender"

MACHINEOVERRIDES_EXTENDER_mx7d   = "imxfbdev:imxpxp:imxepdc"

MACHINEOVERRIDES_EXTENDER_FILTER_OUT_use-mainline-bsp = " \
    mx6 \
    mx6q \
    mx6dl \
    mx6sx \
    mx6sl \
    mx6sll \
    mx6ul \
    mx6ull \
    \
    mx7 \
    mx7d \
    mx7ulp \
    \
    mx8 \
    mx8qm \
    mx8mm \
    mx8mn \
    mx8mq \
    mx8qxp \
"

# Sub-architecture support
MACHINE_SOCARCH_SUFFIX ?= ""
MACHINE_SOCARCH_SUFFIX_mx7d = "-mx7d"
MACHINE_SOCARCH_SUFFIX_use-mainline-bsp = "-imx"

MACHINE_ARCH_FILTER = "virtual/kernel"
MACHINE_SOCARCH_FILTER_append_imx = " \
    alsa-lib \
    gstreamer1.0 \
    weston \
"
MACHINE_SOCARCH_FILTER_append_imxvpu = " \
    imx-codec \
    imx-parser \
    imx-vpuwrap \
    libimxvpuapi \
    virtual/imxvpu \
"
MACHINE_SOCARCH_FILTER_append_imxgpu = " \
    virtual/egl \
    virtual/mesa \
    virtual/libopenvg \
    libdrm \
    cairo \
    libgal-imx \
    pango \
"
MACHINE_SOCARCH_FILTER_append_imxgpu2d = " \
    virtual/libg2d \
"
MACHINE_SOCARCH_FILTER_append_imxgpu3d = " \
    virtual/libgl \
    virtual/libgles1 \
    virtual/libgles2 \
"
MACHINE_SOCARCH_FILTER_append_use-mainline-bsp = " \
    virtual/egl \
    virtual/libopenvg \
    virtual/libg2d \
    virtual/libgl \
    virtual/libgles1 \
    virtual/libgles2 \
    virtual/mesa \
    cairo \
    pango \
    qtbase \
"

MACHINE_SOARCH_FILTER_append_imxpxp = " \
    imx-codec \
"

INHERIT += "fsl-dynamic-packagearch"

SIGGEN_EXCLUDE_SAFE_RECIPE_DEPS_append = " \
    imx-gpu-viv->kernel-module-imx-gpu-viv \
    libimxvpuapi->virtual/imxvpu \
    imx-vpuwrap->virtual/imxvpu \
    imx-codec->virtual/imxvpu \
    imx-test->virtual/imxvpu \
"

# Firmware
MACHINE_FIRMWARE ?= ""
MACHINE_FIRMWARE_append_mx7d = " linux-firmware-imx-sdma-imx7d firmware-imx-epdc"
MACHINE_FIRMWARE_append_use-mainline-bsp = " linux-firmware-imx-sdma-imx7d"

# FIXME: Needs addition of firmware-imx of official BSPs
#MACHINE_FIRMWARE_append_mx27 = " firmware-imx-vpu-imx27"

MACHINE_EXTRA_RRECOMMENDS += "${MACHINE_FIRMWARE}"

# Extra audio support
#MACHINE_EXTRA_RRECOMMENDS_append_mx7 = " ${@bb.utils.contains('DISTRO_FEATURES', 'alsa', 'imx-alsa-plugins', '', d)}"

# Extra QCA Wi-Fi & BTE driver and firmware
#MACHINE_EXTRA_RRECOMMENDS_append = " ${@bb.utils.contains('MACHINE_FEATURES', 'qca6174', 'packagegroup-fsl-qca6174', '', d)}"
#MACHINE_EXTRA_RRECOMMENDS_append = " ${@bb.utils.contains('MACHINE_FEATURES', 'qca9377', 'packagegroup-fsl-qca9377', '', d)}"

# Extra udev rules
MACHINE_EXTRA_RRECOMMENDS += "udev-rules-imx"

# GStreamer 1.0 plugins
MACHINE_GSTREAMER_1_0_PLUGIN ?= ""
MACHINE_GSTREAMER_1_0_PLUGIN_mx7d ?= "gstreamer1.0-plugins-imx-meta"

# Determines if the SoC has support for Vivante kernel driver
SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT        = "0"
SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT_imxgpu = "1"

# Handle Vivante kernel driver setting:
#   0 - machine does not have Vivante GPU driver support
#   1 - machine has Vivante GPU driver support
MACHINE_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT ?= "${SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT}"

# Graphics libraries
PREFERRED_PROVIDER_virtual/egl      ?= "mesa"
PREFERRED_PROVIDER_virtual/libgl    ?= "mesa"
PREFERRED_PROVIDER_virtual/libgles1 ?= "mesa"
PREFERRED_PROVIDER_virtual/libgles2 ?= "mesa"

PREFERRED_PROVIDER_virtual/egl_imxgpu        ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgl_imxgpu3d    ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgles1_imxgpu3d ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgles2_imxgpu3d ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libg2d            ?= "imx-gpu-g2d"
PREFERRED_PROVIDER_virtual/libg2d_imxdpu     ?= "imx-dpu-g2d"

PREFERRED_VERSION_weston_mx6 ?= "5.0.0.imx"
PREFERRED_VERSION_weston_mx7 ?= "5.0.0.imx"
PREFERRED_VERSION_weston_mx8 ?= "5.0.0.imx"

PREFERRED_VERSION_wayland-protocols_mx6 ?= "1.17.imx"
PREFERRED_VERSION_wayland-protocols_mx7 ?= "1.17.imx"
PREFERRED_VERSION_wayland-protocols_mx8 ?= "1.17.imx"

# Use i.MX libdrm Version
PREFERRED_VERSION_libdrm_mx6 ?= "2.4.91.imx"
PREFERRED_VERSION_libdrm_mx7 ?= "2.4.91.imx"
PREFERRED_VERSION_libdrm_mx8 ?= "2.4.91.imx"

# Handle default kernel
IMX_DEFAULT_KERNEL = "linux-imx"
IMX_DEFAULT_KERNEL_mx7 = "linux-fslc-imx"
IMX_DEFAULT_KERNEL_use-mainline-bsp = "linux-fslc"

PREFERRED_PROVIDER_virtual/kernel ??= "${IMX_DEFAULT_KERNEL}"

SOC_DEFAULT_IMAGE_FSTYPES = "wic.bz2 tar.bz2"

# Do not update fstab file when using wic images
WIC_CREATE_EXTRA_ARGS ?= "--no-fstab-update"

OPTEE_BOOT_IMAGE         = "uTee"
OPTEE_BOOT_IMAGE_aarch64 = ""

IMAGE_FSTYPES ?= "${SOC_DEFAULT_IMAGE_FSTYPES}"

IMAGE_BOOT_FILES ?= " \
    ${KERNEL_IMAGETYPE} \
    ${@make_dtb_boot_files(d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'optee', '${OPTEE_BOOT_IMAGE}', '', d)} \
"

### wic default support
OPTEE_WKS_FILE_DEPENDS         = "optee-os"
OPTEE_WKS_FILE_DEPENDS_aarch64 = ""

WKS_FILE_DEPENDS ?= " \
    virtual/bootloader \
    \
    e2fsprogs-native \
    bmap-tools-native \
    ${@bb.utils.contains('MACHINE_FEATURES', 'optee', '${OPTEE_WKS_FILE_DEPENDS}', '', d)} \
"

SOC_DEFAULT_WKS_FILE ?= "imx-uboot-bootpart.wks.in"

WKS_FILE ?= "${SOC_DEFAULT_WKS_FILE}"

# Certain machines override the default fsl u-boot with the
# fslc u-boot. To restore the fsl u-boot, add use-fsl-bsp like this:
#   MACHINEOVERRIDES_prepend_imx6ulevk = "use-fsl-bsp:"
UBOOT_MAKE_TARGET_use-fsl-bsp_mx6 = "u-boot.imx"
UBOOT_SUFFIX_use-fsl-bsp_mx6 = "imx"
SPL_BINARY_use-fsl-bsp_mx6 = ""
WKS_FILE_use-fsl-bsp_mx6 = "imx-uboot-bootpart.wks.in"
UBOOT_MAKE_TARGET_use-fsl-bsp_mx7 = "u-boot.imx"
UBOOT_SUFFIX_use-fsl-bsp_mx7 = "imx"
SPL_BINARY_use-fsl-bsp_mx7 = ""
WKS_FILE_use-fsl-bsp_mx7 = "imx-uboot-bootpart.wks.in"

SERIAL_CONSOLES = "115200;ttymxc0"
SERIAL_CONSOLES_mxs = "115200;ttyAMA0"

KERNEL_IMAGETYPE = "zImage"
KERNEL_IMAGETYPE_aarch64 = "Image"

MACHINE_FEATURES = "usbgadget usbhost vfat touchscreen"

# Add the ability to specify _imx machines
MACHINEOVERRIDES =. "imx:"
