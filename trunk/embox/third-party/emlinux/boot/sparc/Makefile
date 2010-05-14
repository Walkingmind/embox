# $Id: Makefile $
#
# sparc prom_stage2
#
# Author: Nikolay Korotky
#

image:
	cp $(KERNEL)/arch/$(ARCH)/boot/image $(IMAGE)
	$(CROSS_COMPILE)gcc -dM -C -E -P $(SRC_DIR)/dsu.lds.S | cut -d' ' -f -2 | sed 's/#define/#undef/g' > $(BIN_DIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -I$(BIN_DIR) -include $(AUTOCONF) -include $(BIN_DIR)/remove_predefs.h \
	    -E -C -P -DCONFIG_KERNEL_ROOTMEM_ROMFS="0" \
	    -DRDIMAGE="$(ROMFSIMGOBJ)" -DLINUXIMAGE="$(IMAGE)" $(SRC_DIR)/dsu.lds.S -o $(BIN_DIR)/dsu.lds.o
	$(CROSS_COMPILE)gcc -I$(KERNEL)/include -I$(KERNEL)/arch/$(ARCH)/include -I. -include $(AUTOCONF) -D__KERNEL__ -Wall -mno-fpu \
	    -DCONFIG_KERNEL_ROOTMEM_INITRAMFS=1 -DCONFIG_KERNEL_ROOTMEM_ROMFS="0" \
	    -nostdinc -iwithprefix include -O2 -c -o $(BIN_DIR)/prom_stage2.o $(SRC_DIR)/prom_stage2.c
	$(CROSS_COMPILE)gcc -Wall -mno-fpu -nostdinc -iwithprefix include -O2 -c -o $(BIN_DIR)/pgt.o $(SRC_DIR)/pgt.S
	$(CROSS_COMPILE)ld -X -T $(BIN_DIR)/dsu.lds.o $(IMAGE) $(ROMFSIMGOBJ) $(BIN_DIR)/prom_stage2.o $(BIN_DIR)/pgt.o -o $(IMAGE).dsu
