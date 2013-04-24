/**
 * @file
 * @brief
 *
 * @date 22.04.2013
 * @author Anton Bulychev
 */

#include <framework/example/self.h>

#include <errno.h>
#include <stdio.h>

#include <kernel/thread.h>
#include <kernel/thread/event.h>
#include <kernel/time/clock_source.h>
#include <kernel/time/ktime.h>
#include <kernel/time/itimer.h>

EMBOX_EXAMPLE(run);

#define SLEEP_COUNT 100000

static struct event e;

static struct clock_source *cs;
static time64_t f, s, total;
static struct itimer it;

static void *thread2_handler(void *arg) {
	event_init(&e, "event");

	for (int i = 0; i < SLEEP_COUNT; i++) {
		event_wait(&e, EVENT_TIMEOUT_INFINITE);
		s = itimer_read(&it);
		total += s - f;
	}

	return NULL;
}

static int run(int argc, char **argv) {
	struct thread *t;

	cs = clock_source_get_best(CS_ANY);
	itimer_init(&it, cs, 0);

	total = 0;

	thread_create(&t, THREAD_FLAG_DETACHED | THREAD_FLAG_PRIORITY_HIGHER, &thread2_handler, NULL);

	for (int i = 0; i < SLEEP_COUNT; i++) {
		f = itimer_read(&it);
		event_notify(&e);
	}

	printf("TOTAL: %d\n", (int) total);

	return ENOERR;
}
