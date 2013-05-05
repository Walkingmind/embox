/**
 * @file
 *
 * @brief
 *
 * @date 15.05.2012
 * @author Anton Bondarev
 */
#include <stdio.h>
#include <errno.h>
#include <framework/example/self.h>

#include <kernel/time/clock_source.h>
#include <kernel/time/ktime.h>
#include <kernel/time/itimer.h>

#include <kernel/thread.h>
#include <profiler/tracing/trace.h>

EMBOX_EXAMPLE(run);

static struct clock_source *cs;

static int measured_loop(int cycles_loop) {
	volatile int i;
	clock_t cl, thread_clock;
	int interrupts;
	struct __trace_point *p = trace_point_get_by_name("interrupt");

	cl = clock();
	thread_clock = thread_self()->running_time;
	interrupts = trace_point_get_value(p);

	for (i = 0; i < cycles_loop; i++) {
	}

	interrupts = trace_point_get_value(p) - interrupts;

	printf("spent = %d (%d, int - %d)\n", (int) (clock() - cl),
			(int) (thread_self()->running_time - thread_clock), interrupts);

	return 0;
}

static int run(int argc, char **argv) {
	cs = clock_source_get_best(CS_ANY);

	for (int i = 0; i < 100; i++) {
		measured_loop(100000);
	}

	return ENOERR;
}
