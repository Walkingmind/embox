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
//static time64_t f, s, d;
//static time64_t total, min, max;
static unsigned int f, s, d;
static unsigned int total, min, max;
static struct itimer it;

static void *thread2_handler(void *arg) {
	event_init(&e, "event");

	for (int i = 0; i < SLEEP_COUNT; i++) {
		event_wait(&e, EVENT_TIMEOUT_INFINITE);
		s = itimer_read(&it);

		d = s - f;

		if (i == 0) {
			min = d; max = d;
		} else {
			if (min > d) min = d;
			if (max < d) max = d;
		}

		total += d;
	}

	return NULL;
}

static int run(int argc, char **argv) {
	struct thread *t;

	cs = clock_source_get_best(CS_ANY);
	itimer_init(&it, cs, 0);

	printf("Clock source: %s\n", cs->name);

	total = 0; min = 0; max = 0;

	thread_create(&t, THREAD_FLAG_DETACHED | THREAD_FLAG_PRIORITY_HIGHER, &thread2_handler, NULL);

	for (int i = 0; i < SLEEP_COUNT; i++) {
		f = itimer_read(&it);
		event_notify(&e);
	}

	printf("TOTAL: %d\n", total);
	printf("MIN: %d\n", min);
	printf("MAX: %d\n", max);

	return ENOERR;
}
