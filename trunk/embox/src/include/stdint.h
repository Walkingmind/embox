/**
 * @file
 * @brief ISO C99: 7.18 Integer types.
 *
 * @date 09.03.10
 * @author Eldar Abusalimov
 */

#ifndef STDINT_H_
#define STDINT_H_

#include <asm/types.h>

#ifndef __WORDSIZE
# error "You must define __WORDSIZE in asm/types.h"
#endif
#ifndef __ASSEMBLER__
typedef __s8  int8_t;
typedef __s16 int16_t;
typedef __s32 int32_t;
typedef __s64 int64_t;

typedef __u8  uint8_t;
typedef __u16 uint16_t;
typedef __u32 uint32_t;
typedef __u64 uint64_t;

typedef __s8  int_least8_t;
typedef __s16 int_least16_t;
typedef __s32 int_least32_t;
typedef __s64 int_least64_t;

typedef __u8  uint_least8_t;
typedef __u16 uint_least16_t;
typedef __u32 uint_least32_t;
typedef __u64 uint_least64_t;

#if __WORDSIZE == 32
typedef __s32 __s_fast;
typedef __u32 __u_fast;
#elif __WORDSIZE == 64
typedef __s64 __s_fast;
typedef __u64 __u_fast;
#elif __WORDSIZE == 16
typedef __s16 __s_fast;
typedef __u16 __u_fast;
#else
# error "Only 16, 32 and 64 __WORDSIZE values are supported"
#endif

typedef __s_fast int_fast8_t;
typedef __s_fast int_fast16_t;
typedef __s_fast int_fast32_t;
typedef __s_fast int_fast64_t;

typedef __u_fast uint_fast8_t;
typedef __u_fast uint_fast16_t;
typedef __u_fast uint_fast32_t;
typedef __u_fast uint_fast64_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

/* ToDo: WARNING 32bit now */
typedef int intptr_t;
typedef unsigned int uintptr_t;
#endif /* __ASSEMBLER__ */
#endif /* STDINT_H_ */
