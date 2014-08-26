/**
 * @file
 *
 * @author Eldar Abusalimov
 */

#include <stdbool.h>
#include <kernel/sched/current.h>
#include <kernel/sched/schedee.h>

void sched_wait_prepare_schedee(void) {
	struct schedee *s = schedee_get_current();

	// TODO SMP barrier? -- Eldar
	s->waiting = true;
}

void sched_wait_cleanup_schedee(void) {
	struct schedee *s = schedee_get_current();

	s->waiting = false;
	// TODO SMP barrier? -- Eldar
}

