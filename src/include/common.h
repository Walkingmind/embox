/**
 * @file
 *
 * @date 01.01.1970
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __EMBOX__
#include <err.h>
#else
#include <linux/types.h>
#endif

#if defined(CONFIG_TRACE) && !defined(SIMULATION_TRG)
# ifdef __EMBOX__
#  define TRACE(...)  printf(__VA_ARGS__)
# else
#  define TRACE(...)  printk(__VA_ARGS__)
# endif
#else
# define TRACE(...)  do ; while(0)
#endif

#define PRINTREG32_BIN(reg) {int i=0; for(;i<32;i++) TRACE("%d", (reg>>i)&1); TRACE(" (0x%x)\n", reg);}
#define array_len(array)		(sizeof(array) / sizeof(array[0]))

#ifdef __EMBOX__
#define OVK_REGLOAD(a)	a
#define OVK_REGSAVE(a,v) a=v
#define OVK_REGORIN(a,v) (OVK_REGSAVE(a,(OVK_REGLOAD(a) | (v))))
#define OVK_REGANDIN(a,v) (OVK_REGSAVE(a,(OVK_REGLOAD(a) & (v))))
#else
#define OVK_REGLOAD(a)	(LEON3_BYPASS_LOAD_PA(&(a)))
#define OVK_REGSAVE(a,v) (LEON3_BYPASS_STORE_PA(&(a),v))
#define OVK_REGORIN(a,v) (OVK_REGSAVE(a,(OVK_REGLOAD(a) | (v))))
#define OVK_REGANDIN(a,v) (OVK_REGSAVE(a,(OVK_REGLOAD(a) & (v))))
#endif /* __EMBOX__*/
#endif /* _COMMON_H_ */
