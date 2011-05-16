/**
 * @file
 * @brief Definitions used by low-level trap handlers
 *
 * @date 29.11.09
 * @author Eldar Abusalimov
 */

#ifndef SPARC_ENTRY_H_
#define SPARC_ENTRY_H_

#include <asm/regs.h>

#ifdef __ASSEMBLER__

/**
 * All trap entry points must begin with this macro.
 * It makes sure the kernel has a proper window so that c-code can be called.
 */
#define SAVE_ALL \
	sethi %hi(trap_setup_begin), %t_retpc;            \
	jmpl  %t_retpc + %lo(trap_setup_begin), %t_retpc; \
	 rd %wim, %t_wim;

/**
 * All traps low-level code here must end with this macro.
 * Note that the traps must be disabled when entering restore routine.
 */
#define RESTORE_ALL \
	ba trap_setup_end; \
	rd %wim, %t_wim;

#endif /* __ASSEMBLER__ */

#endif /* SPARC_ENTRY_H_ */
