#include <asm-generic/embox.lds.h>

#include <kernel/cpu.h>

#ifdef SMP

SECTIONS {
	.data : {
		_percpu_vma = .;
		*(.percpu)
		_percpu_len = . - _percpu_vma;
		. += _percpu_len * (NCPU - 1);
	} SECTION_REGION(data)
	SECTION_SYMBOLS(data)
}

#endif
