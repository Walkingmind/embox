#!/bin/sh

#
# See:
# http://wiki.osdev.org/OS_Specific_Toolchain
#

BINUTILS_VER=2.23.1
GCC_VER=4.7.2
NEWLIB_VER=1.20.0


SOURCEWARE_URL=ftp://sourceware.org/pub
#BINUTILS_URL=$SOURCEWARE_URL/binutils/releases/binutils-$BINUTILS_VER.tar.bz2
#GCC_URL=$SOURCEWARE_URL/gcc/releases/gcc-$GCC_VER/gcc-$GCC_VER.tar.bz2
#NEWLIB_URL=$SOURCEWARE_URL/newlib/newlib-$NEWLIB_VER.tar.gz
BINUTILS_URL="http://ftp.gnu.org/gnu/binutils/binutils-2.23.1.tar.bz2"
GCC_URL="http://ftp.gnu.org/gnu/gcc/gcc-4.7.2/gcc-4.7.2.tar.bz2"
NEWLIB_URL="http://optimate.dl.sourceforge.net/project/devkitpro/sources/newlib/newlib-1.20.0.tar.gz"

export TARGET=i386-pc-embox
export PREFIX=`pwd`/output
export PATH=$PREFIX/bin:$PATH

MAKEOPTS="-j10"

mkdir -p build
mkdir -p output

download_binutils() {
	echo "Downloading binutils...\n"
	mkdir -p downloads
	cd downloads
	wget -c $BINUTILS_URL || exit
	cd ..
	echo "Binutils was downloaded!\n"
}

download_gcc() {
	echo "Downloading gcc...\n"
	mkdir -p downloads
	cd downloads
	wget -c $GCC_URL || exit
	cd ..
	echo "Gcc was downloaded!\n"
}

download_newlib() {
        echo "Downloading newlib...\n"
	mkdir -p downloads
	cd downloads
	wget -c $NEWLIB_URL || exit
	cd ..
	echo "Newlib was downloaded!\n"
}

download_all() {
	download_binutils && download_gcc && download_newlib	
	echo "All sources were downloaded!\n"
}


unpack_binutils() {
        echo "Unpacking binutils...\n"
	mkdir -p build
	cd build
	tar xf ../downloads/binutils-$BINUTILS_VER.tar.bz2 || exit
	cd ..
	echo "Binutils was unpacked!\n"
}

unpack_gcc() {
        echo "Unpacking gcc...\n"
	mkdir -p build
	cd build
	tar xf ../downloads/gcc-$GCC_VER.tar.bz2 || exit
	cd ..
	echo "Gcc was unpacked!\n"
}

unpack_newlib() {
        echo "Unpacking newlib...\n"
	mkdir -p build
	cd build
	tar xf ../downloads/newlib-$NEWLIB_VER.tar.gz || exit
	cd ..
	echo "Newlib was unpacked!\n"
}
	
unpack_all() {
	unpack_binutils && unpack_gcc && unpack_newlib
	echo "All sources were unpacked!\n"
}

patch_binutils() {
	echo "Patching binutils...\n"
	cd build
	patch -p0 -d binutils-$BINUTILS_VER < ../binutils.patch || exit
	cd ..
	echo "Binutils was patched!\n"
}

patch_gcc() {
	echo "Patching gcc...\n"
	cd build
	patch -p0 -d gcc-$GCC_VER < ../gcc.patch || exit
	cd ..
	echo "Gcc was patched!\n"
}

patch_newlib() {
	echo "Patching newlib...\n"
	cd build
	patch -p0 -d newlib-$NEWLIB_VER < ../newlib.patch || exit
	mkdir -p newlib-$NEWLIB_VER/newlib/libc/sys/embox
	cp ../newlib-files/* newlib-$NEWLIB_VER/newlib/libc/sys/embox
	cd newlib-$NEWLIB_VER/newlib/libc/sys/
	autoconf || exit
	cd embox
	autoreconf || exit
	cd ../../../../..
	cd ..
	echo "Newlib was patched!\n"
}

patch_all() {
	patch_binutils && patch_gcc && patch_newlib
	echo "All sources were patched!\n"
}

build_binutils() {
	echo "Building binutils...\n"
	mkdir -p build/build-binutils
	cd build/build-binutils
	../binutils-$BINUTILS_VER/configure --target=$TARGET --prefix=$PREFIX
	make $MAKEOPTS || exit
	make install || exit
	cd ../..
	echo "Binutils was built!\n"
}

build_gcc() {
	echo "Building gcc...\n"
	mkdir -p build/build-gcc
	cd build/build-gcc
	../gcc-$GCC_VER/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c
	make $MAKEOPTS all-gcc || exit
	make install-gcc || exit
	make $MAKEOPTS all-target-libgcc || exit
	make install-target-libgcc || exit
	cd ../..
	echo "Gcc was built!\n"
}

build_newlib() {
	echo "Compiling newlib...\n"
	mkdir -p build/build-newlib
	cd build/build-newlib
	../newlib-$NEWLIB_VER/configure --target=$TARGET --prefix=$PREFIX
	make $MAKEOPTS || exit
	make install || exit
	cd ../..
	echo "Newlib was built!\n"
}

build_crt() {
	echo "Building crt...\n"
	cd build
	touch crtbegin.S
	$TARGET-as -o crtbegin.o crtbegin.S || exit
	cp crtbegin.o $PREFIX/$TARGET/lib/crtbegin.o
	cp crtbegin.o $PREFIX/$TARGET/lib/crtend.o
	cd ..
	echo "Crt was built!\n"
}

build_all() {
	build_binutils && build_gcc && build_newlib && build_crt
	echo "All sources were built!\n"
}

download_all
unpack_all
patch_all
build_all

echo "Toolchain was builded!\n"
