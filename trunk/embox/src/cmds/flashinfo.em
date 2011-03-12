
$_MODS += flashinfo
$_SRCS-flashinfo += flashinfo.c
$_DEPS-flashinfo += embox.driver.flash

$_BRIEF-flashinfo = Reads flash info

define $_DETAILS-flashinfo
	NAME
		flash - low level flash interface
	SYNOPSIS
		flash [-i;f;u;a;e;l;s;r;w]
	DESCRIPTION
		reads flash info
	OPTIONS
		-i -  show flash info
		-f -  format flash (mbfs)
		-u [NBLOCK] -  unlock all blocks, or one specified 
		-a NBLOCK -  get block address
		-e NBLOCK -  erase block
		-l NBLOCK -  lock block
		-s NBLOCK -  read block status (lock/unlock)
		-r 0xADDR [NWORDS] -  read from flash
		-w 0xADDR [NWORDS] -  write to flash
	AUTHORS
		Alexandr Batyukov, Roman Evstifeev
endef
