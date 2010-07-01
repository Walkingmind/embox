#!/bin/sh

for i in `cat $TOOLS_DIR/dirs.lst`; do
    [ -d $ROMFS_DIR/$i ] || mkdir -p $ROMFS_DIR/$i
done

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

