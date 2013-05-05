/**
 * @file
 * @brief Multi-thread (multi-priority) graph executer
 *
 * @date 19.10.2011
 * @author Anton Bondarev
 * @author Anton Kozlov
 */

#include <embox/unit.h>
#include <util/ring_buff.h>
#include <stdio.h>

#include <kernel/thread.h>
#include <kernel/thread/state.h>
#include <kernel/thread/event.h>

#include <pnet/core.h>
#include <pnet/pnet_pack.h>

EMBOX_UNIT_INIT(rx_thread_init);

#define RX_THRD_BUF_SIZE   0x10

#define PNET_PRIORITY_COUNT  OPTION_GET(NUMBER, pnet_priority_count)

struct thread *pnet_rx_threads[PNET_PRIORITY_COUNT];

#ifdef PNET_THREAD_DEBUG
static int running[PNET_PRIORITY_COUNT];
static int sleeping[PNET_PRIORITY_COUNT];
#endif

struct pnet_wait_unit {
	struct event event;
	struct ring_buff buff;
};

static net_packet_t pack_bufs[PNET_PRIORITY_COUNT][RX_THRD_BUF_SIZE];
static struct pnet_wait_unit pack_storage[PNET_PRIORITY_COUNT];

static void *pnet_rx_thread_hnd(void *args) {
	struct pnet_wait_unit *unit = (struct pnet_wait_unit *) args;
	struct pnet_pack *pack;

	while (1) {
		if (unit->buff.cnt == 0) {
			event_wait(&unit->event, EVENT_TIMEOUT_INFINITE);
			continue;
		}
		ring_buff_dequeue(&unit->buff, &pack, 1);
		pnet_process(pack);
	}
	return NULL;
}

static int rx_thread_init(void) {
	extern int pnet_timer_init(const char *output_file);

	pnet_timer_init("/tmp/pnet_results");

	for (size_t i = 0; i < PNET_PRIORITY_COUNT; i++) {

		event_init(&pack_storage[i].event, "pack_arrived");

		ring_buff_init(&pack_storage[i].buff, sizeof(net_packet_t), RX_THRD_BUF_SIZE,
				(void *) pack_bufs[i]);
		thread_create(&pnet_rx_threads[i], 0, pnet_rx_thread_hnd, &pack_storage[i]);

		thread_set_priority(pnet_rx_threads[i], THREAD_PRIORITY_DEFAULT + 1 + i);
	}

	return 0;
}

struct thread *pnet_rx_get_thread(int prio) {
	assert(prio < PNET_PRIORITY_COUNT);
	return pnet_rx_threads[prio];
}

int pnet_rx_thread_add(struct pnet_pack *pack) {
	uint32_t prio;

	prio = pack->priority;
	ring_buff_enqueue(&pack_storage[prio].buff, &pack, 1);
	event_notify(&pack_storage[prio].event);

	return 0;
}
