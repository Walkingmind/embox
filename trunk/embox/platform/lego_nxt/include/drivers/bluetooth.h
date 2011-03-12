/**
 * @file
 *
 * @brief
 *
 * @date 24.02.2011
 * @author Anton Bondarev
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <types.h>

#define MSG_BEGIN_INQUIRY 0
#define MSG_CANCEL_INQUIRY 1
#define MSG_CONNECT 2
#define MSG_OPEN_PORT 3
#define MSG_LOOKUP_NAME 4
#define MSG_ADD_DEVICE 5
#define MSG_REMOVE_DEVICE 6
#define MSG_DUMP_LIST 7
#define MSG_CLOSE_CONNECTION 8
#define MSG_ACCEPT_CONNECTION 9
#define MSG_PIN_CODE 10
#define MSG_OPEN_STREAM 11
#define MSG_START_HEART 12
#define MSG_HEARTBEAT 13
#define MSG_INQUIRY_RUNNING 14
#define MSG_INQUIRY_RESULT 15
#define MSG_INQUIRY_STOPPED 16
#define MSG_LOOKUP_NAME_RESULT 17
#define MSG_LOOKUP_NAME_FAILURE 18
#define MSG_CONNECT_RESULT 19
#define MSG_RESET_INDICATION 20
#define MSG_REQUEST_PIN_CODE 21
#define MSG_REQUEST_CONNECTION 22
#define MSG_LIST_RESULT 23
#define MSG_LIST_ITEM 24
#define MSG_LIST_DUMP_STOPPED 25
#define MSG_CLOSE_CONNECTION_RESULT 26
#define MSG_PORT_OPEN_RESULT 27
#define MSG_SET_DISCOVERABLE 28
#define MSG_CLOSE_PORT 29
#define MSG_CLOSE_PORT_RESULT 30
#define MSG_PIN_CODE_ACK 31
#define MSG_DISCOVERABLE_ACK 32
#define MSG_SET_FRIENDLY_NAME 33
#define MSG_SET_FRIENDLY_NAME_ACK 34
#define MSG_GET_LINK_QUALITY 35
#define MSG_LINK_QUALITY_RESULT 36
#define MSG_SET_FACTORY_SETTINGS 37
#define MSG_SET_FACTORY_SETTINGS_ACK 38
#define MSG_GET_LOCAL_ADDR 39
#define MSG_GET_LOCAL_ADDR_RESULT 40
#define MSG_GET_FRIENDLY_NAME 41
#define MSG_GET_DISCOVERABLE 42
#define MSG_GET_PORT_OPEN 43
#define MSG_GET_FRIENDLY_NAME_RESULT 44
#define MSG_GET_DISCOVERABLE_RESULT 45
#define MSG_GET_PORT_OPEN_RESULT 46
#define MSG_GET_VERSION 47
#define MSG_GET_VERSION_RESULT 48
#define MSG_GET_BRICK_STATUSBYTE_RESULT 49
#define MSG_SET_BRICK_STATUSBYTE_RESULT 50
#define MSG_GET_BRICK_STATUSBYTE 51
#define MSG_SET_BRICK_STATUSBYTE 52

typedef struct {
	uint8_t length;
	uint8_t type;
	uint8_t content[256];
	uint16_t sum;
}bt_message_t;

extern size_t nxt_bluetooth_read(uint8_t *buff, size_t len);

extern size_t nxt_bluetooth_write(uint8_t *buff, size_t len);

extern void bt_handle(uint8_t *buff);

extern int bt_wrap(bt_message_t *header, uint8_t *buffer); 

extern void bt_unwrap(bt_message_t *header, uint8_t *buffer);

#endif /* BLUETOOTH_H_ */
