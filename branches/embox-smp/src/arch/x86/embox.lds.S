/* $Id$ */

#include <asm-generic/embox.lds.h>
#include <framework/mod/options.h>

#include <kernel/cpu.h>

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

MEMORY {
	MEMORY_REGION(sdram)
	MEMORY_REGION(flash)
}

SECTIONS {
	.text : {
		ALIGNMENT();
		*(.multiboot)
		_traps_text_start = .;
		*(.traps.*)
		_traps_text_end = .;
		*(.text)
		*(.text.*)
		ALIGNMENT();
	} SECTION_REGION(text)
	SECTION_SYMBOLS(text)

	.rodata : {
		ALIGNMENT();
		LDS_INPUT_RODATA
		ALIGNMENT();
	} SECTION_REGION(rodata)
	SECTION_SYMBOLS(rodata)

	.data : {
		ALIGNMENT();
		*(.data)

		_percpu_vma = .;
		*(.data.percpu)
		_percpu_len = . - _percpu_vma;
		. += _percpu_len * (NCPU - 1);

		ALIGNMENT();
	} SECTION_REGION(data)
	SECTION_SYMBOLS(data)

	.bss : {
		ALIGNMENT();
		*(.bss)
		ALIGNMENT();
	} SECTION_REGION(bss)
	SECTION_SYMBOLS(bss)

	.reserve (NOLOAD): {
		ALIGNMENT();
		LDS_INPUT_RESERVE
		ALIGNMENT();
	/* TODO memory region for reserve output section. */
	} SECTION_REGION(bss)
	SECTION_SYMBOLS(reserve)

	/* Sections to be discarded */
	/DISCARD/ : {
		*(.eh_frame)
	}
}

_mem_begin = LDS_REGION_BASE_sdram;
_mem_length = LDS_REGION_SIZE_sdram;
