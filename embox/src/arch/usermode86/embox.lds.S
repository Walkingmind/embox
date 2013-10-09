/* $Id: embox.lds.S 7320 2012-10-30 07:00:26Z drakon.mega $ */

#include <asm-generic/embox.lds.h>

ENTRY(_start)

MEMORY {
	MEMORY_REGION(RAM)
	MEMORY_REGION(ROM)
}

_ram_base = ORIGIN(RAM);
_ram_size = LENGTH(RAM);

SECTIONS {
	.text : {
		*(.trap_table)
		*(.text)
		*(.text.*)
		*(.glue_7t) *(.glue_7)
	}
}
