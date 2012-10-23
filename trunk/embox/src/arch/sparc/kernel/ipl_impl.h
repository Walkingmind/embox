/**
 * @file
 *
 * @date 25.11.09
 * @author Eldar Abusalimov
 */

#ifndef SPARC_IPL_IMPL_H_
#define SPARC_IPL_IMPL_H_

#ifndef __ASSEMBLER__

#include <asm/psr.h>

typedef unsigned int __ipl_t;

static inline void ipl_init(void) {
	unsigned int tmp;

	__asm__ __volatile__(
		"rd %%psr, %0\n\t"
		"andn %0, %1, %0\n\t"
		"wr %0, 0, %%psr\n\t"
		" nop; nop; nop\n"
		: "=&r" (tmp)
		: "i" (PSR_PIL)
		: "memory"
	);
}

static inline unsigned int ipl_save(void) {
	unsigned int ret;
	unsigned int tmp;

	__asm__ __volatile__ (
		"rd %%psr, %0\n\t"
		"or %0, %2, %1\n\t"
		"wr %1, 0, %%psr\n\t"
		" nop; nop; nop\n"
		: "=&r" (ret), "=r" (tmp)
		: "i" (PSR_PIL)
		: "memory"
	);

	return ret;
}

static inline void ipl_restore(unsigned int ipl) {
	unsigned int tmp;

	__asm__ __volatile__(
		"rd %%psr, %0\n\t"
		"and  %2, %1, %2\n\t"
		"andn %0, %1, %0\n\t"
		"wr %0, %2, %%psr\n\t"
		" nop; nop; nop\n"
		: "=&r" (tmp)
		: "i" (PSR_PIL), "r" (ipl)
		: "memory"
	);
}

#endif /* __ASSEMBLER__ */

#endif /* SPARC_IPL_IMPL_H_ */
