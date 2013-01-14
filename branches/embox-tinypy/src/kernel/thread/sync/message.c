/**
 * @file
 * @brief IPC messages implementation.
 *
 * @date 25.02.11
 * @author Dmitry Avdyukhin
 */

#include <kernel/thread/sync/message.h>

#include <stdbool.h>
#include <kernel/thread.h>
#include <kernel/thread/sched.h>

#define MESSAGE_POOL_SZ 100

/** Pool, containing messages to be occupied. */
static struct message message_pool[MESSAGE_POOL_SZ];
/** Shows what messages are free. */
static bool message_pool_mask[MESSAGE_POOL_SZ];

void message_send(struct message *message, struct thread *thread) {
	sched_lock();
	list_add_tail(&message->list, &thread->messages);
	if (thread->need_message) {
		thread->need_message = false;
		event_notify(&thread->msg_event);
	}
	sched_unlock();
}

struct message *message_receive(void) {
	struct list_head *ret;

	if (list_empty(&thread_self()->messages)) {
		thread_self()->need_message = true;
		event_wait(&thread_self()->msg_event, SCHED_TIMEOUT_INFINITE);
	}

	ret = thread_self()->messages.next;
	list_del_init(ret);
	return list_entry(ret, struct message, list);
}

struct message *message_new(void) {
	size_t i;
	for (i = 0; i < MESSAGE_POOL_SZ; i++) {
		if (!message_pool_mask[i]) {
			message_pool_mask[i] = true;
			return message_pool + i;
		}
	}
	return NULL;
}

int message_erase(struct message *message) {
	if (message == NULL) {
		return -1;
	}
	message_pool_mask[message - message_pool] = false;
	return 0;
}
