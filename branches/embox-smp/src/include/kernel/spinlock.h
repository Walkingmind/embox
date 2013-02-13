/**
 * @file
 * @brief
 *
 * @date 08.02.2012
 * @author Anton Bulychev
 */

#ifndef KERNEL_SPINLOCK_H_
#define KERNEL_SPINLOCK_H_

#include <kernel/cpu.h>

#ifdef SMP

typedef unsigned long spinlock_t;

#define SPIN_UNLOCKED 0
#define SPIN_LOCKED   1

#define SPINLOCK_DEFINE(name) \
	spinlock_t name = SPIN_UNLOCKED

#define SPINLOCK_DECLARE(name) \
	extern spinlock_t name

#define __barrier() \
	__asm__ __volatile__("" : : : "memory")


#if 0
#define __xchg_op(ptr, arg, op, lock)                                    \
         ({                                                              \
                 __typeof__ (*(ptr)) __ret = (arg);                      \
                 asm volatile (lock #op "b %0, %1\n"             \
                		 : "+r" (__ret), "+m" (*(ptr))     \
                		 : : "memory", "cc");              \
                 __ret;                                                  \
         })


#define xchg(ptr, v)    __xchg_op((ptr), (v), xchg, "")
#endif

static inline int spin_trylock(spinlock_t *lock) {
	unsigned long val = SPIN_LOCKED;

	__asm__ __volatile__ (
			"lock xchgb %0, %1"
			: "+r" (val), "+m" (*(lock))
	);

	__barrier();

	return val == SPIN_UNLOCKED;
}

static inline void spin_lock(spinlock_t *lock) {
	while (!spin_trylock(lock)) ;
}

static inline void spin_unlock(spinlock_t *lock) {
	*lock = SPIN_UNLOCKED;
	__barrier();
}

#else

#define SPINLOCK_DEFINE(name)

#define SPINLOCK_DECLARE(name)

#define spin_lock(lock)   do { } while (0)

#define spin_unlock(lock) do { } while (0)

#endif

#endif /* KERNEL_SPINLOCK_H_ */
