/**
 * @file
 *
 * @date 24.10.2010
 * @author Anton Kozlov
 */

#ifndef NXT_DIRECT_COMM_H_
#define NXT_DIRECT_COMM_H_

#define DC_SET_OUTPUT_STATE 0x04
#define DC_EX_SET_M_OUTPUT_STATE 0x20

#define MSG_SIZE_BYTE_CNT 2

int direct_comm_handle(uint8_t *buff);
int direct_comm_init_read(void); 

#endif /* NXT_DIRECT_COMM_H */


