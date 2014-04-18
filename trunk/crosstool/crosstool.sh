#!/bin/bash

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

. ./$CROSSTOOL_ARCH.in

CUR_DIR=$(pwd)
# Create temp working dir
if [ ! -z $TMP_DIR -a -d $TMP_DIR ]; then 
	TMP_DIR=$(readlink -f $TMP_DIR)
else
	TMP_DIR=$CUR_DIR/$(mktemp -d build.XXXXX)
fi

PATCHES_DIR=$CUR_DIR/patches

PATCHES="$(ls $PATCHES_DIR/*.patch 2>/dev/null) 
	$(ls $PATCHES_DIR/$CROSSTOOL_ARCH/*.patch 2>/dev/null)"


declare -A GET_URL
# Keys:
#  0 - gmp
#  1 - mpfr
#  2 - mpc
#  3 - binutils
#  4 - gcc
#  5 - gdb
GET_URL[0]="http://ftp.gnu.org/gnu/gmp/gmp-5.1.3.tar.bz2"
GET_URL[1]="http://ftp.gnu.org/gnu/mpfr/mpfr-3.1.2.tar.gz"
GET_URL[2]="http://ftp.gnu.org/gnu/mpc/mpc-1.0.2.tar.gz"
GET_URL[3]="http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.bz2"
GET_URL[4]="http://ftp.gnu.org/gnu/gcc/gcc-4.8.2/gcc-4.8.2.tar.bz2"
GET_URL[5]="http://ftp.gnu.org/gnu/gdb/gdb-7.7.tar.bz2"

DOWNLOAD=../download

for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
	TARBALL[$i]=$(basename ${GET_URL[$i]})
	NAME[$i]=${TARBALL[$i]%%.tar.*}
done

do_download() {
	print_msg "Download sources"
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		print_msg "Downloading ${TARBALL[$i]}"
		wget -c ${GET_URL[$i]} -P $DOWNLOAD
	done
}

do_unpack() {
	print_msg "Extract sources"
	for i in $(seq 0 $((${#GET_URL[@]} - 1))); do
		print_msg "Extracting ${TARBALL[$i]}"
		[ -d ${NAME[$i]} ] || tar xaf $DOWNLOAD/${TARBALL[$i]}
	done

	print_msg "Set symlinks for gcc"
	ln -s ../${NAME[0]} ${NAME[4]}/gmp
	ln -s ../${NAME[2]} ${NAME[4]}/mpc
	ln -s ../${NAME[1]} ${NAME[4]}/mpfr

	print_msg "Set symlinks for gdb"
	ln -s ../${NAME[0]} ${NAME[5]}/gmp
	ln -s ../${NAME[2]} ${NAME[5]}/mpc
	ln -s ../${NAME[1]} ${NAME[5]}/mpfr

	print_msg "Apply patches"
	for f in $PATCHES; do
		print_msg "Applying $f"
		patch -N -p0 < $f || print_msg "$f seems to be applied already"
	done
}

do_gmp() {
	local source_dir="../${NAME[0]}"
	local build_dir="build-gmp"
	local install_dir="$TMP_DIR/install-gmp"
	print_msg "Build gmp start"
	if [ ! -d $build_dir ]; then
		mkdir $build_dir
	fi
	pushd $build_dir > /dev/null
	if [ ! -e Makefile ]; then
		$source_dir/configure \
			--prefix=$install_dir \
			|| error_exit "Configuration gmp failed"
	fi
	make -j `nproc` -q all
	if [ $? -ne 0 ]; then
		#make -j `nproc` all && make -j `nproc` check && make -j `nproc` install
		make -j `nproc` all && make -j `nproc` install \
			|| error_exit "Building gmp failed"
	fi
	popd > /dev/null
	print_msg "Build gmp done"
}

do_mpfr() {
	local source_dir="../${NAME[1]}"
	local build_dir="build-mpfr"
	local install_dir="$TMP_DIR/install-mpfr"
	local gmp_dir="$TMP_DIR/install-gmp"
	print_msg "Build mpfr start"
	if [ ! -d $build_dir ]; then
		mkdir $build_dir
	fi
	pushd $build_dir > /dev/null
	if [ ! -e Makefile ]; then
		$source_dir/configure \
			--prefix=$install_dir \
			--with-gmp=$gmp_dir \
			|| error_exit "Configuration mpfr failed"
	fi
	make -j `nproc` -q all
	if [ $? -ne 0 ]; then
		make -j `nproc` all && make -j `nproc` install \
			|| error_exit "Building mpfr failed"
	fi
	popd > /dev/null
	print_msg "Build mpfr done"
}

do_mpc() {
	local source_dir="../${NAME[2]}"
	local build_dir="build-mpc"
	local install_dir="$TMP_DIR/install-mpc"
	local gmp_dir="$TMP_DIR/install-gmp"
	local mpfr_dir="$TMP_DIR/install-mpfr"
	print_msg "Build mpc start"
	if [ ! -d $build_dir ]; then
		mkdir $build_dir
	fi
	pushd $build_dir > /dev/null
	if [ ! -e Makefile ]; then
		$source_dir/configure \
			--prefix=$install_dir \
			--with-gmp=$gmp_dir \
			--with-mpfr=$mpfr_dir \
			|| error_exit "Configuration mpc failed"
	fi
	make -j `nproc` -q all
	if [ $? -ne 0 ]; then
		make -j `nproc` all && make -j `nproc` install \
			|| error_exit "Building mpc failed"
	fi
	popd > /dev/null
	print_msg "Build mpc done"
}

do_binutils() {
	local source_dir="../${NAME[3]}"
	local build_dir="build-binutils"
	local install_dir="$TMP_DIR/install-binutils"
	local gmp_dir="$TMP_DIR/install-gmp"
	local mpfr_dir="$TMP_DIR/install-mpfr"
	local mpc_dir="$TMP_DIR/install-mpc"
	print_msg "Build binutils start"
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
			|| [ -e Makefile ] || error_exit "Configuration binutils failed"
	fi
	make -j `nproc` -q all
	if [ $? -ne 0 ]; then
		make -j `nproc` all && make -j `nproc` install \
			|| error_exit "Building binutils failed"
	fi
	popd > /dev/null
	print_msg "Build binutils done"
}

do_gcc() {
	local source_dir="../${NAME[4]}"
	local build_dir="build-gcc"
	local install_dir="$TMP_DIR/install-gcc"
	local gmp_dir="$TMP_DIR/install-gmp"
	local mpfr_dir="$TMP_DIR/install-mpfr"
	local mpc_dir="$TMP_DIR/install-mpc"
	local binutils_dir="$TMP_DIR/install-binutils"
	local path=$binutils_dir/bin:$PATH
	local ld_lib_path=$gmp_dir/lib:$mpfr_dir/lib:$mpc_dir/lib:$LD_LIBRARY_PATH
	print_msg "Build gcc start"
	if [ ! -d $build_dir ]; then
		mkdir $build_dir
	fi
	pushd $build_dir > /dev/null
	if [ ! -e Makefile ]; then
		PATH=$path $source_dir/configure \
			--prefix=$install_dir \
			--target=$TARGET \
			--disable-multilib \
			--disable-libssp \
			--without-headers \
			--without-newlib \
			--with-gnu-as \
			--with-gnu-ld \
			--enable-languages=c,c++ \
			--enable-soft-float \
			--disable-shared \
			--with-gmp=$gmp_dir \
			--with-mpfr=$mpfr_dir \
			--with-mpc=$mpc_dir \
			$TARGET_OPTIONS \
			|| error_exit "Configuration gcc failed"
	fi
	make -j `nproc` -q all-gcc all-target-libgcc
	if [ $? -ne 0 ]; then
		PATH=$path LD_LIBRARY_PATH=$ld_lib_path make -j `nproc` all-gcc all-target-libgcc \
			&& PATH=$path make -j `nproc` install-gcc install-target-libgcc \
			|| error_exit "Building gcc failed"
	fi
	popd > /dev/null
	print_msg "Build gcc done"
}

do_gdb() {
	local source_dir="../${NAME[5]}"
	local build_dir="build-gdb"
	local install_dir="$TMP_DIR/install-gdb"
	local gmp_dir="$TMP_DIR/install-gmp"
	local mpfr_dir="$TMP_DIR/install-mpfr"
	local mpc_dir="$TMP_DIR/install-mpc"
	print_msg "Build gdb start"
	if [ ! -d $build_dir ]; then
		mkdir $build_dir
	fi
	pushd $build_dir > /dev/null
	if [ ! -e Makefile ]; then
		$source_dir/configure \
			--prefix=$install_dir \
			--target=$TARGET \
			--with-gmp=$gmp_dir \
			--with-mpfr=$mpfr_dir \
			--with-mpc=$mpc_dir \
			|| error_exit "Configuration gdb failed"
	fi
	make -j `nproc` -q all
	if [ $? -ne 0 ]; then
		make -j `nproc` all && make -j `nproc` install \
			|| error_exit "Building gdb failed"
	fi
	popd > /dev/null
	print_msg "Build gdb done"
}

makepkg() {
	local gmp_dir="install-gmp"
	local mpfr_dir="install-mpfr"
	local mpc_dir="install-mpc"
	local binutils_dir="install-binutils"
	local gcc_dir="install-gcc"
	local gdb_dir="install-gdb"
	local pkg_dir="$TARGET-toolchain"
	print_msg "Prepare package directory"
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
}

echo "" > $LOG_FILE

pushd $TMP_DIR > /dev/null

print_msg "directory is $TMP_DIR"

do_download && do_unpack && do_binutils && do_gcc && do_gdb && makepkg

popd > /dev/null
