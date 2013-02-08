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

static inline int spin_trylock(spinlock_t *lock) {
	int val = SPIN_LOCKED;

	__asm__ __volatile__ (
			"lock xchgb %0,(%2)"
			: "=r" (val)
			: "" (val), "r" (lock)
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

#endif

#endif /* KERNEL_SPINLOCK_H_ */
