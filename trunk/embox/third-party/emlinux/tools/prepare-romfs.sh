#!/bin/sh

[ -d $ROMFSDIR ] || mkdir -p $ROMFSDIR
for i in $(shell cat $SRC_DIR/$DIRS_LIST); do
        [ -d $ROMFSDIR/$$i ] || mkdir -p $ROMFSDIR/$$i;
done

#TODO: copy binaries into romfs dir
chmod +x $KERNEL/scripts/gen_initramfs_list.sh
$KERNEL/scripts/gen_initramfs_list.sh $ROMFSDIR > $KERNEL/$INITRAMFS_LIST 2>&1
for i in `cat $SRC_DIR/$DEVICE_LIST`; do \
        name=$${i%%,*}; \
        i=$${i##$${name},}; \
        type=$${i%%,*}; \
        i=$${i##$${type},}; \
        maj=$${i%%,*}; \
        i=$${i##$${maj},}; \
        min=$${i%%,*}; \
        echo "nod /dev/$$name 0600 0 0 $$type $$maj $$min" >> $KERNEL/$INITRAMFS_LIST; \
done
$GENROMFS -V "ROMdisk" -f $ROMFSIMGOBJ.img -d $ROMFSDIR
gzip -f $ROMFSIMGOBJ.img
${CROSS_COMPILE}ld -r -b binary $ROMFSIMGOBJ.img.gz -o $ROMFSIMGOBJ
rm -f $ROMFSIMGOBJ.img.gz