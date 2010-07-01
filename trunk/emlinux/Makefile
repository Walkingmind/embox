# $Id$
#
# emlinux Makefile
#
# Author: Nikolay Korotky
#

include $(CURDIR)/config.mk

ifeq ($(ARCH), sparc)
CROSS_COMPILE  = sparc-linux-
KERNEL_VERSION = 2.6.21.1
endif
ifeq ($(ARCH), microblaze)
CROSS_COMPILE  = mb-linux-
KERNEL_VERSION = 2.6.33
endif

KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-$(ARCH).patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-$(ARCH).default
KERNEL_FTP     = ftp://ftp.kernel.org/pub/linux/kernel/v2.6/$(KERNEL_SRC)

ROOT_DIR   = $(CURDIR)
BOOT_DIR   = $(ROOT_DIR)/boot
CONFIG_DIR = $(ROOT_DIR)/config
IMAGE_DIR  = $(ROOT_DIR)/images
PATCH_DIR  = $(ROOT_DIR)/patches
ROMFS_DIR  = $(ROOT_DIR)/romfs
TOOLS_DIR  = $(ROOT_DIR)/tools
USER_DIR   = $(ROOT_DIR)/user
KERNEL_DIR = $(ROOT_DIR)/linux-$(KERNEL_VERSION)
RM         = rm -fr

IMAGE      = $(IMAGE_DIR)/image
BIN_IMAGE  = $(IMAGE_DIR)/image.bin
IMAGE_DSU  = $(IMAGE_DIR)/image.dsu
PIGGY      = $(IMAGE_DIR)/piggy
UIMAGE     = $(IMAGE_DIR)/uImage
export

.PHONY: users kernel image clean

all: users kernel image

users:
	@$(MAKE) -C $(USER_DIR)

kernel: users
	[ -e $(KERNEL_SRC) ] || wget -c $(KERNEL_FTP)
	[ -d $(KERNEL_DIR) ] || tar -xvjf $(KERNEL_SRC)
	for p in $(KERNEL_PATCHES); do \
	    [[ -e $(PATCH_DIR)/$$p ]] && zcat $(PATCH_DIR)/$$p | patch -N -p0; \
	done
	[ -d $(ROMFS_DIR) ] || mkdir -p $(ROMFS_DIR)
	[ -d $(IMAGE_DIR) ] || mkdir -p $(IMAGE_DIR)
	$(TOOLS_DIR)/romfs-inst.sh
	[ -d $(IMAGE_DIR) ] || mkdir -p $(IMAGE_DIR)
	[ -e $(KERNEL_DIR)/.config ] || cp $(CONFIG_DIR)/$(KERNEL_CONFIG) $(KERNEL_DIR)/.config
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) KBUILD_VERBOSE=1 image.bin uImage

image: kernel
	# linux kernel image (elf)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) $(IMAGE_DIR)
	# linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) $(IMAGE_DIR)
	# u-boot linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) $(IMAGE_DIR)
	# dsu loadable image (elf)
	@$(MAKE) -C $(BOOT_DIR)/$(ARCH) image
	# raw piggy image (binary)
	[ -e $(IMAGE_DSU) ] && $(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S $(IMAGE_DSU) $(PIGGY)
	# disassemble
	[ -e $(IMAGE) ] && $(CROSS_COMPILE)objdump -d $(IMAGE) > $(IMAGE).dis
	[ -e $(IMAGE_DSU) ] && $(CROSS_COMPILE)objdump -d $(IMAGE_DSU) > $(IMAGE).dsu.dis
	@echo 'Build done'

clean:
	@$(MAKE) -C $(BOOT_DIR)/$(ARCH) clean
	@$(MAKE) -C $(USER_DIR) clean
	@$(RM) $(IMAGE_DIR) $(ROMFS_DIR) $(KERNEL_DIR)
	@echo 'Clean complete'

menuconfig: ARCH := `dialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 10 40 \
                $(shell echo $(notdir $(wildcard $(BOOT_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(BOOT_DIR)/*)))`
menuconfig:
	@echo "ARCH=$(ARCH)" > config.mk

xconfig: ARCH := `Xdialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 20 40 \
                $(shell echo $(notdir $(wildcard $(BOOT_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(BOOT_DIR)/*)))`
xconfig:
	@echo "ARCH=$(ARCH)" > config.mk

