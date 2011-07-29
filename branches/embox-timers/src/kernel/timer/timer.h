/**
 * @file
 *
 * @date 02.09.09
 * @author Andrey Baboshin
 */

#ifndef TIMER_IMPL_H_
#define TIMER_IMPL_H_

#include <types.h>
#include <kernel/irq.h>
#include <lib/list.h>

#ifndef __ASSEMBLER__

struct sys_tmr {
	struct list_head lnk;
	uint32_t   load;
	uint32_t   cnt;
	TIMER_FUNC handle;
	void       *param;
	bool       is_preallocated;
};

#endif /*__ASSEMBLER__*/
#endif /* TIMER_IMPL_H_ */

