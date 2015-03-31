#!/bin/bash

# Build a GNU/Linux cross-toolchain
# $Id$

set -e 

CROSSTOOL_ARCH=$1
MAKE_FLAGS=-j$(nproc || echo 1)

print_msg() {
	echo -e $1 | tee -a $LOG_FILE
}

error_exit() {
	print_msg "$1"
	exit 1
}

[ ! -z $CROSSTOOL_ARCH ] || error_exit "Provide arch name, like \n$0 sparc"
[ -f $CROSSTOOL_ARCH.in ] || error_exit "This arch is not supported"

. ./$CROSSTOOL_ARCH.in

realpath() {
	[[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

CUR_DIR=$(pwd)
# Create temp working dir
if [ ! -e build-$CROSSTOOL_ARCH ]; then 
	mkdir build-$CROSSTOOL_ARCH
fi
BUILD_DIR=$CUR_DIR/build-$CROSSTOOL_ARCH

LOG_FILE=$BUILD_DIR/emtool.log


PATCHES_DIR=$CUR_DIR/patches

PATCHES="$(ls $PATCHES_DIR/*.patch 2>/dev/null || true) 
	$(ls $PATCHES_DIR/$CROSSTOOL_ARCH/*.patch 2>/dev/null || true)"

# Keys:
#  0 - gmp
#  1 - mpfr
#  2 - mpc
#  3 - binutils
#  4 - gcc
#  5 - gdb
GET_URL=("http://ftp.gnu.org/gnu/gmp/gmp-6.0.0a.tar.bz2" \
	"http://ftp.gnu.org/gnu/mpfr/mpfr-3.1.2.tar.gz" \
	"http://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz" \
	"http://ftp.gnu.org/gnu/binutils/binutils-2.25.tar.bz2" \
	"http://ftp.gnu.org/gnu/gcc/gcc-4.9.2/gcc-4.9.2.tar.bz2" \
	"http://ftp.gnu.org/gnu/gdb/gdb-7.9.tar.xz")

DOWNLOAD=../download

for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
	TARBALL[$i]=$(basename ${GET_URL[$i]})
	NAME[$i]=${TARBALL[$i]%%.tar.*}
done

do_download() {
	local downloaded=".downloaded"
	print_msg "Download sources"
    if [ ! -e $downloaded ]; then
        for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
        	print_msg "Downloading ${TARBALL[$i]}"
        	wget -c ${GET_URL[$i]} -P $DOWNLOAD
    	done
    fi
	print_msg "Download done"
	touch $downloaded
}

do_unpack() {
	local extracted=".extracted"
	local patched=".patched"
	print_msg "Extract sources"
	if [ ! -e $extracted ]; then
		for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
			print_msg "Extracting ${TARBALL[$i]}"
			unzip_tar=$(echo ${TARBALL[$i]} | sed 's/.*\.gz/z/;s/.*.\.bz2/j/;s/.*\.xz/J/')
			[ -d ${NAME[$i]} ] || tar -${unzip_tar}xf $DOWNLOAD/${TARBALL[$i]}
		done

		print_msg "Set symlinks for binutils"
		ln -s ../${NAME[0]} ${NAME[3]}/gmp
		ln -s ../${NAME[1]} ${NAME[3]}/mpfr
		ln -s ../${NAME[2]} ${NAME[3]}/mpc

		print_msg "Set symlinks for gcc"
		ln -s ../${NAME[0]} ${NAME[4]}/gmp
		ln -s ../${NAME[1]} ${NAME[4]}/mpfr
		ln -s ../${NAME[2]} ${NAME[4]}/mpc

		print_msg "Set symlinks for gdb"
		ln -s ../${NAME[0]} ${NAME[5]}/gmp
		ln -s ../${NAME[1]} ${NAME[5]}/mpfr
		ln -s ../${NAME[2]} ${NAME[5]}/mpc
	fi
	print_msg "Extract done"
	touch $extracted

	print_msg "Apply patches"
	if [ ! -e $patched ]; then 
		for f in $PATCHES; do
			print_msg "Applying $f"
			patch -N -p0 < $f || print_msg "$f seems to be applied already"
		done
	fi
	print_msg "Patch done"
    touch $patched
}

do_binutils() {
	local source_dir="../${NAME[3]}"
	local build_dir="build-binutils"
	local install_dir="$BUILD_DIR/install-binutils"
	local binutils_done=".binutils_done"
	print_msg "Build binutils start"
	if [ ! -e $binutils_done ]; then
		if [ ! -d $build_dir ]; then
			mkdir $build_dir
		fi
		pushd $build_dir > /dev/null
		if [ ! -e Makefile ]; then
			$source_dir/configure \
				--prefix=$install_dir \
				--target=$TARGET \
				--with-float=soft \
				--enable-soft-float \
				--disable-werror \
				|| [ -e Makefile ] || error_exit "Configuration binutils failed"
		fi
		if ! make -q all; then
			make $MAKE_FLAGS all && make $MAKE_FLAGS install \
				|| error_exit "Building binutils failed"
		fi
		popd > /dev/null
	fi
	print_msg "Build binutils done"
	touch $binutils_done
}

do_gcc() {
	local source_dir="../${NAME[4]}"
	local build_dir="build-gcc"
	local install_dir="$BUILD_DIR/install-gcc"
	local binutils_dir="$BUILD_DIR/install-binutils"
	local path=$binutils_dir/bin:$PATH
	local gcc_done=".gcc_done"
	print_msg "Build gcc start"
	if [ ! -e $gcc_done ]; then
		if [ ! -d $build_dir ]; then
			mkdir $build_dir
		fi
		pushd $build_dir > /dev/null
		if [ ! -e Makefile ]; then
			PATH=$path $source_dir/configure \
				--prefix=$install_dir \
				--target=$TARGET \
				--disable-libssp \
				--disable-shared \
				--without-headers \
				--without-newlib \
				--with-gnu-as \
				--with-gnu-ld \
				--enable-languages=c,c++ \
				--enable-multilib \
				--enable-soft-float \
				$TARGET_OPTIONS \
				|| error_exit "Configuration gcc failed"
		fi
		if ! make -q all-gcc all-target-libgcc; then 
			PATH=$path make $MAKE_FLAGS all-gcc all-target-libgcc \
				&& PATH=$path make $MAKE_FLAGS install-gcc install-target-libgcc \
				|| error_exit "Building gcc failed"
		fi
		popd > /dev/null
	fi
	print_msg "Build gcc done"
	touch $gcc_done
}

do_gdb() {
	local source_dir="../${NAME[5]}"
	local build_dir="build-gdb"
	local install_dir="$BUILD_DIR/install-gdb"
	local gdb_done=".gdb_done"
	print_msg "Build gdb start"
	if [ ! -e $gdb_done ]; then
		if [ ! -d $build_dir ]; then
			mkdir $build_dir
		fi
		pushd $build_dir > /dev/null
		if [ ! -e Makefile ]; then
			$source_dir/configure \
				--prefix=$install_dir \
				--target=$TARGET \
				|| error_exit "Configuration gdb failed"
		fi
		if ! make -q all; then 
			make $MAKE_FLAGS all && make $MAKE_FLAGS install \
				|| error_exit "Building gdb failed"
		fi
		popd > /dev/null
	fi
	print_msg "Build gdb done"
	touch $gdb_done
}

makepkg() {
	local binutils_dir="install-binutils"
	local gcc_dir="install-gcc"
	local gdb_dir="install-gdb"
	local pkg_dir="$TARGET-toolchain"
	local pkg_done=".pkg_done"
	print_msg "Prepare package directory"
	if [ ! -e $pkg_done ]; then
		if [ -d $pkg_dir ]; then
			rm -rf $pkg_dir/*
		else
			mkdir $pkg_dir
		fi
		cp -r $binutils_dir/* $gcc_dir/* $gdb_dir/* $pkg_dir
		print_msg "Stripping..."
		find $pkg_dir | xargs file | grep -e "executable" -e "shared object" | grep ELF \
		  | cut -f 1 -d : | xargs strip --strip-unneeded 2> /dev/null
		print_msg "Make package"
		tar cf - $pkg_dir | bzip2 -f > ../${pkg_dir}.tar.bz2
	fi
	print_msg "Package done"
	touch $pkg_done
}

echo "" > $LOG_FILE

pushd $BUILD_DIR > /dev/null

print_msg "directory is $BUILD_DIR"

do_download && do_unpack && do_binutils && do_gcc && do_gdb && makepkg

popd > /dev/null
