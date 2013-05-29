/**
 * @file
 * @brief
 *
 * @date 16.11.2012
 * @author Anton Bulychev
 */

#include <stdio.h>
#include <errno.h>
#include <framework/example/self.h>
#include <kernel/thread.h>
#include <kernel/syscall_caller.h>
#include <kernel/printk.h>
#include <kernel/irq.h>

EMBOX_EXAMPLE(run);

#define NRS 100000000

SYSCALL1(1,int,syscall_1,int,arg1);
extern int sys_1(int arg1);

long long total1, total2;
long long min1, min2;
long long max1, max2;
long long avg1, avg2;

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


static void *thread_syscall(void *arg) {
	long long end, start, d, total = 0, min, max;

	irq_lock();
	for (int i = 0; i < NRS; i++) {
		start = rdtsc();
		syscall_1(i);
		end = rdtsc();

		d = end - start;
		total += d;
		if (i == 0 || min > d) min = d;
		if (i == 0 || max < d) max = d;
	}
	irq_unlock();

	total1 = total;
	min1 = min;
	max1 = max;
	avg1 = total / NRS;
	return NULL;
}

static void *thread_nosyscall(void *arg) {
	long long end, start, d, total = 0, min, max;

	irq_lock();
	for (int i = 0; i < NRS; i++) {
		start = rdtsc();
		sys_1(i);
		end = rdtsc();

		d = end - start;
		total += d;
		if (i == 0 || min > d) min = d;
		if (i == 0 || max < d) max = d;
	}
	irq_unlock();

	total2 = total;
	min2 = min;
	max2 = max;
	avg2 = total / NRS;
	return NULL;
}

static int run(int argc, char **argv) {
	struct thread *thread;

	printf("Total calls: %d\n", NRS);

	printf("Running syscall thread.\n");
	thread_create(&thread, 0, thread_syscall, NULL);
	thread_join(thread, NULL);

	printf("Total time: %lld, min: %lld, max: %lld: avg: %lld\n", total1, min1, max1, avg1);

	printf("Running nosyscall thread.\n");
	thread_create(&thread, 0, thread_nosyscall, NULL);
	thread_join(thread, NULL);

	printf("Total time: %lld, min: %lld, max: %lld, avg: %lld\n", total2, min2, max2, avg2);


	printf("Diff total: %lld, min: %lld, max: %lld, avg: %lld\n", total1 - total2, min1 - min2, max1 - max2, avg1 - avg2);

	return ENOERR;
}
