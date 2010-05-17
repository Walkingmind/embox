#!/bin/sh

BUSYBOX_VERSION="1.16.1"
BUSYBOX_SRC="busybox-$BUSYBOX_VERSION.tar.bz2"
HTTP_LINK="http://busybox.net/downloads/$BUSYBOX_SRC"
BUSYBOX_DIR="busybox-$BUSYBOX_VERSION"

[ -e $BUSYBOX_SRC ] || wget -c --proxy=on $HTTP_LINK
[ -d $BUSYBOX_DIR ] || tar -xvjf $BUSYBOX_SRC

pushd $BUSYBOX_DIR > /dev/null

make ARCH=sparc_v7soft V=1 menuconfig
make ARCH=sparc_v7soft V=1
make ARCH=sparc_v7soft CONFIG_PREFIX=$ROMFS_DIR install

popd > /dev/null 
 
[ -d $ROMFS_DIR/etc ] || mkdir -p $ROMFS_DIR/etc
cp $TOOLS_DIR/inittab $ROMFS_DIR/etc

[ -d $ROMFS_DIR/etc/init.d ] || mkdir -p $ROMFS_DIR/etc/init.d
cp $TOOLS_DIR/rc.S $ROMFS_DIR/etc/init.d
