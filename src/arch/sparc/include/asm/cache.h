/**
 * @file
 * @brief Cache specific code for the Sparc.
 *
 * @date 14.02.10
 * @author Eldar Abusalimov
 */

#ifndef SPARC_CACHE_H_
#define SPARC_CACHE_H_

static inline void cache_flush(void) {
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
	);
}

static inline void cache_enable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"or %0,0xF,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

static inline void cache_disable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"andn %0,0xF,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

static inline void cache_insn_enable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"or %0,0x3,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

static inline void cache_insn_disable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"andn %0,0x3,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

static inline void cache_data_enable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"or %0,0xC,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

static inline void cache_data_disable(void) {
	register unsigned int tmp = 0;
	__asm__ __volatile__ (
		"flush\n\t"
		"nop;nop;nop\n\t"
		"lda [%%g0]0x2,%0\n\t"
		"andn %0,0xC,%0\n\t"
		"sta %0,[%%g0]0x2\n\t" : : "r" (tmp)
	);
}

#endif /* SPARC_CACHE_H_ */
