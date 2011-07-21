#include <asm-generic/embox.lds.h>

SECTIONS {
	.rodata (NOLOAD) : {
		ALIGNMENT();
		_romfs_start = .;
		*(.romfs)
		_romfs_end = .;
		ALIGNMENT();
	} SECTION_REGION(rodata)
	SECTION_SYMBOLS(rodata)

	.reloc : {
		ALIGNMENT();
		_flash_utils_start = .;
		*(.reloc.flash_utils)
		ALIGNMENT();
		_flash_utils_end = .;
	} SECTION_REGION(reloc)
	SECTION_SYMBOLS(reloc)
}
