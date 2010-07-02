# $Id$
#

AUTOCONF=$(KERNEL_DIR)/include/linux/autoconf.h

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
CFLAGS += -Wall -mno-fpu -nostdinc -O2

boot.o: boot.c
	$(CC) -I$(KERNEL_DIR)/include -I$(KERNEL_DIR)/arch/$(ARCH)/include -I. -include $(AUTOCONF) \
	    -D__KERNEL__ $(CFLAGS) -DCONFIG_KERNEL_ROOTMEM_INITRAMFS=1 \
	    -DKERNEL_VERSION=$(shell echo $(KERNEL_VERSION) | perl -ne "s/(\d+).(\d+).(\d+).(\d+)/\3/;print;") \
	    -iwithprefix include -c $<

pgt.o: pgt.S
	$(CC) $(CFLAGS) -iwithprefix include -c $<

emlinux.lds.o: emlinux.lds.S
	$(CC) -dM -C -E -P $< | cut -d' ' -f -2 | sed 's/#define/#undef/g' > remove_predefs.h
	$(CC) -include $(AUTOCONF) -include remove_predefs.h \
	    -E -C -P -DLINUXIMAGE="$(IMAGE)" $< -o $@

image.dsu: emlinux.lds.o boot.o pgt.o
	$(LD) -X -T emlinux.lds.o $(IMAGE) boot.o pgt.o -o $(IMAGE_DIR)/$@

clean:
	$(RM) remove_predefs.h *.o

