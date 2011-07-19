/**
 * @file
 * @brief Bluetooth driver 
 *
 * @date 24.02.11
 * @author Anton Bondarev
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <types.h>

#include <embox/service/callback.h>

#define BT_DRV_MSG_CONNECTED 1
#define BT_DRV_MSG_READ 2
#define BT_DRV_MSG_DISCONNECTED 3

typedef int(*bt_comm_handler_t)(int msg, uint8_t *buff);

extern void bluetooth_set_handler(bt_comm_handler_t handler);

extern size_t bluetooth_read(uint8_t *buff, size_t len);
extern size_t bluetooth_write(uint8_t *buff, size_t len);

CALLBACK_DECLARE(bluetooth_uart);

#endif /* BLUETOOTH_H_ */
