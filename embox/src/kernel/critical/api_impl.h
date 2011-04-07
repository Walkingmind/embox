/**
 * @file
 * @brief Implements critical sections API.
 *
 * @details
 *
@verbatim
        +-----+---+---+-----+---+---+-----+---+---+
  bit#: | ... |13 |12 | ... | 9 | 8 | ... | 1 | 0 |
 level: |    preempt  |    softirq  |    hardirq  |
        +-----+---+---+-----+---+---+-----+---+---+
@endverbatim
 *
 * @c hardirq:
@verbatim
        +-----+---+---+-----+---+---+-----+---+---+
 level: |    preempt  |    softirq  |    hardirq  |
        +-----+---+---+-----+---+---+-----+---+---+
  mask: |     |   |   |     |   |   | *** | * | * |
 below: |     |   |   |     |   |   | *** | * | * |
 count: |     |   |   |     |   |   |     |   | * |
        +-----+---+---+-----+---+---+-----+---+---+
@endverbatim
 *
 * @c softirq:
@verbatim
        +-----+---+---+-----+---+---+-----+---+---+
 level: |    preempt  |    softirq  |    hardirq  |
        +-----+---+---+-----+---+---+-----+---+---+
  mask: |     |   |   | *** | * | * |     |   |   |
 below: |     |   |   | *** | * | * | *** | * | * |
 count: |     |   |   |     |   | * |     |   |   |
        +-----+---+---+-----+---+---+-----+---+---+
@endverbatim
 *
 * @c preempt:
@verbatim
        +-----+---+---+-----+---+---+-----+---+---+
 level: |    preempt  |    softirq  |    hardirq  |
        +-----+---+---+-----+---+---+-----+---+---+
  mask: | *** | * | * |     |   |   |     |   |   |
 below: | *** | * | * | *** | * | * | *** | * | * |
 count: |     |   | * |     |   |   |     |   |   |
        +-----+---+---+-----+---+---+-----+---+---+
@endverbatim
 *
 * @date 16.05.2010
 * @author Eldar Abusalimov
 */

#ifndef KERNEL_CRITICAL_API_IMPL_H_
#define KERNEL_CRITICAL_API_IMPL_H_

#include "count.h"

#define __CRITICAL_VALUE(bits, lower_mask) \
	((__CRITICAL_BELOW(lower_mask) << (bits) | __CRITICAL_VALUE_LOWEST(bits)) \
			^ __CRITICAL_BELOW(lower_mask))

#define __CRITICAL_VALUE_LOWEST(bits) \
	((0x1UL << (bits)) - 1)

/* Internal helper macros. */

#define __CRITICAL_LOWER(critical) \
	(((critical) ^ ((critical) - 1)) >> 1)

#define __CRITICAL_MASK(critical) \
	(critical)

#define __CRITICAL_BELOW(critical) \
	((critical) | __CRITICAL_LOWER(critical))

#define __CRITICAL_COUNT(critical) \
	(__CRITICAL_LOWER(critical) + 1)

/* Critical levels mask. */

#define __CRITICAL_HARDIRQ \
	__CRITICAL_VALUE_LOWEST(8)              /* 0x00ff */

#define __CRITICAL_SOFTIRQ \
	__CRITICAL_VALUE(4, __CRITICAL_HARDIRQ) /* 0x0f00 */

#define __CRITICAL_PREEMPT \
	__CRITICAL_VALUE(4, __CRITICAL_SOFTIRQ) /* 0xf000 */

inline static int critical_allows(__critical_t critical) {
	return !(__critical_count_get() & __CRITICAL_BELOW(critical));
}

inline static int critical_inside(__critical_t critical) {
	return __critical_count_get() & __CRITICAL_MASK(critical);
}

inline static void critical_enter(__critical_t critical) {
	__critical_count_add(__CRITICAL_COUNT(critical));
}

inline static void critical_leave(__critical_t critical) {
	__critical_count_sub(__CRITICAL_COUNT(critical));
}

#endif /* KERNEL_CRITICAL_API_IMPL_H_ */
