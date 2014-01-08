/**
 * @file
 *
 * @brief
 *
 * @date 12.12.2010
 * @author Anton Bondarev
 */

#ifndef ASM_X86_IO_H_
#define ASM_X86_IO_H_

#include <types.h>

static inline uint8_t in8(unsigned long port) {
	uint8_t tmp;
	__asm__ __volatile__(
		"inb %w1, %b0"
		: "=a"(tmp)
		: "Nd"(port)
	);
	return tmp;
}

static inline uint16_t in16(unsigned long port) {
	uint16_t tmp;
	__asm__ __volatile__(
		"inw %w1, %w0"
		: "=a"(tmp)
		: "Nd"(port)
	);
	return tmp;
}

static inline uint32_t in32(unsigned long port) {
	uint32_t tmp;
	__asm__ __volatile__(
		"in %w1, %0"
		: "=a"(tmp)
		: "Nd"(port)
	);
	return tmp;
}

#define inb(port) in8(port)

#define out8(val, port)                  \
	__asm__ __volatile__(            \
		"outb %b0, %w1"          \
		: : "a"(val), "Nd"(port) \
	)

#define out16(val, port)                 \
	__asm__ __volatile__(            \
		"outw %w0, %w1"          \
		: : "a"(val), "Nd"(port) \
	)

#define out32(val, port)                 \
	__asm__ __volatile__(            \
		"out %0, %w1"            \
		: : "a"(val), "Nd"(port) \
	)

#define outb(value, port)  out8(value, port)

#endif /* ASM_X86_IO_H_ */