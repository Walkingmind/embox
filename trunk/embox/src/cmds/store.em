# -*- Makefile-gmake -*-
# $Id$

$_MODS += store
$_SRCS-store += store.c
$_DEPS-store += embox.driver.flash

$_BRIEF-store = Store memory area to flash

define $_DETAILS-store
	NAME
		store - store memory area to flash
	SYNOPSIS
		store [-h] -f <src_addr> -t <dst_addr> -n <numbytes>
	DESCRIPTION
		-f <src_addr>
		-t <dst_addr>
		-n <numbytes>
	AUTHORS
		Alexander Batyukov
endef
