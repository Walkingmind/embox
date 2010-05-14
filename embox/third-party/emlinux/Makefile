# $Id: Makefile $
#
# emlinux Makefile
#
# Author: Nikolay Korotky
#

include linux.conf

BIN_DIR=build
IMAGE=$(BIN_DIR)/image
PIGGY=$(BIN_DIR)/piggy
ROMFSDIR=$(BIN_DIR)/romfs
ROMFSIMGOBJ=$(BIN_DIR)/rdimage.o
SRC_DIR=arch/$(ARCH)

ifeq ($(KERNEL),linux-2.6.33.3)
AUTOCONF=$(KERNEL)/include/generated/autoconf.h
else
AUTOCONF=$(KERNEL)/include/linux/autoconf.h
endif

.PHONY: prepare romfs kernel image clean

all: prepare romfs kernel piggy

prepare:
	[ -e $(KERNEL).tar.bz2 ] || wget -c $(FTP_LINK)
	[ -d $(KERNEL) ] || tar -xvjf $(KERNEL).tar.bz2
	@for p in $(PATCHES); do \
		zcat $(SRC_DIR)/$$p | patch -p0; \
	done

romfs:
	[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	[ -d $(ROMFSDIR) ] || mkdir -p $(ROMFSDIR)
	@for i in $(shell cat $(SRC_DIR)/$(DIRS_LIST)); do \
	        [ -d $(ROMFSDIR)/$$i ] || mkdir -p $(ROMFSDIR)/$$i; \
	done
	#TODO: copy binaries into romfs dir
	chmod +x $(KERNEL)/scripts/gen_initramfs_list.sh
	$(KERNEL)/scripts/gen_initramfs_list.sh $(ROMFSDIR) > $(KERNEL)/$(INITRAMFS_LIST) 2>&1
	@for i in $(shell cat $(SRC_DIR)/$(DEVICE_LIST)); do \
	        name=$${i%%,*}; \
	        i=$${i##$${name},}; \
	        type=$${i%%,*}; \
	        i=$${i##$${type},}; \
	        maj=$${i%%,*}; \
	        i=$${i##$${maj},}; \
	        min=$${i%%,*}; \
	        echo "nod /dev/$$name 0600 0 0 $$type $$maj $$min" >> $(KERNEL)/$(INITRAMFS_LIST); \
	done
	$(GENROMFS) -V "ROMdisk" -f $(ROMFSIMGOBJ).img -d $(ROMFSDIR)
	gzip -f $(ROMFSIMGOBJ).img
	$(CROSS_COMPILE)ld -r -b binary $(ROMFSIMGOBJ).img.gz -o $(ROMFSIMGOBJ)
	rm -f $(ROMFSIMGOBJ).img.gz

kernel:
	$(MAKE) -C $(KERNEL) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) menuconfig
	$(MAKE) -C $(KERNEL) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) KBUILD_VERBOSE=1

image: 
	make -C boot/sparc image
	$(CROSS_COMPILE)objdump -d $(IMAGE) > $(IMAGE).dis
	$(CROSS_COMPILE)objdump -d $(IMAGE).dsu > $(IMAGE).dsu.dis

piggy: image
	$(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S $(IMAGE).dsu $(PIGGY)

clean:
	make -C $(KERNEL) clean
	rm -fr $(BIN_DIR)
