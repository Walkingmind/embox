/**
 * @file
 * @brief Tests threads.
 *
 * @date 18.04.2010
 * @author Dmitry Avdyukhin
 */
#include <embox/test.h>
#include <kernel/thread.h>
#include <kernel/heap_scheduler.h>
#include <errno.h>
#include <assert.h>

#define THREAD_STACK_SIZE 0x1000

static char plus_stack[THREAD_STACK_SIZE];
static char minus_stack[THREAD_STACK_SIZE];
static char mult_stack[THREAD_STACK_SIZE];
static char natural_stack[THREAD_STACK_SIZE];
static struct thread *plus_thread;
static struct thread *minus_thread;
static struct thread *mult_thread;
static struct thread *natural_thread;

EMBOX_TEST(run_test)
;

/**
 * Writes "+".
 * Deletes minus_thread.
 */
static void plus_run(void) {
	thread_stop(minus_thread);
	thread_yield();
	TRACE("+");
}

/**
 * Endlessly writes "-".
 * Will be deleted.
 */
static void minus_run(void) {
	while (true) {
		TRACE("-");
	}
}

/**
 * Endlessly writes "*".
 */
static void mult_run(void) {
	while (true) {
		TRACE("*");
	}
}

/**
 * Endlessly writes natural numbers.
 */
static void natural_run(void) {
	for (int i = 1; ; i++) {
		TRACE("%d ", i);
	}
}

/**
 * Test, which infinitely writes "?", "+", "*" and
 * natural numbers on the screen.
 * Thread, which writes "-", will be deleted in plus_thread.
 *
 * @retval 0 if test is passed
 * @retval -EINVAL if an error occurs.
 */
static int run_test() {
	TRACE("\n");
	scheduler_init();

	plus_thread = thread_create(plus_run, plus_stack + THREAD_STACK_SIZE);
	natural_thread = thread_create(natural_run, natural_stack + THREAD_STACK_SIZE);
	minus_thread = thread_create(minus_run, minus_stack + THREAD_STACK_SIZE);
	mult_thread = thread_create(mult_run, mult_stack + THREAD_STACK_SIZE);

	assert(plus_thread != NULL);
	assert(minus_thread != NULL);
	assert(mult_thread != NULL);
	assert(natural_thread != NULL);

	thread_start(plus_thread);
	thread_start(natural_thread);
	thread_start(minus_thread);
	thread_start(mult_thread);

	TRACE("\nBefore start\n");
	scheduler_start();

	return 0;
}
