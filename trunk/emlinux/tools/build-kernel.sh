#!/bin/sh

FTP_LINK="ftp://ftp.kernel.org/pub/linux/kernel/v2.6/$KERNEL_VERSION"
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

cp $CONFIG_DIR/$KERNEL_CONFIG config.def
make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE menuconfig
make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE KBUILD_VERBOSE=1 image
cp $KERNEL_DIR/arch/$ARCH/boot/image $IMAGE_DIR

if [[ -e `which ${CROSS_COMPILE}mkimage`/${CROSS_COMPILE}mkimage ]]; then
    make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE KBUILD_VERBOSE=1 uImage
    cp $KERNEL_DIR/arch/$ARCH/boot/uImage $IMAGE_DIR
fi

popd > /dev/null
