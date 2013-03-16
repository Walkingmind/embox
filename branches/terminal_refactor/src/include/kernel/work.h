/**
 * @file
 * @brief Async work interface.
 *
 * @date 15.03.13
 * @author Eldar Abusalimov
 */

#ifndef KERNEL_WORK_H_
#define KERNEL_WORK_H_

#include <util/slist.h>

#define WORK_F_DISABLED (0x1 << 0)  /**< Initially disabled work. */

struct work {
	struct slist_link pending_link;
	unsigned int state;
	void (*handler)(struct work *);
};

extern struct work *work_init(struct work *, void (*worker)(struct work *),
		unsigned int flags);

extern void work_disable(struct work *);
extern void work_enable(struct work *);
extern int work_disabled(struct work *);

extern void work_post(struct work *);
extern unsigned int work_pending(struct work *);
extern unsigned int work_pending_reset(struct work *);

/**
 * Evaluate a given @a expr inside a block with the specified @a work disabled.
 */
#define WORK_DISABLED_DO(work, expr) \
	({                             \
		typeof(expr) __ret;        \
		typeof(work) __w = (work); \
		work_disable(__w);         \
		__ret = (expr);            \
		work_enable(__w);          \
		__ret;                     \
	})

#endif /* KERNEL_WORK_H_ */

