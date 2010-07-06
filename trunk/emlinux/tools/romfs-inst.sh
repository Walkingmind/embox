#!/bin/sh

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

