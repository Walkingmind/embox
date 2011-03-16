# -*- Makefile-gmake -*-
# $Id$

$_MODS += goto

$_REQUIRES-goto += embox.hal.interrupt

$_SRCS-goto += goto.c
$_USES-goto += libframework.a

$_BRIEF-goto = Transfer of control flow

define $_DETAILS-goto
	NAME
		goto - one-way control transfer
	SYNOPSIS
		goto [-h] [-a address]
	DESCRIPTION
		Executes the code at the specified address.
	OPTIONS
		-h
			Show usage
		-a address
			Entry point
	EXAMPLES
		goto -a 0x40000000
	SEE ALSO
		load
	AUTHORS
		Sergey Kuzmin
endef
