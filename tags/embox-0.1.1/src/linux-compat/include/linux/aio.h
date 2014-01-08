/**
 * @file
 * @brief Describes asynchronous I/O operations
 *
 * @date 13.01.2010
 * @author Anton Bondarev
 */

#ifndef AIO_H_
#define AIO_H_

#include <lib/list.h>
/**
 * AIO control block structure use in asynchronous I/O operations
 * we use it's in kernel mode instead of <aio.h> from standart library.
 * Now it use only for compatible socket interface.
 */
struct kiocb {
	struct list_head	ki_run_list;
	long			ki_flags;
	int			ki_users;
	unsigned		ki_key;		/* id of this request */
};

#endif /* AIO_H_ */