#!/bin/bash

DEVICES_LIST=$SCRIPTS_DIR/devices.lst
INITRAMFS_LIST=$KERNEL_DIR/initramfs.lst

for i in `cat $DEVICES_LIST`; do
    name=${i%%,*}
    i=${i##${name},}
    type=${i%%,*}
    i=${i##${type},}
    maj=${i%%,*}
    i=${i##${maj},}
    min=${i%%,*}
    echo "nod /dev/$name 0600 0 0 $type $maj $min" >> $INITRAMFS_LIST
done

