# $Id$
#

CFLAGS = -Wall -ffixed-r31 -mno-xl-soft-mul -nostdinc -O2

boot.o: boot.c $(AUTOCONF)
	$(CC) -I$(KERNEL_DIR)/include -I$(KERNEL_DIR)/arch/$(ARCH)/include -I. -include $(AUTOCONF) \
	    -D__KERNEL__ $(CFLAGS) \
	    -DKERNEL_VERSION=$(shell echo $(KERNEL_VERSION) | perl -ne "s/(\d+).(\d+).(\d+).([\d]*)/\3/;print;") \
	    -iwithprefix include -c $<

emlinux.lds.o: emlinux.lds.S $(AUTOCONF)
	$(CC) -dM -C -E -P $< | cut -d' ' -f -2 | sed 's/#define/#undef/g' > remove_predefs.h
	$(CC) -include $(AUTOCONF) -include remove_predefs.h \
	    -E -C -P -DLINUXIMAGE="$(IMAGE)" $< -o $@

image.ram: emlinux.lds.o boot.o
	$(CP) $(IMAGE) $(IMAGE_RAM)
#	$(LD) -X -T emlinux.lds.o $(IMAGE) boot.o -o $(BIN_DIR)/$@

image.rom:
	@echo 'stub'
	$(LD) -r -b binary -o $(IMAGE_PIGGY).o $(IMAGE_PIGGY)

clean:
	$(RM) remove_predefs.h *.o
