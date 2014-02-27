/**
 * @file
 *
 * @brief Testing interface for thread with different priority
 *
 * @date Oct 17, 2012
 * @author: Anton Bondarev
 */

#include <embox/test.h>

#include <kernel/thread.h>
#include <kernel/thread/thread_register.h>
#include <kernel/time/ktime.h>
#include <kernel/task.h>
#include <framework/mod/options.h>

#include <err.h>

EMBOX_TEST_SUITE("test for different priority threads");

#define THREADS_QUANTITY OPTION_GET(NUMBER, threads_quantity)
#define __str(x) #x
#define str(x) __str(x)

static void *thread_run(void *arg) {
	ksleep(2 * 1000);
	return 0;
}

TEST_CASE("Create " str(THREADS_QUANTITY) " threads with"
		" different priority") {
	for (int i = 0; i < THREADS_QUANTITY; i++) {
		struct thread *t;
		t = thread_create(THREAD_FLAG_NOTASK | THREAD_FLAG_SUSPENDED,
				thread_run, (void *) i);
		test_assert_zero(err(t));
		thread_register(task_kernel_task(), t);
		test_assert_zero(thread_set_priority(t, i));
		test_assert_zero(thread_detach(t));
		test_assert_zero(thread_launch(t));
	}
}
