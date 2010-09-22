# $Id$
#
# Author: Nikolay Korotky
#

BUSYBOX_VERSION = 1.8.2
BUSYBOX_SRC     = busybox-$(BUSYBOX_VERSION).tar.bz2
BUSYBOX_LINK    = http://busybox.net/downloads/$(BUSYBOX_SRC)
LIBS = libc.so.6 libm.so.6 libcrypt.so.1 libstdc++.so.6 libgcc_s.so.1 \
       libgcc_s_soft_v8.so.1 libpthread.so.0 libgcc_s_soft.so.1 librt.so.1
ifeq ($(CROSS_COMPILE),sparc-linux-)
CROSS_COMPILER_DIR = $(shell dirname `which $(CROSS_COMPILE)gcc`)/../sparc-linux
LIBS              += ld-linux.so.2
ARCH_BUSYBOX       = sparc_v7soft
else
CROSS_COMPILER_DIR = $(shell dirname `which $(CROSS_COMPILE)gcc`)/../microblaze-unknown-linux-gnu
LIBS              += ld.so.1
ARCH_BUSYBOX       = microblaze
endif

BUSYBOX := busybox-$(BUSYBOX_VERSION)

MODULES := $(BUSYBOX)

.PHONY: download $(MODULES) install clean

all: download $(MODULES)

download:
	# busybox
	@[ -e $(DOWNLOADS_DIR)/$(BUSYBOX_SRC) ] || wget -O $(DOWNLOADS_DIR)/$(BUSYBOX_SRC) -c $(BUSYBOX_LINK)
	@[ -d $(BUSYBOX) ] || tar -xvjf $(DOWNLOADS_DIR)/$(BUSYBOX_SRC)

$(BUSYBOX):
	cp $(CONFIG_DIR)/config-busybox-$(BUSYBOX_VERSION).default $@/.config
	@$(MAKE) -C $@ ARCH=$(ARCH_BUSYBOX)

install:
	# install /etc
	cp etc/inittab $(RAMFS_DIR)/etc
	cp etc/rc.S $(RAMFS_DIR)/etc
	# install busybox
	$(MAKE) -C $(BUSYBOX) ARCH=$(ARCH_BUSYBOX) CONFIG_PREFIX=$(RAMFS_DIR) install
	# install libs from compiler
	for lib in $(LIBS); do \
	    cp `readlink -f $(CROSS_COMPILER_DIR)/lib/$$lib` $(RAMFS_DIR)/lib/$$lib; \
	done
	find $(RAMFS_DIR)/lib -type f | xargs -r $(STRIP) -g

clean:
	@$(MAKE) -C $(BUSYBOX) clean

