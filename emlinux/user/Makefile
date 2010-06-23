# $Id$
#
# Author: Nikolay Korotky
#

BUSYBOX_VERSION=1.8.2
BUSYBOX_SRC=busybox-$(BUSYBOX_VERSION).tar.bz2
BUSYBOX_LINK=http://busybox.net/downloads/$(BUSYBOX_SRC)
BUSYBOX_DIR=busybox-$(BUSYBOX_VERSION)
ifeq ($(CROSS_COMPILE),sparc-linux-)
CROSS_COMPILER_DIR=$(shell dirname `which $(CROSS_COMPILE)gcc`)/../sparc-linux
else
CROSS_COMPILER_DIR=$(shell dirname `which $(CROSS_COMPILE)gcc`)/../microblaze-unknown-linux-gnu
endif

.PHONY: busybox install clean

all: busybox install

busybox:
	[ -e $(BUSYBOX_SRC) ] || wget -c $(BUSYBOX_LINK)
	[ -d $(BUSYBOX_DIR) ] || tar -xvjf $(BUSYBOX_SRC)
	$(MAKE) -C $(BUSYBOX_DIR) ARCH=sparc_v7soft V=1 menuconfig
	$(MAKE) -C $(BUSYBOX_DIR) ARCH=sparc_v7soft V=1

install:
	# install busybox
	$(MAKE) -C $(BUSYBOX_DIR) ARCH=sparc_v7soft CONFIG_PREFIX=$(ROMFS_DIR) install
	# install libs from compiler
	@[ -d $(ROMFS_DIR)/lib ] || mkdir -p $(ROMFS_DIR)/lib
	for lib in ld-linux.so.2 libc.so.6 libm.so.6 libcrypt.so.1 libstdc++.so.6 \
	libgcc_s.so.1 libgcc_s_soft_v8.so.1 libpthread.so.0 libgcc_s_soft.so.1 librt.so.1; do \
	    cp `readlink -f $(CROSS_COMPILER_DIR)/lib/$$lib` $(ROMFS_DIR)/lib/$$lib; \
	done
	# install /etc
	@[ -d $(ROMFS_DIR)/etc ] || mkdir -p $(ROMFS_DIR)/etc
	cp etc/inittab $(ROMFS_DIR)/etc
	@[ -d $(ROMFS_DIR)/etc/init.d ] || mkdir -p $(ROMFS_DIR)/etc/init.d
	cp etc/rc.S $(ROMFS_DIR)/etc/init.d

clean:
	rm -fr $(BUSYBOX_DIR)

