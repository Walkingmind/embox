/**
 * @file
 * @brief Event dispatcher implementation
 *
 * @date 16.03.11
 * @author Kirill Tyushev
 */

#include <lib/list.h>
#include <mem/misc/pool.h>
#include <kernel/softirq.h>
#include <kernel/evdispatch.h>

/** maximum count of messages in queue */
#define MAX_MSG_COUNT_IN_QUEUE 10

/** Handlers, that can handle message with specified id */
struct handler {
	void (*handler)(struct event_msg *msg);
};

/** pool for message in queue */
POOL_DEF(msg_queue_pool, struct event_msg, MAX_MSG_COUNT_IN_QUEUE);

/** Queue of messages, sent to handlers */
static LIST_HEAD(msg_queue);

/**
 * Tables of messages(message can be determine by it's id)
 * and functions, that can handle them.
 */
static struct handler handler_arr[EVENT_MSG_COUNT];


#include <embox/unit.h>
#define make_cache_name(name) \
		""#name""
#include <mem/misc/slab.h>
EMBOX_UNIT_INIT(event_dispatcher_init);

static int event_dispatcher_init(void) {
	cache_t *cache;

	cache = cache_create(make_cache_name(msg_queue_cache), sizeof(struct event_msg), MAX_MSG_COUNT_IN_QUEUE);

	return 0;
}

void event_dispatch(unsigned int softirq_nr, void *data) {
	while (!list_empty(&msg_queue)) {
		struct list_head *result = msg_queue.next;
		struct event_msg *msg = list_entry(result, struct event_msg, list);
		list_del(result);

		handler_arr[msg->id].handler(msg);

		pool_free(&msg_queue_pool, msg);
	}
}

/**
 * Create the message to add it to queue.
 *
 * @param id id, that corresponds to type of message
 * @param data data, that will be send in message
 * @return pointer to created message
 */
static struct event_msg *create_message(int id, void *data) {
	struct event_msg *msg = pool_alloc(&msg_queue_pool);
	msg->id = id;
	msg->data = data;
	return msg;
}

void event_send(int id, void *data) {
	struct event_msg *msg;

	if (id > EVENT_MSG_COUNT - 1)
			return;

	msg = create_message(id, data);
	list_add_tail(&msg->list, &msg_queue);
}

void event_register(int id, void (*handler)(struct event_msg *msg)) {
	if (id > EVENT_MSG_COUNT - 1)
		return;

	handler_arr[id].handler = handler;
}
