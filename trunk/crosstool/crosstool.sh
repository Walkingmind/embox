#!/bin/bash

# Build a GNU/Linux cross-toolchain

source arm.in
#source microblaze.in
#source sparc.in

# Create temp working dir
TMP_DIR=$(mktemp -d)

# Keys:
#  0 - binutils
#  1 - gmp
#  2 - mpc
#  3 - mpfr
#  4 - gcc
#  5 - gdb

GET_URL[0]="http://ftp.gnu.org/gnu/binutils/binutils-2.22.tar.bz2"
GET_URL[1]="http://mirrors.kernel.org/gnu/gmp/gmp-5.0.2.tar.bz2"
#GET_URL[1]="ftp://ftp.gmplib.org/pub/gmp-5.0.2/gmp-5.0.2.tar.bz2"
GET_URL[2]="http://www.multiprecision.org/mpc/download/mpc-0.9.tar.gz"
GET_URL[3]="http://www.mpfr.org/mpfr-current/mpfr-3.1.0.tar.bz2"
GET_URL[4]="http://gcc.cybermirror.org/releases/gcc-4.6.2/gcc-4.6.2.tar.bz2"
GET_URL[5]="http://ftp.gnu.org/gnu/gdb/gdb-7.4.tar.bz2"

do_download() {
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		TARBALL[$i]=`basename $(echo ${GET_URL[$i]} | perl -MURI -le 'chomp(${GET_URL[$i]} = <>); print URI->new(${GET_URL[$i]})->path')`
		echo "Download ${TARBALL[$i]}"
		if [ ! -e ${TARBALL[$i]} ]; then
			wget ${GET_URL[$i]}
		fi
	done
}

do_unpack() {
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		echo "Unpack ${TARBALL[$i]}"
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
			echo "Unknown type"
			exit 1
			;;
		esac
	done

	echo "Set symlinks for gcc"
	ln -s ../${NAME[1]} ${NAME[4]}/gmp
	ln -s ../${NAME[2]} ${NAME[4]}/mpc
	ln -s ../${NAME[3]} ${NAME[4]}/mpfr

	echo "Set symlinks for gdb"
	ln -s ../${NAME[1]} ${NAME[5]}/gmp
	ln -s ../${NAME[2]} ${NAME[5]}/mpc
	ln -s ../${NAME[3]} ${NAME[5]}/mpfr
}

do_binutils() {
	echo "Build Binutils"
	mkdir build-binutils 
	pushd build-binutils > /dev/null
	../${NAME[0]}/configure \
		--prefix=$TMP_DIR/$target_name-${NAME[4]} \
		--target=$target_name \
		--disable-werror \
		--disable-nls
	make && make install
	popd > /dev/null
}

do_gcc() {
	echo "Build GCC"
	mkdir build-gcc
	pushd build-gcc > /dev/null
	../${NAME[4]}/configure \
		--prefix=$TMP_DIR/$target_name-${NAME[4]} \
		--target=$target_name \
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
		$target_configure_options
	make && make install
	popd > /dev/null
}

do_gdb() {
	echo "build GDB"
	mkdir build-gdb 
	pushd build-gdb > /dev/null
	../${NAME[5]}/configure \
		--prefix=$TMP_DIR/$target_name-${NAME[4]} \
		--target=$target_name
	make && make install
	popd > /dev/null
}

makepkg() {
	echo "Make package"
	tar cf - $target_name-${NAME[4]} | bzip2 -f > ../$target_name-${NAME[4]}.tar.bz2
}

pushd $TMP_DIR > /dev/null

do_download
do_unpack
do_binutils
#do_gcc
#do_gdb
makepkg

popd > /dev/null

rm -fr $TMP_DIR
