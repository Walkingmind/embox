/**
 * @file
 * @brief
 *
 * @date 24.04.2013
 * @author Anton Bulychev
 */

#include <framework/example/self.h>

#include <errno.h>
#include <stdio.h>

#include <hal/ipl.h>

#include <kernel/time/clock_source.h>
#include <kernel/time/ktime.h>
#include <kernel/time/itimer.h>

EMBOX_EXAMPLE(run);

#define COUNT 10
#define CYCLE 100000000

static unsigned long long f, s, d;

static inline unsigned long long rdtsc(void) {
	unsigned hi, lo;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
}

static int run(int argc, char **argv) {
	ipl_t ipl;
	for (int i = 1; ; i++) {
		ipl = ipl_save();
		{
			f = rdtsc();
			for (volatile int j = 0; j < CYCLE; j++) ;
			s = rdtsc();
		}
		ipl_restore(ipl);

		d = s - f;
		printf("CYCLE #%5d: %9lld\n", i, d);
	}

	return ENOERR;
}
