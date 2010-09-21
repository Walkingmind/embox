# $Id$
#

CFLAGS += -Wall -mno-fpu -nostdinc -O2

boot.o: boot.c $(AUTOCONF)
	$(CC) -I$(KERNEL_DIR)/include -I$(KERNEL_DIR)/arch/$(ARCH)/include -I. -include $(AUTOCONF) \
	    -D__KERNEL__ $(CFLAGS) \
	    -DKERNEL_VERSION=$(shell echo $(KERNEL_VERSION) | perl -ne "s/(\d+).(\d+).(\d+)([\d.]*)/\3/;print;") \
	    -iwithprefix include -c $<

pgt.o: pgt.S
	$(CC) $(CFLAGS) -iwithprefix include -c $<

emlinux.lds.o: emlinux.lds.S $(AUTOCONF)
	$(CC) -dM -C -E -P $< | cut -d' ' -f -2 | sed 's/#define/#undef/g' > remove_predefs.h
	$(CC) -include $(AUTOCONF) -include remove_predefs.h \
	    -E -C -P -DLINUXIMAGE="$(IMAGE)" $< -o $@

flash.lds.o: flash.lds.S
	echo "" > remove_predefs.h                                                               
	$(CC) -dM -C -E -P $< | cut -d' ' -f -2 | sed 's/#define/#undef/g' > remove_predefs.h
	$(CC) -include $(AUTOCONF) -E -C -P -DDATA_START=$(shell ls -la $(PIGGY) | awk '{print $$5}') -DPIGGY="piggy.o" $< -o $@

#locore.o: locore.S
#	$(CC) -D__ASSEMBLY__ -c -o $@ $<

#main.o: main.c
#	$(CC) -D__KERNEL_ $(CFLAGS) -iwithprefix include -c -o $@ $<

image.ram: emlinux.lds.o boot.o pgt.o
	$(LD) -X -T emlinux.lds.o $(IMAGE) boot.o pgt.o -o $(BIN_DIR)/$@

image.rom: flash.lds.o
	@echo 'stub'
	$(LD) -r -b binary -o piggy.o $(PIGGY)
	cp piggy.o $(BIN_DIR)
#	$(LD) -X -T flash.lds.o locore.o main.o piggy.o -o $(BIN_DIR)/$@

clean:
	$(RM) remove_predefs.h *.o

