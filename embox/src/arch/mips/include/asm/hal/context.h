/**
 * @file
 *
 * @brief
 *
 * @date 22.06.2012
 * @author Anton Bondarev
 */

#ifndef MIPS_CONTEXT_H_
#define MIPS_CONTEXT_H_

struct context {
	unsigned int s[9]; /* static registers s0-s8 */
	unsigned int gp;   /* global pointer */
	unsigned int ra;   /* return address */
	unsigned int sp;   /* stack pointer */
};

#endif /* MIPS_CONTEXT_H_ */
