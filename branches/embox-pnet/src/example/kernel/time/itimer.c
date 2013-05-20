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

#include <hal/ipl.h>

static int measured_loop(int cycles_loop) {
	volatile int i;
	time64_t t;

	t = cs->read(cs);

	for (i = 0; i < cycles_loop; i++) {
	}

	t = cs->read(cs) - t;

	printf("spent %lld\n", t);

	return 0;
}

static int run(int argc, char **argv) {
	//ipl_t ipl;
	//cs = clock_source_get_best(CS_ANY);

	cs = ktime_get_clock_source();
	printf("%s\n", cs->name);

	for (int i = 0; i < 100; i++) {
		measured_loop(1000);
	}

	return ENOERR;
}
