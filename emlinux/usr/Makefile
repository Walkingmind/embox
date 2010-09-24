# $Id$
#
# Author: Nikolay Korotky
#

LIBS = libc.so.6 libm.so.6 libcrypt.so.1 libstdc++.so.6 libgcc_s.so.1 \
       libgcc_s_soft_v8.so.1 libpthread.so.0 libgcc_s_soft.so.1 librt.so.1
ifeq ($(CROSS_COMPILE),sparc-linux-)
CROSS_COMPILER_DIR = $(shell dirname `which $(CROSS_COMPILE)gcc`)/../sparc-linux
LIBS              += ld-linux.so.2
else
CROSS_COMPILER_DIR = $(shell dirname `which $(CROSS_COMPILE)gcc`)/../microblaze-unknown-linux-gnu
LIBS              += ld.so.1
endif

MAKEFILES = Makefile.busybox

.PHONY: all install clean

all:
	for mk in $(MAKEFILES); do \
	    $(MAKE) -f $$mk all; \
	done

install:
	for mk in $(MAKEFILES); do \
	    $(MAKE) -f $$mk install; \
	done
	# install libs from compiler
	for lib in $(LIBS); do \
	    cp `readlink -f $(CROSS_COMPILER_DIR)/lib/$$lib` $(RAMFS_DIR)/lib/$$lib; \
	done
	cp etc/* $(RAMFS_DIR)/etc
	find $(RAMFS_DIR)/lib -type f | xargs -r $(STRIP) -g

clean:
	for mk in $(MAKEFILES); do \
	    $(MAKE) -f $$mk clean; \
	done

