/**
 * @file
 *
 * @brief Tests changing thread's state by event.
 *
 * @date 18.12.2011
 * @author Anton Bondarev
 */

#include <unistd.h>

#include <kernel/thread/sched.h>
#include <kernel/thread/api.h>
#include <kernel/thread/event.h>
#include <kernel/time/ktime.h>

#include <embox/test.h>

EMBOX_TEST_SUITE("test for change thread state by events");

static void *thread_run(void *arg) {
	struct event *event = (struct event *)arg;

	event_wait(event, SCHED_TIMEOUT_INFINITE);
	return 0;
}

TEST_CASE("Create thread waiting event and then finish") {
	struct event sync_event;
	struct thread *thread;

	event_init(&sync_event, "sync_event");
	test_assert_zero(
				thread_create(&thread, 0, thread_run, &sync_event));
	ksleep(100);
	event_notify(&sync_event);

	test_assert_zero(thread_join(thread, NULL));
}
