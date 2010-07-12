# $Id$
#
# Author: Nikolay Korotky
#

BUSYBOX_VERSION=1.8.2
BUSYBOX_SRC=busybox-$(BUSYBOX_VERSION).tar.bz2
BUSYBOX_LINK=http://busybox.net/downloads/$(BUSYBOX_SRC)
ifeq ($(CROSS_COMPILE),sparc-linux-)
CROSS_COMPILER_DIR=$(shell dirname `which $(CROSS_COMPILE)gcc`)/../sparc-linux
ARCH_BUSYBOX=sparc_v7soft
else
CROSS_COMPILER_DIR=$(shell dirname `which $(CROSS_COMPILE)gcc`)/../microblaze-unknown-linux-gnu
ARCH_BUSYBOX=microblaze
endif

BUSYBOX    := busybox-$(BUSYBOX_VERSION)

MODULES := $(BUSYBOX)

.PHONY: download $(MODULES) install clean

all: download $(MODULES) install

download:
	# busybox
	@[ -e $(BUSYBOX_SRC) ] || wget -c $(BUSYBOX_LINK)
	@[ -d $@ ] || tar -xvjf $(BUSYBOX_SRC)

$(BUSYBOX):
	cp $(CONFIG_DIR)/config-busybox-$(BUSYBOX_VERSION).default $@/.config
	@$(MAKE) -C $@ ARCH=$(ARCH_BUSYBOX)

install:
	# install /etc
	@[ -d $(ROMFS_DIR)/etc ] || $(MKDIR) $(ROMFS_DIR)/etc
	cp etc/inittab $(ROMFS_DIR)/etc
	@[ -d $(ROMFS_DIR)/etc/init.d ] || $(MKDIR) $(ROMFS_DIR)/etc/init.d
	cp etc/rc.S $(ROMFS_DIR)/etc/init.d
	# install busybox
	$(MAKE) -C $(BUSYBOX) ARCH=$(ARCH_BUSYBOX) CONFIG_PREFIX=$(ROMFS_DIR) install
	# install libs from compiler
	@[ -d $(ROMFS_DIR)/lib ] || $(MKDIR) $(ROMFS_DIR)/lib
	for lib in ld-linux.so.2 libc.so.6 libm.so.6 libcrypt.so.1 libstdc++.so.6 \
	libgcc_s.so.1 libgcc_s_soft_v8.so.1 libpthread.so.0 libgcc_s_soft.so.1 librt.so.1; do \
	    cp `readlink -f $(CROSS_COMPILER_DIR)/lib/$$lib` $(ROMFS_DIR)/lib/$$lib; \
	done
	find $(ROMFS_DIR)/lib -type f | xargs -r $(CROSS_COMPILE)strip -g

clean:
	$(RM) $(BUSYBOX)

