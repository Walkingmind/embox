/**
 * @file
 * @brief
 *
 * @date 17.10.12
 * @author Alexander Kalmuk
 * @author Ilia Vaprol
 */

#ifndef KERNEL_TASK_IO_SYNC_H_
#define KERNEL_TASK_IO_SYNC_H_

#include <kernel/manual_event.h>

struct io_sync {
	struct manual_event can_read;
	struct manual_event can_write;
	int error_on_read;
	int error_on_write;
	struct manual_event *on_reading;
	struct manual_event *on_writing;
	struct manual_event *on_error;
};

enum io_sync_op {
	IO_SYNC_READING,
	IO_SYNC_WRITING
};

#define IO_SYNC_TIMEOUT_INFINITE MANUAL_EVENT_TIMEOUT_INFINITE

extern void io_sync_init(struct io_sync *ios, int r_set,
		int w_set);
extern void io_sync_enable(struct io_sync *ios,
		enum io_sync_op op);
extern void io_sync_disable(struct io_sync *ios,
		enum io_sync_op op);
extern void io_sync_error_on(struct io_sync *ios,
		enum io_sync_op op);
extern void io_sync_error(struct io_sync *ios);
extern int io_sync_ready(struct io_sync *ios,
		enum io_sync_op op);
extern void io_sync_notify(struct io_sync *ios,
		enum io_sync_op op, struct manual_event *on_op);
extern int io_sync_wait(struct io_sync *ios, enum io_sync_op op,
		unsigned long timeout);

#endif /* KERNEL_TASK_IO_SYNC_H_ */