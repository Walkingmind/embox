/**
 * @file
 * @brief
 *
 * @date 26.12.2012
 * @author Anton Bulychev
 */

#include <kernel/cpu.h>

/* TODO: Delete it */
#ifdef SMP

#include <module/embox/driver/interrupt/lapic.h>

unsigned int cpu_get_id(void) {
	return lapic_id();
}

#endif /* SMP */
