# $Id$
#
# Author: Nikolay Korotky
#

include $(CURDIR)/config.mk

CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
STRIP   = $(CROSS_COMPILE)strip
RM      = rm -fr
MKDIR   = mkdir -p

ROOT_DIR      = $(CURDIR)
ARCH_DIR      = $(ROOT_DIR)/arch
BIN_DIR       = $(ROOT_DIR)/bin
CONFIG_DIR    = $(ROOT_DIR)/config
DOWNLOADS_DIR = $(ROOT_DIR)/downloads
PATCH_DIR     = $(ROOT_DIR)/patches
RAMFS_DIR     = $(BIN_DIR)/ramfs
SCRIPTS_DIR   = $(ROOT_DIR)/scripts
USR_DIR       = $(ROOT_DIR)/usr
KERNEL_DIR    = $(ROOT_DIR)/linux-$(KERNEL_VERSION)
BOOT_DIR      = $(KERNEL_DIR)/arch/$(ARCH)/boot

OBJCOPYFLAGS  = -O binary -R .note -R .comment
GEN_INITRAMFS = $(KERNEL_DIR)/scripts/gen_initramfs_list.sh
#AUTOCONF      = $(KERNEL_DIR)/include/linux/autoconf.h
AUTOCONF      = $(KERNEL_DIR)/include/generated/autoconf.h
INITRAMFS_DIRS   = bin dev dev/etherd etc lib root sbin usr usr/bin usr/sbin var
INITRAMFS_SOURCE = $(KERNEL_DIR)/initramfs.lst

# elf image for loading with embox
IMAGE       = $(BIN_DIR)/image
# binary image for loading with embox
IMAGE_BIN   = $(IMAGE).bin
# elf image for loading without embox into RAM
IMAGE_RAM   = $(IMAGE).ram
# elf image for loading without embox into ROM
IMAGE_ROM   = $(IMAGE).rom
# srec image
IMAGE_SREC  = $(IMAGE).srec
# piggy image
IMAGE_PIGGY = $(BIN_DIR)/piggy
# Das U-Boot image
IMAGE_UBOOT = $(BIN_DIR)/uImage

export

.PHONY: patch-kernel usr ramfs kernel

all: patch-kernel usr ramfs kernel \
    $(IMAGE) $(IMAGE_BIN) $(IMAGE_UBOOT) $(IMAGE_RAM) $(IMAGE_PIGGY) $(IMAGE_SREC) $(IMAGE_ROM)
	@echo 'Build complete'

usr u:
	@$(MAKE) -C $(USR_DIR)

# Get kernel sources and apply patches
patch-kernel pk:
	[ -d $(DOWNLOADS_DIR) ] || $(MKDIR) $(DOWNLOADS_DIR)
	[ -e $(DOWNLOADS_DIR)/$(KERNEL_SRC) ] || wget -O $(DOWNLOADS_DIR)/$(KERNEL_SRC) -c $(KERNEL_URL)
	[ -d $(KERNEL_DIR) ] || tar -xvjf $(DOWNLOADS_DIR)/$(KERNEL_SRC)
	# WARN: be convinced of correct sequence of patches.
	for p in $(KERNEL_PATCHES); do \
	    [ "`cat $(PATCH_DIR)/CHECKSUMS.md5 | grep $$p | awk '{print $$1}'`" = \
		"`md5sum $(PATCH_DIR)/$$p | awk '{print $$1}'`" ] || echo 'md5 checksumm incorrect!'; \
	    [ -e $(KERNEL_DIR)/.patched_$$p ] || \
		zcat $(PATCH_DIR)/$$p | patch -N -p0 && touch $(KERNEL_DIR)/.patched_$$p; \
	done

ramfs:
	[ -d $(BIN_DIR) ] || $(MKDIR) $(BIN_DIR)
	[ -d $(RAMFS_DIR) ] || $(MKDIR) $(RAMFS_DIR)
	for i in $(INITRAMFS_DIRS); do \
	    [[ -d $(RAMFS_DIR)/$$i ]] || $(MKDIR) $(RAMFS_DIR)/$$i; \
	done
	@$(MAKE) -C $(USR_DIR) install

kernel k:
	chmod +x $(GEN_INITRAMFS)                                                                                                                                 
	$(GEN_INITRAMFS) $(RAMFS_DIR) > $(INITRAMFS_SOURCE) 2>&1
	$(SCRIPTS_DIR)/romfs-inst.sh
	[ -e $(KERNEL_DIR)/.config ] || cp $(CONFIG_DIR)/$(KERNEL_CONFIG) $(KERNEL_DIR)/.config
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) image.bin uImage

$(IMAGE):
	cp $(BOOT_DIR)/$(shell basename $(IMAGE)) $(BIN_DIR)
	@$(OBJDUMP) -d $(IMAGE) > $(IMAGE).dis

$(IMAGE_BIN): $(IMAGE)
	cp $(BOOT_DIR)/$(shell basename $(IMAGE_BIN)) $(BIN_DIR)

$(IMAGE_RAM): $(IMAGE)
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.ram
	@$(OBJDUMP) -d $(IMAGE_RAM) > $(IMAGE_RAM).dis

$(IMAGE_ROM): $(IMAGE)
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) image.rom

$(IMAGE_SREC): $(IMAGE_RAM)
	@$(OBJCOPY) -O srec $< $@

$(IMAGE_PIGGY): $(IMAGE_RAM)
	@$(OBJCOPY) $(OBJCOPYFLAGS) -S $< $@

$(IMAGE_UBOOT): $(IMAGE)
	cp $(BOOT_DIR)/$(shell basename $(IMAGE_UBOOT)) $(BIN_DIR)

clean c:
	@$(MAKE) -C $(ARCH_DIR)/$(ARCH) clean
	@$(MAKE) -C $(USR_DIR) clean
	@$(RM) $(BIN_DIR)
	@$(MAKE) -C $(KERNEL_DIR) clean
	@echo 'Clean complete'

distclean dc:
	@$(MAKE) -C $(KERNEL_DIR) distclean
	@$(RM) $(INITRAMFS_SOURCE)
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

