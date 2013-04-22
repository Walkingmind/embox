/**
 * @file
 * @brief
 *
 * @date 22.04.2013
 * @author Anton Bulychev
 */

#include <framework/example/self.h>

#include <errno.h>
#include <time.h>
#include <stdio.h>

#include <kernel/thread.h>
#include <kernel/thread/event.h>

EMBOX_EXAMPLE(run);

#define SLEEP_COUNT 100000

struct event e;
clock_t f, s, total;


static void *thread2_handler(void *arg) {
	event_init(&e, "event");

	for (int i = 0; i < SLEEP_COUNT; i++) {
		event_wait(&e, EVENT_TIMEOUT_INFINITE);
		s = clock();
		total += s - f;
	}

	return NULL;
}

static int run(int argc, char **argv) {
	struct thread *t;

	total = 0;

	thread_create(&t, THREAD_FLAG_DETACHED | THREAD_FLAG_PRIORITY_HIGHER, &thread2_handler, NULL);

	for (int i = 0; i < SLEEP_COUNT; i++) {
		f = clock();
		event_notify(&e);
	}

	printf("TOTAL: %d\n", (int) total);

	return ENOERR;
}
