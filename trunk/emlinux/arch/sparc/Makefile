# $Id$
#

AUTOCONF=$(KERNEL_DIR)/include/linux/autoconf.h

image: boot.c
	$(CROSS_COMPILE)gcc -dM -C -E -P emlinux.lds.S | cut -d' ' -f -2 | sed 's/#define/#undef/g' > remove_predefs.h
	$(CROSS_COMPILE)gcc -include $(AUTOCONF) -include remove_predefs.h \
	    -E -C -P -DLINUXIMAGE="$(IMAGE)" emlinux.lds.S -o emlinux.lds.o
	$(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include -I$(KERNEL_DIR)/arch/$(ARCH)/include -I. -include $(AUTOCONF) \
	    -D__KERNEL__ -Wall -mno-fpu -DCONFIG_KERNEL_ROOTMEM_INITRAMFS=1 \
	    -DKERNEL_VERSION=$(shell echo $(KERNEL_VERSION) | perl -ne "s/(\d+).(\d+).(\d+).(\d+)/\3/;print;") \
	    -nostdinc -iwithprefix include -O2 -c boot.c
	$(CROSS_COMPILE)gcc -Wall -mno-fpu -nostdinc -iwithprefix include -O2 -c pgt.S
	$(CROSS_COMPILE)ld -X -T emlinux.lds.o $(IMAGE) boot.o pgt.o -o $(IMAGE).dsu

clean:
	$(RM) remove_predefs.h *.o

