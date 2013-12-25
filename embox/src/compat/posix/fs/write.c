/**
 * @file
 *
 * @date Nov 15, 2013
 * @author: Anton Bondarev
 */

#include <errno.h>
//#include <posix_errno.h>
#include <stddef.h>
#include <unistd.h>

#include <kernel/task.h>
#include <kernel/task/idx.h>
/*#include <kernel/task/io_sync.h>*/

#include <fs/index_descriptor.h>

#include <fs/idesc.h>

ssize_t write(int fd, const void *buf, size_t nbyte) {
	const struct idesc_ops *ops;
	struct idesc *idesc;
	int res;

	if(!idesc_index_valid(fd)) {
		return SET_ERRNO(EBADF);
	}

	idesc = index_descriptor_get(fd);
	if(!idesc) {
		return SET_ERRNO(EBADF);
	}

	ops = idesc->idesc_ops;
	assert(ops);
	
	res = ops->write(idesc, buf, nbyte);
	if (res < 0) {
		return SET_ERRNO(-res);
	}

	return res;
}
