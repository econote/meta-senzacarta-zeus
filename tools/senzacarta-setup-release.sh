#!/bin/sh
# 
# SenzaCarta Yocto Project Build Environment Setup Script
#
# Copyright (C) 2020 SenzaCarta

. sources/meta-senzacarta/tools/setup-utils.sh

CWD=`pwd`
PROGNAME="setup-environment"
exit_message ()
{
	echo "To return to this build environment later please run:"
	echo "    source setup-environment build-sc"
}

usage ()
{
	echo -e "\nUsage: source senzacarta-setup-release.sh
	Optional parameters: [-b build-dir] [-h]"
	echo "
		* [-b build-dir]: Build Directory, if unspecified script uses 'build' as output directory
		* [-h]: help
	"
}

clean_up ()
{
	unset CWD BUILD_DIR FSLDISTRO
	unset fsl_setup_help fsl_setup_error fsl_setup_flag
	unset usage clean_up
	unset ARM_DIR META_FSL_BSP_RELEASE
	exit_message clean_up
}

# Cleanup previous meta-freescale/EULA overrides
cd $CWD/sources/meta-freescale
if [ -h EULA ]; then
    echo Cleanup meta-freescale/EULA...
    git checkout -- EULA
fi
if [ ! -f classes/fsl-eula-unpack.bbclass ]; then
    echo Cleanup meta-freescale/classes/fsl-eula-unpack.bbclass...
    git checkout -- classes/fsl-eula-unpack.bbclass
fi
cd -

# Override the click-through in meta-freescale/EULA
FSL_EULA_FILE=$CWD/sources/meta-senzacarta/EULA

# Point to the current directory since the last command changed the directory to $BUILD_DIR
BUILD_DIR=.

if [ ! -e $BUILD_DIR/conf/local.conf ]; then
    echo -e "\n ERROR - No build directory is set yet. Run the 'setup-environment' script before running this script to create " $BUILD_DIR
    echo -e "\n"
    return 1
fi

# On the first script run, backup the local.conf file
# Consecutive runs, it restores the backup and changes are appended on this one.
if [ ! -e $BUILD_DIR/conf/local.conf.org ]; then
    cp $BUILD_DIR/conf/local.conf $BUILD_DIR/conf/local.conf.org
else
    cp $BUILD_DIR/conf/local.conf.org $BUILD_DIR/conf/local.conf
fi

if [ ! -e $BUILD_DIR/conf/bblayers.conf.org ]; then
    cp $BUILD_DIR/conf/bblayers.conf $BUILD_DIR/conf/bblayers.conf.org
else
    cp $BUILD_DIR/conf/bblayers.conf.org $BUILD_DIR/conf/bblayers.conf
fi

META_FSL_BSP_RELEASE="${CWD}/sources/meta-senzacarta"

echo "" >> $BUILD_DIR/conf/bblayers.conf
echo "# SenzaCarta Yocto Project Release layer" >> $BUILD_DIR/conf/bblayers.conf
echo "BBLAYERS += \"\${BSPDIR}/sources/meta-senzacarta\"" >> $BUILD_DIR/conf/bblayers.conf

echo BSPDIR=$BSPDIR
echo BUILD_DIR=$BUILD_DIR

cd  $BUILD_DIR
clean_up
unset FSLDISTRO
