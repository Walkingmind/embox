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
KERNEL_URL     = http://www.kernel.org/pub/linux/kernel/v2.6/$(KERNEL_SRC)

ROOT_DIR   = $(CURDIR)
ARCH_DIR   = $(ROOT_DIR)/arch
CONFIG_DIR = $(ROOT_DIR)/config
IMAGE_DIR  = $(ROOT_DIR)/images
PATCH_DIR  = $(ROOT_DIR)/patches
ROMFS_DIR  = $(ROOT_DIR)/romfs
TOOLS_DIR  = $(ROOT_DIR)/tools
USER_DIR   = $(ROOT_DIR)/user
KERNEL_DIR = $(ROOT_DIR)/linux-$(KERNEL_VERSION)
RM         = rm -fr
OBJCOPYFLAGS = -O binary -R .note -R .comment

IMAGE      = $(IMAGE_DIR)/image
BIN_IMAGE  = $(IMAGE_DIR)/image.bin
IMAGE_RAM  = $(IMAGE_DIR)/image.ram
IMAGE_ROM  = $(IMAGE_DIR)/image.rom
PIGGY      = $(IMAGE_DIR)/piggy
UIMAGE     = $(IMAGE_DIR)/uImage
export

.PHONY: users kernel image clean

all: users kernel image

users u:
	@$(MAKE) -C $(USER_DIR)

kernel k:
	[ -e $(KERNEL_SRC) ] || wget -c $(KERNEL_URL)
	[ -d $(KERNEL_DIR) ] || tar -xvjf $(KERNEL_SRC)
	for p in $(KERNEL_PATCHES); do \
	    [[ -e $(PATCH_DIR)/$$p ]] && zcat $(PATCH_DIR)/$$p | patch -N -p0; \
	done
	[ -d $(ROMFS_DIR) ] || mkdir -p $(ROMFS_DIR)
	[ -d $(IMAGE_DIR) ] || mkdir -p $(IMAGE_DIR)
	for i in `cat $(TOOLS_DIR)/dirs.lst`; do \
	    [[ -d $(ROMFS_DIR)/$$i ]] || mkdir -p $(ROMFS_DIR)/$$i; \
	done
	ln -fs "/sbin/init" $(ROMFS_DIR)/init                                                                                                                                                 
	chmod +x $(KERNEL_DIR)/scripts/gen_initramfs_list.sh                                                                                                                                  
	$(KERNEL_DIR)/scripts/gen_initramfs_list.sh $(ROMFS_DIR) > $(KERNEL_DIR)/initramfs.lst 2>&1
	$(TOOLS_DIR)/romfs-inst.sh
	[ -d $(IMAGE_DIR) ] || mkdir -p $(IMAGE_DIR)
	[ -e $(KERNEL_DIR)/.config ] || cp $(CONFIG_DIR)/$(KERNEL_CONFIG) $(KERNEL_DIR)/.config
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) KBUILD_VERBOSE=1 image.bin uImage

image i:
	# linux kernel image (elf)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) $(IMAGE_DIR)
	# linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) $(IMAGE_DIR)
	# u-boot linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) ] && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) $(IMAGE_DIR)
	# ram loadable image (elf)
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.ram
	# raw piggy image (binary)
	[ -e $(IMAGE_RAM) ] && $(CROSS_COMPILE)objcopy $(OBJCOPYFLAGS) -S $(IMAGE_RAM) $(PIGGY)
	# rom image
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.rom
	# disassemble
	[ -e $(IMAGE) ] && $(CROSS_COMPILE)objdump -d $(IMAGE) > $(IMAGE).dis
	[ -e $(IMAGE_RAM) ] && $(CROSS_COMPILE)objdump -d $(IMAGE_RAM) > $(IMAGE).ram.dis
	@echo 'Build done'

distclean clean dc c:
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) clean
	@$(MAKE) -C $(USER_DIR) clean
	@$(RM) $(IMAGE_DIR) $(ROMFS_DIR) $(KERNEL_DIR)
	@echo 'Clean complete'

menuconfig m: ARCH := `dialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 10 40 \
                $(shell echo $(notdir $(wildcard $(ARCH_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(ARCH_DIR)/*)))`
menuconfig m:
	@echo "ARCH=$(ARCH)" > config.mk

xconfig x: ARCH := `Xdialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 20 40 \
                $(shell echo $(notdir $(wildcard $(ARCH_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(ARCH_DIR)/*)))`
xconfig x:
	@echo "ARCH=$(ARCH)" > config.mk

