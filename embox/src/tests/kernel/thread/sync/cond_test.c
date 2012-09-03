/**
 * @file
 * @brief Tests condition variable wait/signal methods.
 *
 * @date Sep 03, 2012
 * @author Bulychev Anton
 */

#include <embox/test.h>
#include <kernel/thread/sync/cond.h>
#include <unistd.h>

static struct thread *low, *high;
static cond_t c;
static struct mutex m;

EMBOX_TEST_SUITE("Condition variable test");

TEST_SETUP(setup);

TEST_CASE("General") {
	test_assert_zero(thread_resume(low));
	test_assert_zero(thread_join(low, NULL));
	test_assert_zero(thread_join(high, NULL));
	test_assert_emitted("abcdefgh");
}

static void *low_run(void *arg) {
	test_emit('a');
	test_assert_zero(thread_resume(high));
	test_emit('d');
	mutex_lock(&m);
	test_emit('e');
	cond_signal(&c);
	test_emit('f');
	mutex_unlock(&m);
	test_emit('h');
	return NULL;
}

static void *high_run(void *arg) {
	test_emit('b');
	mutex_lock(&m);
	test_emit('c');
	cond_wait(&c, &m);
	test_emit('g');
	return NULL;
}

static int setup(void) {
	thread_priority_t l = 10, h = 20;

	mutex_init(&m);
	cond_init(&c);
	test_assert_zero(thread_create(&low, THREAD_FLAG_SUSPENDED, low_run, NULL));
	test_assert_zero(thread_create(&high, THREAD_FLAG_SUSPENDED, high_run, NULL));
	test_assert_zero(thread_set_priority(low, l));
	test_assert_zero(thread_set_priority(high, h));

	return 0;
}

