/**
 * @file
 *
 * @brief
 *
 * @date 19.10.2011
 * @author Anton Bondarev
 * @author Anton Kozlov 
 */

#include <pnet/core.h>
#include <util/ring_buff.h>
#include <kernel/thread/api.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(rx_thread_init);

#define RX_THRD_CNT PNET_PRIORITY_COUNT 
#define RX_THRD_BUF_SIZE 0x10

static struct thread *pnet_rx_threads[RX_THRD_CNT];

static void *pnet_rx_thread_hnd(void *args) {
	struct ring_buff *buf = (struct ring_buff *) args;
	net_packet_t pack;
	while (1) {
		if (buf->cnt == 0) {
			thread_suspend(thread_self());
			continue;
		}
		ring_buff_deque(buf, &pack);
		pnet_process(pack);
	}
	return NULL;
}	

static net_packet_t pack_bufs[RX_THRD_CNT][RX_THRD_BUF_SIZE];
static struct ring_buff c_bufs[RX_THRD_CNT];

static int rx_thread_init(void) {
	for (int i = 0; i < RX_THRD_CNT; i++) {
		ring_buff_init(&c_bufs[i], sizeof(net_packet_t), RX_THRD_BUF_SIZE, (void *) pack_bufs[i]);
		thread_create(&pnet_rx_threads[i], 0, pnet_rx_thread_hnd, &c_bufs[i]);
	}
	return 0;
}

int pnet_rx_thread_add(net_packet_t pack) {
	net_prior_t prior = pack->node->prior;
	
	ring_buff_enque(&c_bufs[prior], &pack);
	
	thread_resume(pnet_rx_threads[prior]);

	return 0;	
}

