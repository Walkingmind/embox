/**
 * @file
 *
 * @date 01.12.10
 * @author Nikolay Korotkiy
 */

#ifndef ARCH_X86_CONTEXT_H_
#define ARCH_X86_CONTEXT_H_

#include <types.h>

#ifndef __ASSEMBLER__

struct context {
	/* 0x00 */uint32_t eip; /**< TODO */
	/* 0x04 */uint32_t ebx; /**< TODO */
	/* 0x08 */uint32_t edi; /**< TODO */
	/* 0x0c */uint32_t esi; /**< TODO */
	/* 0x10 */uint32_t ebp; /**< TODO */
	/* 0x14 */uint32_t esp; /**< TODO */
	/* 0x18 */uint32_t eflags; /**< TODO */
};

#endif /* __ASSEMBLER__ */

#endif /* ARCH_X86_CONTEXT_H_ */
