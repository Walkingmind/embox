#!/bin/sh

ROMFSIMGOBJ="$IMAGE_DIR/rdimage.o"

[ -d $ROMFS_DIR ] || mkdir -p $ROMFS_DIR
[ -d $IMAGE_DIR ] || mkdir -p $IMAGE_DIR

for i in `cat $TOOLS_DIR/dirs.lst`; do
    [ -d $ROMFS_DIR/$i ] || mkdir -p $ROMFS_DIR/$i
done

#TODO: copy binaries into romfs dir

ln -fs "/sbin/init" $ROMFS_DIR/init
chmod +x $KERNEL_DIR/scripts/gen_initramfs_list.sh
$KERNEL_DIR/scripts/gen_initramfs_list.sh $ROMFS_DIR > $KERNEL_DIR/initramfs.lst 2>&1

for i in `cat $TOOLS_DIR/devices.lst`; do
    name=${i%%,*}
    i=${i##${name},}
    type=${i%%,*}
    i=${i##${type},}
    maj=${i%%,*}
    i=${i##${maj},}
    min=${i%%,*}
    echo "nod /dev/$name 0600 0 0 $type $maj $min" >> $KERNEL_DIR/initramfs.lst
done

$GENROMFS -V "ROMdisk" -f $ROMFSIMGOBJ.img -d $ROMFS_DIR
gzip -f $ROMFSIMGOBJ.img
${CROSS_COMPILE}ld -r -b binary $ROMFSIMGOBJ.img.gz -o $ROMFSIMGOBJ
rm -f $ROMFSIMGOBJ.img.gz
