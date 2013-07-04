/**
 * @file
 * @brief POSIX Standard: 2.6 Primitive System Data Types.
 *
 * @date 24.11.09
 * @author Anton Bondarev
 */

#ifndef SYS_TYPES_H_
#define SYS_TYPES_H_

#ifndef __ASSEMBLER__

#include <asm/types.h>

#ifndef __size_t_defined
#define __size_t_defined
typedef unsigned int size_t; /**<Used for sizes of objects*/
#endif /* __size_t_defined */

/** Note also that 'size_t' is a typedef required by the ISO C standard
 (it must be available if <stddef.h> is included). However, 'ssize_t'
 does not exist in the C standard -- the standard 'ptrdiff_t'
 typedef is nearly equivalent.*/
typedef int ssize_t;

/** Used for system times in clock ticks or CLOCKS_PER_SEC*/
typedef unsigned long clock_t;

/** Used for time in microseconds.*/
typedef unsigned long useconds_t;

/** Used for time in microseconds.*/
typedef long suseconds_t;

typedef unsigned long spinlock_t;

typedef __u32 gfp_t;

typedef struct {
	volatile int counter;
} atomic_t;

typedef long time_t;

typedef int id_t;

typedef int pid_t;

typedef int dev_t;

typedef int clockid_t;

typedef unsigned int ino_t;

typedef unsigned short nlink_t;

typedef unsigned int mode_t;

typedef unsigned short uid_t;
typedef unsigned short gid_t;

typedef unsigned int blkno_t;

typedef int off_t;  /*  Used for file sizes. */

typedef long long loff_t;

typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;

#endif /* __ASSEMBLER__ */

#endif /* SYS_TYPES_H_ */
