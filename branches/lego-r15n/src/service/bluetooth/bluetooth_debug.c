/**
 * @file
 * @brief debug bluetooth front-end
 *
 * @date 7.07.11 
 * @author Anton Kozlov
 */

#include <types.h>
#include <embox/unit.h>

#include <drivers/bluetooth.h>

#define BUFF_SIZE 256

EMBOX_UNIT_INIT(bluetooth_debug_init);

#if 1
static uint8_t read_buff[BUFF_SIZE];
static int pos = 0;

static int handler(int msg, uint8_t *buff) {
	if (msg == BT_DRV_MSG_READ) {
		pos++;
	}
	bluetooth_read(&(read_buff[pos]), 1);
	return 0;
}
#endif
int bluetooth_debug_init(void) {
	bluetooth_set_handler(handler);
	return 0;
}


