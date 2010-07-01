#!/bin/sh

FTP_LINK="ftp://ftp.kernel.org/pub/linux/kernel/v2.6/linux-$KERNEL_VERSION.tar.bz2"
export ftp_proxy="http://proxy.tepkom.spb.su:3128"

[ -e $KERNEL_SRC ] || wget -c --proxy=on $FTP_LINK
[ -d $KERNEL_DIR ] || tar -xvjf $KERNEL_SRC

for p in $KERNEL_PATCHES; do
    if [[ -e $PATCH_DIR/$p ]]; then
	zcat $PATCH_DIR/$p | patch -N -p0
    fi
done

$TOOLS_DIR/romfs-inst.sh

[ -d $IMAGE_DIR ] || mkdir -p $IMAGE_DIR

pushd $KERNEL_DIR > /dev/null

[ -e .config ] || cp $CONFIG_DIR/$KERNEL_CONFIG .config

make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE KBUILD_VERBOSE=1 image.bin
make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE KBUILD_VERBOSE=1 uImage

popd > /dev/null
