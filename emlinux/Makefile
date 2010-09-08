# $Id$
#
# emlinux Makefile
#
# Author: Nikolay Korotky
#

include $(CURDIR)/config.mk

ifeq ($(ARCH), sparc)
CROSS_COMPILE  = sparc-linux-
endif
ifeq ($(ARCH), microblaze)
CROSS_COMPILE  = mb-linux-
endif

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

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
MKDIR      = mkdir -p
OBJCOPYFLAGS = -O binary -R .note -R .comment

IMAGE      = $(IMAGE_DIR)/image
BIN_IMAGE  = $(IMAGE_DIR)/image.bin
IMAGE_RAM  = $(IMAGE_DIR)/image.ram
IMAGE_ROM  = $(IMAGE_DIR)/image.rom
PIGGY      = $(IMAGE_DIR)/piggy
UIMAGE     = $(IMAGE_DIR)/uImage
export

.PHONY: users patch-kernel kernel image clean patch

all: users kernel image

users u:
	@$(MAKE) -C $(USER_DIR)

patch-kernel pk:
	[ -e $(KERNEL_SRC) ] || wget -c $(KERNEL_URL)
	[ -d $(KERNEL_DIR) ] || tar -xvjf $(KERNEL_SRC)
	for p in $(KERNEL_PATCHES); do \
	    [ "`cat $(PATCH_DIR)/CHECKSUMS.md5 | grep $$p | awk '{print $$1}'`" = \
		"`md5sum $(PATCH_DIR)/$$p | awk '{print $$1}'`" ] || echo 'md5 checksumm incorrect!'; \
	    [ -e $(PATCH_DIR)/$$p ] && [ ! -e $(KERNEL_DIR)/.patched_$$p ] \
		&& zcat $(PATCH_DIR)/$$p | patch -N -p0 && touch $(KERNEL_DIR)/.patched_$$p; \
	done

kernel k: patch-kernel
	[ -d $(ROMFS_DIR) ] || $(MKDIR) $(ROMFS_DIR)
	[ -d $(IMAGE_DIR) ] || $(MKDIR) $(IMAGE_DIR)
	for i in `cat $(TOOLS_DIR)/dirs.lst`; do \
	    [[ -d $(ROMFS_DIR)/$$i ]] || $(MKDIR) $(ROMFS_DIR)/$$i; \
	done
	ln -fs "/sbin/init" $(ROMFS_DIR)/init                                                                                                                                                 
	chmod +x $(KERNEL_DIR)/scripts/gen_initramfs_list.sh                                                                                                                                  
	$(KERNEL_DIR)/scripts/gen_initramfs_list.sh $(ROMFS_DIR) > $(KERNEL_DIR)/initramfs.lst 2>&1
	$(TOOLS_DIR)/romfs-inst.sh
	[ -d $(IMAGE_DIR) ] || $(MKDIR) $(IMAGE_DIR)
	[ -e $(KERNEL_DIR)/.config ] || cp $(CONFIG_DIR)/$(KERNEL_CONFIG) $(KERNEL_DIR)/.config
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) image.bin uImage

image i:
	# linux kernel image (elf)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) $(IMAGE_DIR)
	# linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(BIN_IMAGE)) $(IMAGE_DIR)
	# u-boot linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) $(IMAGE_DIR)
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

clean c:
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) clean
	@$(MAKE) -C $(USER_DIR) clean
	@$(RM) $(IMAGE_DIR) $(ROMFS_DIR)
	@$(MAKE) -C $(KERNEL_DIR) clean
	@echo 'Clean complete'

distclean dc:
	@$(MAKE) -C $(KERNEL_DIR) distclean
	@$(RM) $(KERNEL_DIR)/initramfs.lst
	@echo 'Distclean complete'

menuconfig m: ARCH := `dialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 10 40 \
                $(shell echo $(notdir $(wildcard $(ARCH_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(ARCH_DIR)/*)))`
menuconfig m: KERNEL_VERSION := `dialog \
                --stdout --backtitle "Kernel version" \
                --radiolist "Select kernel version:" 10 40 \
                $(shell ls $(PATCH_DIR) | grep linux | perl -ne "s/^linux-(\d.+)-(\w.+)/\1/;print" | uniq | wc -w) \
                $(patsubst %,% "" off,$(shell ls $(PATCH_DIR) | grep linux | perl -ne "s/^linux-(\d.+)-(\w.+)/\1/;print" | uniq))`
menuconfig m:
	@perl -i -ne "s/^ARCH(\s+)=(\s\w+)/ARCH\1= $(ARCH)/;print" config.mk
	@perl -i -ne "s/^KERNEL_VERSION(\s+)=(\s\w.+)/KERNEL_VERSION\1= $(KERNEL_VERSION)/;print" config.mk

xconfig x: ARCH := `Xdialog \
                --stdout --backtitle "Arch" \
                --radiolist "Select target arch:" 20 40 \
                $(shell echo $(notdir $(wildcard $(ARCH_DIR)/*)) | wc -w) \
                $(patsubst %,% "" off,$(notdir $(wildcard $(ARCH_DIR)/*)))`
xconfig x: KERNEL_VERSION := `Xdialog \
                --stdout --backtitle "Kernel version" \
                --radiolist "Select kernel version:" 20 40 \
                $(shell ls $(PATCH_DIR) | grep linux | perl -ne "s/^linux-(\d.+)-(\w.+)/\1/;print" | uniq | wc -w) \
                $(patsubst %,% "" off,$(shell ls $(PATCH_DIR) | grep linux | perl -ne "s/^linux-(\d.+)-(\w.+)/\1/;print" | uniq))`
xconfig x:
	@perl -i -ne "s/^ARCH(\s+)=(\s\w+)/ARCH\1= $(ARCH)/;print" config.mk
	@perl -i -ne "s/^KERNEL_VERSION(\s+)=(\s\w.+)/KERNEL_VERSION\1= $(KERNEL_VERSION)/;print" config.mk

patch p:
	cd $(PATCH_DIR); $(TOOLS_DIR)/make-ovk-patch.sh

