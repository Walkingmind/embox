#!/bin/bash

print_msg() {
	echo -e $1 | tee -a $LOG_FILE
}

error_exit() {
	print_msg "$1"
	exit 1
}

CROSSTOOL_ARCH=$1

[ ! -z $CROSSTOOL_ARCH ] || error_exit "Provide arch name, like \n$0 sparc"
[ -f $CROSSTOOL_ARCH.in ] || error_exit "This arch is not supported"

. ./$CROSSTOOL_ARCH.in

[ -f $TARGET-toolchain.tar.bz2 ] || error_exit "build crosstool for this arch before install"

tar -xjf ./$TARGET-toolchain.tar.bz2 -C /opt
echo 'PATH="/opt/'$TARGET'-toolchain/bin/:$PATH"' >> ~/.profile

