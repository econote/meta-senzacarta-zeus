# meta-senzacarta

SenzaCarta Yocto Project for SCV1 & SCV4 Boards

## How to compile and use software for SenzaCarta

Here you will find some basic info about how to start with YOCTO and SenzaCarta. If you follow the steps below, you should be able to compile the source code.

In case you would like to know more about YOCTO and How to use it, for example: How to create, modify, compile and use meta-senzacarta. Please contact the MAINTAINER of the board Vikrant A. P. <vikrant.ap@econote.in>

### 1) Install the repo utility
	$ mkdir ~/bin
	$ curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
	$ chmod a+x ~/bin/repo

add following line to the `.bashrc` file to ensure that the `~/bin` folder is in your `PATH` variable

	$ PATH=${PATH}:~/bin

### 2) Get the YOCTO Project
	$ git config --global user.name "your name"
	$ git config --global user.email "your email"
	$ git config --list
	$ cd
	$ mkdir sc-yocto-bsp
	$ cd sc-yocto-bsp
	$ repo init -u https://source.codeaurora.org/external/imx/imx-manifest -b imx-linux-zeus -m imx-5.4.24-2.1.0.xml

### 3) Add SenzaCarta support - Create manifest
	$ cd ~/sc-yocto-bsp/
	$ mkdir -pv .repo/local_manifests/

Copy and Paste this into your Linux host machine

	$ cat > .repo/local_manifests/imx7dsenzacarta.xml << EOF
	<?xml version="1.0" encoding="UTF-8"?>
	<manifest>
		<remote fetch="git://github.com/econote" name="econote"/>
		<project remote="econote" revision="master" name="meta-senzacarta" path="sources/meta-senzacarta">
			<copyfile src="senzacarta-setup-release.sh" dest="senzacarta-setup-release.sh"/>
		</project>
	</manifest>
	EOF

### 4) Sync repositories
	$ repo sync

### 5) Add SenzaCarta meta layer into BSP
	$ source senzacarta-setup-release.sh

# Building Images
	$ cd ~/sc-yocto-bsp/
	$ repo sync

### Currently Supported machines <MACHINE>
Here is a list of 'machine names' which you can use to build SenzaCarta images. Use the 'machine name' based on the board you have:

	imx7dsenzacarta

### Setup and Build Console image
	$ DISTRO=fsl-imx-fb MACHINE=imx7dsenzacarta source senzacarta-setup-release -b build-sc
	$ bitbake core-image-base

### Setup and Build Toolchain
	$ bitbake core-image-base -c populate_sdk

All repositories regarding U-boot and Linux Kernel maintained separately by SenzaCarta Team
