#!/bin/sh

# Build a GNU/Linux cross-toolchain
# $Id$

LOG_FILE=$PWD/emtool.log

CROSSTOOL_ARCH=$1

print_msg() {
	echo -e $1 | tee -a $LOG_FILE
}

error_exit() {
	print_msg "$1"
	exit 1
}

[ ! -z $CROSSTOOL_ARCH ] || error_exit "Provide arch name, like \n$0 sparc"

source ./$CROSSTOOL_ARCH.in

CUR_DIR=$(pwd)
# Create temp working dir
TMP_DIR=$CUR_DIR/$(mktemp -d build.XXXXX)
PATCHES_DIR=$CUR_DIR/patches

PATCHES="$(ls $PATCHES_DIR/*.patch 2>/dev/null) 
	$(ls $PATCHES_DIR/$CROSSTOOL_ARCH/*.patch 2>/dev/null)"

# Keys:
#  0 - binutils
#  1 - gmp
#  2 - mpc
#  3 - mpfr
#  4 - gcc
#  5 - gdb
GET_URL[0]="http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/binutils/binutils-2.22.tar.gz"
GET_URL[1]="http://mirrors.kernel.org/gnu/gmp/gmp-5.0.2.tar.bz2"
GET_URL[2]="http://www.multiprecision.org/mpc/download/mpc-0.9.tar.gz"
GET_URL[3]="http://www.mpfr.org/mpfr-current/mpfr-3.1.2.tar.bz2"
GET_URL[4]="http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/gcc/gcc-4.6.2/gcc-4.6.2.tar.bz2"
GET_URL[5]="http://ftp.gnu.org/gnu/gdb/gdb-7.4.tar.bz2"

for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
	TARBALL[$i]=$(basename ${GET_URL[$i]})
	NAME[$i]=${TARBALL[$i]%%.tar.*}
done

do_download() {
	print_msg "downloading start" 
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		print_msg "Download ${TARBALL[$i]}"
		if [ ! -e ${TARBALL[$i]} ]; then
			wget ${GET_URL[$i]}
		fi
	done
	print_msg "downloading done"
}

do_unpack() {
	print_msg "unpack start"
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		print_msg "Unpack ${TARBALL[$i]}"
		[ -d ${NAME[$i]} ] || tar xaf ${TARBALL[$i]}
	done

	print_msg "Set symlinks for gcc"
	ln -s ../${NAME[1]} ${NAME[4]}/gmp
	ln -s ../${NAME[2]} ${NAME[4]}/mpc
	ln -s ../${NAME[3]} ${NAME[4]}/mpfr

	print_msg "Set symlinks for gdb"
	ln -s ../${NAME[1]} ${NAME[5]}/gmp
	ln -s ../${NAME[2]} ${NAME[5]}/mpc
	ln -s ../${NAME[3]} ${NAME[5]}/mpfr

	print_msg "Apply patches"
	for f in $PATCHES; do
		print_msg "Applying $f"
		patch -N -p0 < $f || print_msg "$f seems to be applied already"
	done
}

do_binutils() {
	print_msg "Build Binutils start"
	mkdir build-binutils 
	pushd build-binutils > /dev/null
	../${NAME[0]}/configure \
		--prefix=$TMP_DIR/$TARGET-${NAME[4]} \
		--target=$TARGET \
		--disable-werror \
		--disable-nls
	make && make install || error_exit "Building binutils failed"

	popd > /dev/null
	print_msg "Build Binutils done"
}

do_gcc() {
	print_msg "Build GCC start"
	mkdir build-gcc
	pushd build-gcc > /dev/null
	../${NAME[4]}/configure \
		--prefix=$TMP_DIR/$TARGET-${NAME[4]} \
		--target=$TARGET \
		--disable-werror \
		--with-gnu-ld \
		--disable-nls \
		--disable-multilib \
		--with-gnu-as \
		--without-headers \
		--enable-languages=c,c++ \
		--disable-libssp \
		--with-mpfr-include=$(pwd)/../${NAME[4]}/mpfr/src \
		--with-mpfr-lib=$(pwd)/mpfr/src/.libs \
		$TARGET_OPTIONS
	make && make install || error_exit "Building gcc failed"
	popd > /dev/null
	print_msg "Build GCC done"
}

do_gdb() {
	print_msg "Build GDB start"
	mkdir build-gdb 
	pushd build-gdb > /dev/null
	../${NAME[5]}/configure \
		--prefix=$TMP_DIR/$TARGET-${NAME[4]} \
		--target=$TARGET \
		--with-mpfr-include=$(pwd)/../${NAME[4]}/mpfr/src \
		--with-mpfr-lib=$(pwd)/mpfr/src/.libs 

	make && make install || error_exit "Building gdb failed"
	popd > /dev/null
	print_msg "Build GDB done"
}

makepkg() {
	print_msg "Make package"
	tar cf - $TARGET-${NAME[4]} | bzip2 -f > ../$TARGET-${NAME[4]}.tar.bz2
	cp ../$TARGET-${NAME[4]}.tar.bz2 $CUR_DIR
}

echo "" > $LOG_FILE

[ -d $TMP_DIR ] || mkdir $TMP_DIR

pushd $TMP_DIR > /dev/null

print_msg "directory is $TMP_DIR"

do_download && do_unpack && do_binutils && do_gcc && do_gdb && makepkg

popd > /dev/null
