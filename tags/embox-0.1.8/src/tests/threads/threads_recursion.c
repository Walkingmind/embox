/**
 * @file
 * @brief Tests thread with recursion.
 *
 * @date 09.05.2010
 * @author Dmitry Avdyukhin
 */

#include <embox/test.h>
#include <kernel/thread.h>
#include <kernel/scheduler.h>
#include <errno.h>
#include <assert.h>

#define THREAD_STACK_SIZE 0x1000
#define MAX_DEPTH 100
static char recursion_stack[THREAD_STACK_SIZE];
static struct thread *recursion_thread;

EMBOX_TEST(run_test)
;

/**
 * Shows natural number on the screen and maybe calls itself.
 * @param i shown number. if i < MAX_DEPTH f calls itself.
 */
void f(int i) {
	TRACE("%d ", i);
	if (i < MAX_DEPTH) {
		f(i+1);
	}
	TRACE("-%d ", i);
}

/**
 * Starts recursion.
 * Shows natural numbers.
 */
static void recursion_run(void) {
	f(1);
}


/**
 * Test, which writes some numbers using recursion.
 *
 * If MAX_DEPTH = 100, then error occurs (maybe stack overflow).
 *
 * @retval 0 if test is passed
 * @retval -EINVAL if an error occurs.
 */
static int run_test() {
	TRACE("\n");

	recursion_thread =
		thread_create(recursion_run, recursion_stack + THREAD_STACK_SIZE);

	assert(recursion_thread != NULL);

	thread_start(recursion_thread);

	TRACE("\nBefore start\n");
	scheduler_start();
	scheduler_stop();
	return 0;
}
