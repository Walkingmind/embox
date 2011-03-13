$_MODS += tcpdump
$_SRCS-tcpdump += tcpdump.c
$_DEPS-tcpdump += embox.net.core

$_BRIEF-tcpdump = Dump traffic on a network

define $_DETAILS-tcpdump
	NAME
		tcpdump - dump traffic on a network.
	SYNOPSIS
		tcpdump [-i] [-c] [-h]
	AUTHORS
		Alexandr Batyukov
endef
