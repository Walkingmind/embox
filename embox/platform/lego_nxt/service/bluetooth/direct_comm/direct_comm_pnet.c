/*
 * @file
 * @brief Lego NXT direct command manager
 *
 * @date 13.03.11
 * @author Anton Kozlov
 */
#include <types.h>
#include <string.h>

#include <drivers/nxt/direct_comm.h>
#include <drivers/bluetooth.h>

#include <pnet/core.h>
#include <pnet/repo.h>
#include <pnet/node.h>

#include <kernel/prom_printf.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(dc_pnet_init);

#define DC_BUFF_SIZE 0x20 /* lego_nxt direct command maximum length */

static int rx_hnd(net_packet_t pack);
PNET_NODE_DEF_NAME("nxt direct src", this, {
	.rx_hnd = rx_hnd
});

static uint8_t direct_comm_buff[DC_BUFF_SIZE];

static void send_to_net(unsigned char *data, int len) {
	net_packet_t pack = pnet_pack_alloc(&this, len);

	memcpy(pnet_pack_get_data(pack), (void *) data, len);

	pnet_entry(pack);

	return;
}

static int size = 0;

static int handle_size(uint8_t *buff) {
	return buff[0] + (buff[1] << 8);
}

static int direct_wait_body(void);
static int direct_get_header(void) {
#if 0
	prom_printf("%x;", direct_comm_buff[0]);
	bluetooth_read(direct_comm_buff, 1);
#endif		
	size = handle_size(direct_comm_buff);

	if (size > DC_BUFF_SIZE - MSG_SIZE_BYTE_CNT) {
		//TODO error length
	}
	CALLBACK_REG(bt_rx, direct_wait_body);
	bluetooth_read(direct_comm_buff + MSG_SIZE_BYTE_CNT, size);
	return 0;
}

static int direct_wait_body(void /*int msg, uint8_t *buff*/) {
	send_to_net(direct_comm_buff, MSG_SIZE_BYTE_CNT + size);
	//nxt_bt_set_rx_handle(direct_get_header);
	CALLBACK_REG(bt_rx, direct_get_header);
	bluetooth_read(direct_comm_buff, MSG_SIZE_BYTE_CNT);
	return 0;
}

static int rx_hnd(net_packet_t pack) {
	int res = NET_HND_SUPPRESSED;
	if (0 != strcmp("connect", pnet_pack_get_data(pack))) {
		return res;
	}
	CALLBACK_REG(bt_rx, direct_get_header);

	pnet_pack_free(pack);
	bluetooth_read(direct_comm_buff, MSG_SIZE_BYTE_CNT);
	return res;
}

static int dc_pnet_init(void) {
	return 0;
}       


