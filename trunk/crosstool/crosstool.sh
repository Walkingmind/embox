#!/bin/bash

# Build a GNU/Linux cross-toolchain

#source arm.in
#source microblaze.in
#source sparc.in
source mips.in

# Create temp working dir
TMP_DIR=$(mktemp -d)

CUR_DIR=$(pwd)

LOG_FILE=$CUR_DIR/emtool.log


# Keys:
#  0 - binutils
#  1 - gmp
#  2 - mpc
#  3 - mpfr
#  4 - gcc
#  5 - gdb

GET_URL[0]="http://ftp.gnu.org/gnu/binutils/binutils-2.22.tar.bz2"
GET_URL[1]="http://mirrors.kernel.org/gnu/gmp/gmp-5.0.2.tar.bz2"
GET_URL[2]="http://www.multiprecision.org/mpc/download/mpc-0.9.tar.gz"
GET_URL[3]="http://www.mpfr.org/mpfr-current/mpfr-3.1.1.tar.bz2"
GET_URL[4]="http://gcc.parentingamerica.com/releases/gcc-4.6.2/gcc-4.6.2.tar.bz2"
GET_URL[5]="http://ftp.gnu.org/gnu/gdb/gdb-7.4.tar.bz2"

print_msg() {
	echo $1	
	echo $1  >> $LOG_FILE
}

do_download() {
	print_msg "downloading start" 
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		TARBALL[$i]=`basename $(echo ${GET_URL[$i]} | perl -MURI -le 'chomp(${GET_URL[$i]} = <>); print URI->new(${GET_URL[$i]})->path')`
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
		case `file -b ${TARBALL[$i]} | awk '{print $1}'` in
		    bzip2 )
			NAME[$i]=${TARBALL[$i]%%.tar.bz2}
			[ -d ${NAME[$i]} ] || tar xjf ${TARBALL[$i]}
			;;
		    gzip )
			NAME[$i]=${TARBALL[$i]%%.tar.gz}
			[ -d ${NAME[$i]} ] || tar xzf ${TARBALL[$i]}
			;;
		    * )
			print_msg "Unknown type"
			exit 1
			;;
		esac
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
		patch -p0 < $CUR_DIR/patches/$f
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
	make && make install
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
		--enable-languages=c \
		--disable-libssp \
		--with-mpfr-include=$(pwd)/../${NAME[4]}/mpfr/src \
		--with-mpfr-lib=$(pwd)/mpfr/src/.libs \
		$TARGET_OPTIONS
	make && make install
	popd > /dev/null
	print_msg "Build GCC done"
}

do_gdb() {
	print_msg "Build GDB start"
	mkdir build-gdb 
	pushd build-gdb > /dev/null
	../${NAME[5]}/configure \
		--prefix=$TMP_DIR/$TARGET-${NAME[4]} \
		--target=$TARGET
	make && make install
	popd > /dev/null
	print_msg "Build GDB done"
}

makepkg() {
	print_msg "Make package"
	tar cf - $TARGET-${NAME[4]} | bzip2 -f > ../$TARGET-${NAME[4]}.tar.bz2
	cp ../$TARGET-${NAME[4]}.tar.bz2 $(CUR_DIR)
}

echo "" > $LOG_FILE
pushd $TMP_DIR > /dev/null

print_msg "directory is $TMP_DIR"

do_download
do_unpack
do_binutils
do_gcc
do_gdb
makepkg

popd > /dev/null

rm -fr $TMP_DIR
