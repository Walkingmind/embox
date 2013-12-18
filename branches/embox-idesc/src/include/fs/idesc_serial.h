/**
 * @file
 *
 * @date Dec 18, 2013
 * @author: Anton Bondarev
 */

#ifndef IDESC_SERIAL_H_
#define IDESC_SERIAL_H_

#include <fs/idesc.h>
#include <drivers/uart_device.h>

struct idesc_serial {
	struct idesc idesc;
	struct uart uart;
};

extern struct idesc *idesc_serial_create(struct node *node, const char *name);

#endif /* IDESC_SERIAL_H_ */
