# $Id$
#
# emlinux Makefile
#
# Author: Nikolay Korotky
#

ARCH           = sparc
CROSS_COMPILE  = sparc-linux-
KERNEL_VERSION = 2.6.21.1

KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-$(ARCH).patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-$(ARCH).default 

ROOT_DIR   = $(shell pwd)
BOOT_DIR   = $(ROOT_DIR)/boot/$(ARCH)
CONFIG_DIR = $(ROOT_DIR)/config
IMAGE_DIR  = $(ROOT_DIR)/images
PATCH_DIR  = $(ROOT_DIR)/patches
ROMFS_DIR  = $(ROOT_DIR)/romfs
TOOLS_DIR  = $(ROOT_DIR)/tools
USER_DIR   = $(ROOT_DIR)/user
KERNEL_DIR = $(ROOT_DIR)/linux-$(KERNEL_VERSION)

IMAGE      =$(IMAGE_DIR)/image
PIGGY      =$(IMAGE_DIR)/piggy
export

.PHONY: user kernel image piggy clean

all: user kernel piggy

user:
	$(MAKE) -C $(USER_DIR)

kernel:
	$(TOOLS_DIR)/build-kernel.sh

image: 
	$(MAKE) -C $(BOOT_DIR) image
	$(CROSS_COMPILE)objdump -d $(IMAGE) > $(IMAGE).dis
	$(CROSS_COMPILE)objdump -d $(IMAGE).dsu > $(IMAGE).dsu.dis

piggy: image
	$(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S $(IMAGE).dsu $(PIGGY)
	$(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S $(IMAGE) $(IMAGE).raw

clean:
	$(MAKE) -C $(BOOT_DIR) clean
	$(MAKE) -C $(USER_DIR) clean
	rm -fr $(IMAGE_DIR) $(ROMFS_DIR) $(KERNEL_DIR)

menuconfig: KERNEL_VERSION := `dialog \
                --stdout --backtitle "Linux kernel version" \
                --inputbox version: 10 30`
menuconfig:
	@echo "#define KERNEL_VERSION $(KERNEL_VERSION)" > autoconf.h

xconfig: KERNEL_VERSION := `Xdialog \
                --stdout --backtitle "Linux kernel version" \
                --inputbox version: 10 30`
xconfig:
	@echo "#define KERNEL_VERSION $(KERNEL_VERSION)" > autoconf.h
