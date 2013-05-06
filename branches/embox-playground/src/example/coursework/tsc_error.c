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

#define COUNT 500
#define CYCLE 100000000

static unsigned long long f, s, d;

static inline void set_cr0(unsigned int val) {
	asm ("mov %0, %%cr0" : :"r" (val));
}

static inline unsigned int get_cr0(void) {
	unsigned int _cr0;
	asm ("mov %%cr0, %0":"=r" (_cr0));
	return _cr0;
}

static inline unsigned long long rdtsc(void) {
	unsigned hi, lo;
	__asm__ __volatile__(
			"cpuid\n\t"
			"rdtsc"
		: "=a"(lo), "=d"(hi)
		: "a"(0)
//		: "%ebx", "%ecx"
	);
	return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
}

static inline void cycle(int top) {
	__asm__ __volatile__ (
			"movl $0, %%eax\n\t"
			"cc:\n\t"
			"inc %%eax\n\t"
			"cmp %%ebx, %%eax\n\t"
			"jl cc"
		:
		: "b"(top)
		: "%eax"
	);
}

#define DIFF_VAL 20

unsigned long long val[DIFF_VAL];
int count[DIFF_VAL];

static int run(int argc, char **argv) {
	ipl_t ipl;
	int i, j;

//	set_cr0(get_cr0() | (1UL << 30)); /* Disable caching */

	for (i = 1; i <= COUNT; i++) {

		ipl = ipl_save();
		{
			f = rdtsc();
			//for (volatile int j = 0; j < CYCLE; j++) ;
			cycle(CYCLE);
			s = rdtsc();
		}
		ipl_restore(ipl);

		d = s - f;
		//printf("CYCLE #%5d: %9lld\n", i, d);

		for (j = 0; j < DIFF_VAL; j++) {
			if (val[j] == d) {
				count[j]++;
				break;
			}

			if (count[j] == 0) {
				val[j] = d;
				count[j] = 1;
				break;
			}
		}

		if (j == DIFF_VAL) {
			printf("Too many different values!\n");
			break;
		}
	}

	printf("\nSummary (%d iterations):\n", i - 1);
	for (j = 0; j < DIFF_VAL; j++) {
		if (count[j] == 0) break;
		printf("VAL: %9lld, COUNT: %d\n", val[j], count[j]);
	}

	return ENOERR;
}
