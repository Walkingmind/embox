# $Id: Makefile $
#
# emlinux Makefile
#
# Author: Nikolay Korotky
#

ARCH           = sparc
CROSS_COMPILE  = sparc-linux-
GENROMFS       = genromfs
KERNEL_VERSION = 2.6.21.1
KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-$(ARCH).patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-$(ARCH).default

ROOT_DIR   = $(shell pwd)
IMAGE_DIR  = $(ROOT_DIR)/images
PATCH_DIR  = $(ROOT_DIR)/patches
ROMFS_DIR  = $(ROOT_DIR)/romfs
TOOLS_DIR  = $(ROOT_DIR)/tools
KERNEL_DIR = $(ROOT_DIR)/linux-$(KERNEL_VERSION)

IMAGE      =$(IMAGE_DIR)/image
PIGGY      =$(IMAGE_DIR)/piggy
ROMFSIMGOBJ=$(IMAGE_DIR)/rdimage.o
export

.PHONY: kernel image piggy clean

all: kernel piggy

kernel:
	$(TOOLS_DIR)/build-busybox.sh
	$(TOOLS_DIR)/build-kernel.sh

image: 
	make -C boot/$(ARCH) image
	$(CROSS_COMPILE)objdump -d $(IMAGE) > $(IMAGE).dis
	$(CROSS_COMPILE)objdump -d $(IMAGE).dsu > $(IMAGE).dsu.dis

piggy: image
	$(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S $(IMAGE).dsu $(PIGGY)

clean:
	make -C boot/$(ARCH) clean
	rm -fr $(IMAGE_DIR) $(ROMFS_DIR) $(KERNEL_DIR)
