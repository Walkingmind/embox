/**
 * @file
 * @brief Tests for sleep function
 *
 * @date 06.07.11
 * @author Ilia Vaprol
 */

#include <embox/test.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <kernel/thread/api.h>

EMBOX_TEST_SUITE("sleep suite");

#define EPSILON_BORDER 10
#define TIME_TO_SLEEP  20
#define NUM_THREADS     8

/**
 *  sleep( any_time )
 *  assert that real time for sleep different with any_time is less than EPSILON_BORDER
 */

TEST_CASE("one sleep") {
	/* TODO: change uint32_t to system time_t type */
	clock_t cur_time, epsilon;

	cur_time = clock();
	usleep(TIME_TO_SLEEP);
	epsilon = abs((int) (clock() - cur_time) - (int) TIME_TO_SLEEP);
	test_assert_true(epsilon < EPSILON_BORDER);
}

/**
 *  run ~3 threads (~3 times) with 1,2,3 sec wait
 *  assert right done sequence of threads
 */

static void * handler1(void* args) {
	usleep(TIME_TO_SLEEP * (uint32_t) args);
	test_emit('0' + (uint32_t) args);
	return NULL;
}

TEST_CASE("simple multi-threaded check") {
	struct thread *t1, *t2, *t3;

	/* Start threads */
	test_assert_zero(thread_create(&t1, 0, handler1, (void *) 1));
	test_assert_not_null(t1);
	test_assert_zero(thread_create(&t2, 0, handler1, (void *) 2));
	test_assert_not_null(t2);
	test_assert_zero(thread_create(&t3, 0, handler1, (void *) 3));
	test_assert_not_null(t3);

	/* join thread */
	test_assert_zero(thread_join(t1, NULL));
	test_assert_zero(thread_join(t2, NULL));
	test_assert_zero(thread_join(t3, NULL));

	test_assert_emitted("123");
}

/**
 * run NUM_THREADS threads and with progressive time to sleep
 * after execute buffer2 must be "87654321"
 */

static void * handler2(void* args) {
	usleep(TIME_TO_SLEEP * (NUM_THREADS - (uint32_t) args) + 1);
	test_emit('1' + (uint32_t) args);
	return NULL;
}

TEST_CASE("sleep sort") {
	uint32_t i;
	struct thread *t[NUM_THREADS];

	for (i = 0; i < NUM_THREADS; i++) {
		test_assert_zero(
				thread_create(&t[i], 0, handler2, (void *) i));
		test_assert_not_null(t[i]);
	}
	for (i = 0; i < NUM_THREADS; i++) {
		test_assert_zero(thread_join(t[i], NULL));
	}
	for (i=0;i<10;++i);
	test_assert_emitted("87654321");
}

TEST_CASE("sleep 0 seconds") {
	test_emit('1');
	usleep(0);
	test_emit('2');
	test_assert_emitted("12");
}
