/**
 * @file
 * @brief Tests thread suspend/resume methods.
 *
 * @details The test create two threads, the first with a high priority
 *      the second with a low priority, Both of them create with (suspend) flag
 *      THREAD_FLAG_SUSPENDED. Than the low priority thread is waked up and it
 *      execute while it will not finished (the main thread call thread_join).
 *      Then resume the high thread. The test checks a correct sequence of
 *      these stage.
 *
 * @date 17.04.11
 * @author Eldar Abusalimov
 */

#include <embox/test.h>

#include <kernel/thread/api.h>

EMBOX_TEST_SUITE("Thread suspend/resume");

static void *low_run(void *);
static void *high_run(void *);

TEST_CASE() {
	struct thread *low = NULL, *high = NULL;
	void *ret;

	test_assert_zero(
			thread_create(&high, THREAD_FLAG_SUSPENDED, high_run, NULL));
	test_assert_not_null(high);
	test_assert_zero(thread_set_priority(high, THREAD_PRIORITY_HIGH));

	test_assert_zero(thread_create(&low, THREAD_FLAG_SUSPENDED, low_run, high));
	test_assert_not_null(low);
	test_assert_zero(thread_set_priority(low, THREAD_PRIORITY_LOW));

	test_emit('a');

	test_assert_zero(thread_launch(low));
	test_assert_zero(thread_join(low, &ret));
	test_assert_null(ret);

	test_emit('e');

	test_assert_zero(thread_launch(high));
	test_assert_zero(thread_join(high, &ret));
	test_assert_null(ret);

	test_assert_emitted("abcdef");
}

static void *low_run(void *arg) {
	struct thread *high = (struct thread *) arg;

	test_emit('b');
	thread_launch(high);
	test_emit('d');

	return NULL;
}

static void *high_run(void *arg) {
	test_emit('c');
	thread_suspend(thread_self());
	test_emit('f');

	return NULL;
}
