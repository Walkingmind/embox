# $Id$
#
# Author: Nikolay Korotky
#

include $(CURDIR)/config.mk

CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
RM      = rm -fr
MKDIR   = mkdir -p

ROOT_DIR    = $(CURDIR)
ARCH_DIR    = $(ROOT_DIR)/arch
BIN_DIR     = $(ROOT_DIR)/bin
CONFIG_DIR  = $(ROOT_DIR)/config
PATCH_DIR   = $(ROOT_DIR)/patches
ROMFS_DIR   = $(ROOT_DIR)/romfs
SCRIPTS_DIR = $(ROOT_DIR)/scripts
USR_DIR     = $(ROOT_DIR)/usr
KERNEL_DIR  = $(ROOT_DIR)/linux-$(KERNEL_VERSION)

OBJCOPYFLAGS  = -O binary -R .note -R .comment
GEN_INITRAMFS = $(KERNEL_DIR)/scripts/gen_initramfs_list.sh

# elf image for loading with embox
IMAGE     = $(BIN_DIR)/image
# binary image for loading with embox
IMAGE_BIN = $(BIN_DIR)/image.bin
# elf image for loading without embox into RAM
IMAGE_RAM = $(BIN_DIR)/image.ram
# elf image for loading without embox into ROM
IMAGE_ROM = $(BIN_DIR)/image.rom
# piggy image
PIGGY     = $(BIN_DIR)/piggy
# Das U-Boot image
UIMAGE    = $(BIN_DIR)/uImage

export

.PHONY: patch-kernel usr kernel image

all: usr kernel image

usr u:
	@$(MAKE) -C $(USR_DIR)

patch-kernel pk:
	[ -e $(KERNEL_SRC) ] || wget -c $(KERNEL_URL)
	[ -d $(KERNEL_DIR) ] || tar -xvjf $(KERNEL_SRC)
	for p in $(KERNEL_PATCHES); do \
	    [ "`cat $(PATCH_DIR)/CHECKSUMS.md5 | grep $$p | awk '{print $$1}'`" = \
		"`md5sum $(PATCH_DIR)/$$p | awk '{print $$1}'`" ] || echo 'md5 checksumm incorrect!'; \
	    [ -e $(PATCH_DIR)/$$p ] && [ ! -e $(KERNEL_DIR)/.patched_$$p ] \
		&& zcat $(PATCH_DIR)/$$p | patch -N -p0 && touch $(KERNEL_DIR)/.patched_$$p; \
	done

kernel k: #patch-kernel
	[ -d $(ROMFS_DIR) ] || $(MKDIR) $(ROMFS_DIR)
	[ -d $(BIN_DIR) ] || $(MKDIR) $(BIN_DIR)
	for i in `cat $(SCRIPTS_DIR)/dirs.lst`; do \
	    [[ -d $(ROMFS_DIR)/$$i ]] || $(MKDIR) $(ROMFS_DIR)/$$i; \
	done
	chmod +x $(GEN_INITRAMFS)                                                                                                                                 
	$(GEN_INITRAMFS) $(ROMFS_DIR) > $(KERNEL_DIR)/initramfs.lst 2>&1
	$(SCRIPTS_DIR)/romfs-inst.sh
	[ -d $(BIN_DIR) ] || $(MKDIR) $(BIN_DIR)
	[ -e $(KERNEL_DIR)/.config ] || cp $(CONFIG_DIR)/$(KERNEL_CONFIG) $(KERNEL_DIR)/.config
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) image.bin uImage

image i:
	# linux kernel image (elf)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE)) $(BIN_DIR)
	# linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE_BIN)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(IMAGE_BIN)) $(BIN_DIR)
	# u-boot linux kernel image (binary)
	[ -e $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) ] \
	    && cp $(KERNEL_DIR)/arch/$(ARCH)/boot/$(shell basename $(UIMAGE)) $(BIN_DIR)
	# ram loadable image (elf)
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.ram
	# raw piggy image (binary)
	[ -e $(IMAGE_RAM) ] && $(OBJCOPY) $(OBJCOPYFLAGS) -S $(IMAGE_RAM) $(PIGGY)
	# rom image
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.rom
	# disassemble
	[ -e $(IMAGE) ] && $(OBJDUMP) -d $(IMAGE) > $(IMAGE).dis
	[ -e $(IMAGE_RAM) ] && $(OBJDUMP) -d $(IMAGE_RAM) > $(IMAGE).ram.dis
	@echo 'Build done'

clean c:
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) clean
	@$(MAKE) -C $(USR_DIR) clean
	@$(RM) $(BIN_DIR) $(ROMFS_DIR)
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

