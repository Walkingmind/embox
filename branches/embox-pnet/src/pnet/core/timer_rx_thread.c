/**
 * @file
 *
 * @brief
 *
 * @date 12.04.2013
 * @author Alexander Kalmuk
 */

#include <stdio.h>
#include <fcntl.h>
#include <kernel/thread.h>
#include <framework/cmd/api.h>
#include <stdlib.h>
#include <pnet/core.h>
#include <pnet/pnet_pack.h>
#include <pnet/timer.h>

#include <profiler/tracing/trace.h>
#include <profiler/sampling.h>

#define MAX_PNET_PRIORITY_COUNT 64
#define TESTING_PRIO_CNT    1
#define ITERATIONS_PER_TEST 100
#define TESTS_PER_PRIO      3
#define TESTS_ALL           (TESTS_PER_PRIO * TESTING_PRIO_CNT)

static int pnet_time_info[MAX_PNET_PRIORITY_COUNT][TESTS_PER_PRIO];

static FILE *results;
static int completed_tests;

static int jiffies_freq = 1000;

static int pnet_test_save_result(int prio, int test_nr, const char *testname, int value) {
	if (NULL == results) {
		return -1;
	}

	if (++pnet_time_info[prio][test_nr] <= ITERATIONS_PER_TEST) {
		fprintf(results, "%s(%d): %d\n", testname, prio, value);
	} else if (pnet_time_info[prio][test_nr] == ITERATIONS_PER_TEST + 1) {
		printf("%d%% of tests completed\n", completed_tests * 100 / TESTS_ALL);
		completed_tests++;
	}

	return 0;
}

time64_t trace_block_get_total_time(struct __trace_block *tb);

void pnet_timer_hnd_stopped(struct pnet_pack *pack) {
	struct timespec ts;
	unsigned int elapsed_time;
	static int completed;
	struct __trace_block *tb;
	char *argv[2] = {"cat", "/tmp/pnet_results"};

	if (completed) {
		return;
	}

	if (completed_tests == TESTS_ALL) {
		completed = 1;
		printf("All test are completed. Iterations per test - %d\n", ITERATIONS_PER_TEST);
		cmd_exec(cmd_lookup("cat"), 2, argv);
		return;
	}

	ktime_get_timespec(&ts);

	/* total time */
	ktime_get_timespec(&ts);
	ts = timespec_sub(ts, pack->stat.start_time);
	elapsed_time = timespec_to_ns(&ts) / 1000;

	/* time in interrupts */
	tb = trace_block_get_by_name("irq_handler_tb");
	ts = ns_to_timespec(trace_block_get_total_time(tb));
	ts = timespec_sub(ts, pack->stat.last_interrupts_time);

	sched_lock();
	{
		pnet_test_save_result(pack->priority, 0, "pnet_total", elapsed_time);

		/* actual time on cpu */
		pnet_test_save_result(pack->priority, 1, "pnet_running", timespec_to_ns(&pack->stat.running_time) / 1000);

		pnet_test_save_result(pack->priority, 2, "pnet_inside_irq", timespec_to_ns(&ts) / 1000);
	}
	sched_unlock();

	//assert(elapsed_time >= timespec_to_ns(&pack->stat.running_time)/1000, "elapsed_time-%d, running_time- %d\n",
	//		elapsed_time, (int)(timespec_to_ns(&pack->stat.running_time) / 1000));
}

void pnet_timer_hnd_enter(struct pnet_pack *pack) {
	sched_lock();
	{
		pack->stat.thread_last_sync = clock_to_timespec(jiffies_freq, thread_self()->last_sync);
		pack->stat.thread_run_time = clock_to_timespec(jiffies_freq, thread_self()->running_time);
		ktime_get_timespec(&pack->stat.last_sync);
	}
	sched_unlock();
}

void pnet_timer_hnd_leave(struct pnet_pack *pack) {
	struct timespec ts;

	sched_lock();
	{
		ktime_get_timespec(&ts);
		ts = timespec_sub(ts, clock_to_timespec(jiffies_freq, thread_self()->last_sync));
		pack->stat.running_time = timespec_add(pack->stat.running_time, ts);

		ts = timespec_sub(clock_to_timespec(jiffies_freq, thread_self()->running_time),
				pack->stat.thread_run_time);
		pack->stat.running_time = timespec_add(pack->stat.running_time, ts);

		ts = timespec_sub(pack->stat.last_sync, pack->stat.thread_last_sync);
		pack->stat.running_time = timespec_sub(pack->stat.running_time, ts);
	}
	sched_unlock();
}

struct thread *pnet_rx_get_thread(int prio);

#include <prom/prom_printf.h>

static bool cond_handler(void *data) {
	return (thread_self() == pnet_rx_get_thread(1));
}

int pnet_timer_init(const char *output_file) {
	struct __trace_block *tb;

	tb = trace_block_get_by_name("irq_handler_tb");
	trace_point_set_condition(tb->begin, NULL, cond_handler);
	trace_point_set_condition(tb->end, NULL, cond_handler);

	results = fopen(output_file, "rw");
	return (NULL == results ? -1 : 0);
}
