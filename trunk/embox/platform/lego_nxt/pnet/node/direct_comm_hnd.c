/**
 * @file
 * @brief
 *
 * @date 28.10.2011
 * @author Anton Kozlov
 */

#include <types.h>
#include <stdio.h>
#include <string.h>
#include <embox/unit.h>

#include <drivers/nxt/motor.h>
#include <drivers/nxt/sensor.h>
#include <drivers/nxt/direct_comm.h>
#include <drivers/bluetooth.h>

#include <pnet/core.h>
#include <pnet/node.h>
#include <pnet/repo.h>

#include <kernel/prom_printf.h>

EMBOX_UNIT_INIT(node_dc_init);

static struct lego_dc_msg dc_out_msg;

static int reply_need(struct lego_dc_msg *dc) {
	return !(dc->type & 0x80);
}

static void reply_handle(uint8_t status, uint8_t cmd, int addit_len, struct lego_dc_msg *dc_out_msg) {
	int extra_len = sizeof(dc_out_msg->type) + 
		sizeof(dc_out_msg->command) + sizeof(dc_out_msg->body[0]); // 3
	dc_out_msg->len = addit_len + extra_len;
	dc_out_msg->type = 0x02;
	dc_out_msg->command = cmd;
	dc_out_msg->body[0] = status;
	bluetooth_write((uint8_t *) dc_out_msg, sizeof(dc_out_msg->len) + extra_len + addit_len);
}

#define SENSOR_VALUE_THRESHOLD 200

static int sensor_send(uint8_t sensor_id, int *addit_len, uint8_t addit_msg[]) {
	sensor_val_t sens_val =  nxt_sensor_get_val(nxt_get_sensor(sensor_id));
	memset(addit_msg, 0, 16);

	addit_msg[3] = sensor_id;
	addit_msg[4] = 1;
	addit_msg[5] = 1;
	addit_msg[8] = (sens_val >> 8) & 0xff;
	addit_msg[9] = sens_val & 0xff;
	addit_msg[10] = addit_msg[8];
	addit_msg[11] = addit_msg[9];
	addit_msg[14] = (sens_val > SENSOR_VALUE_THRESHOLD ? 0 : 1);
	*addit_len = 16;
	return 0;
}

static int keep_alive_send(int *addit_len, uint8_t addit_msg[]) {
	*addit_len = 0;
#ifdef LEGO_COMPATIBLE 
//	printf("Hi! I'm Lego =(\n");
	return 0;
#else 
	printf("Hi! I'm Embox!\n");
	return 1;
#endif

}

static int handle_body(struct lego_dc_msg *msg, int *addit_len, uint8_t addit_msg[]) {
	uint8_t power;
	uint8_t *buff = msg->body;

	switch (msg->command) {
	case DC_SET_OUTPUT_STATE:
		power = buff[1];
		if (buff[0] != 0xff) {
			nxt_motor_set_power(nxt_get_motor(buff[0]), power);
		} else {
			nxt_motor_set_power(NXT_MOTOR_A, power);
			nxt_motor_set_power(NXT_MOTOR_B, power);
			nxt_motor_set_power(NXT_MOTOR_C, power);
		}
		*addit_len = 0;
		return 0;
	case DC_GET_INPUT_VALUES:
		return sensor_send(buff[0], addit_len, addit_msg);
	case DC_KEEP_ALIVE:
		return keep_alive_send(addit_len, addit_msg);
	case DC_EX_SET_M_OUTPUT_STATE:
		nxt_motor_set_power(NXT_MOTOR_A, buff[0]);
		nxt_motor_set_power(NXT_MOTOR_B, buff[1]);
		nxt_motor_set_power(NXT_MOTOR_C, buff[2]);
		*addit_len = 0;
		return 0;
	default:
		return 0;
	}
}

static int dc_rx_hnd(net_packet_t pack) {
	struct lego_dc_msg *msg;
	int addit_len = 0;
	int status;
	
	msg = (struct lego_dc_msg *) pnet_pack_get_data(pack);

	status = handle_body(msg, &addit_len, dc_out_msg.body + 1);

	if (reply_need(msg)) {
	    reply_handle(status, msg->command, addit_len, &dc_out_msg);
	}

	pnet_pack_free(pack);
	return NET_HND_SUPPRESSED;
}

static int node_dc_init(void) {
	return 0;
}

PNET_NODE_DEF("nxt direct handler",  {
		.rx_hnd = dc_rx_hnd,
		.tx_hnd = NULL
	});
