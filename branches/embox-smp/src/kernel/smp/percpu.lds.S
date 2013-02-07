#include <asm-generic/embox.lds.h>

#include <kernel/cpu.h>

#ifdef SMP

SECTIONS {
	.percpu : {
		*(.percpu*)
	} SECTION_REGION(data)
	SECTION_SYMBOLS(percpu)

	.percpu_aps (NOLOAD) : {
		. += SIZEOF(.percpu) * (NCPU - 1);
	} SECTION_REGION(data)
	SECTION_SYMBOLS(percpu_aps)
}

#endif
