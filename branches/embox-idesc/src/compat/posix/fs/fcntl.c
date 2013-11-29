/**
 * @file
 *
 * @date Nov 21, 2013
 * @author: Anton Bondarev
 */
#include <errno.h>
#include <fcntl.h>

#include <kernel/task.h>


#include <fs/index_descriptor.h>


int fcntl(int fd, int cmd, ...) {
	void * data;
	va_list args;
	int dint;
	int res;

	if (!idesc_index_valid(fd)) {
		return SET_ERRNO(EBADF);
	}

	/* Fcntl works in two steps:
	 * 1. Make general commands like F_SETFD, F_GETFD.
	 * 2. If fd has some internal fcntl(), it will be called.
	 *    Otherwise result of point 1 will be returned. */
	switch (cmd) {
	case F_DUPFD:
		va_start(args, cmd);
		dint = va_arg(args, int);
		va_end(args);

		res = index_descriptor_dupfd(fd, dint);

		if (res < 0) {
			return SET_ERRNO(-res);
		}
		return res;

	case F_GETFL:
		return index_descriptor_flags_get(fd);

	case F_SETFL:
		va_start(args, cmd);
		dint = va_arg(args, int);
		va_end(args);

		return index_descriptor_flags_set(fd, dint);

	case F_GETFD: /* only for CLOEXEC flag */
		return index_descritor_cloexec_get(fd);

	case F_SETFD: /* only for CLOEXEC flag */
		va_start(args, cmd);
		dint = va_arg(args, int);
		va_end(args);
		return index_descriptor_cloexec_set(fd, dint);
/*	case F_GETPIPE_SZ:
	case F_SETPIPE_SZ:
		break;
*/

	default:
		va_start(args, cmd);
		data = va_arg(args, void*);
		va_end(args);
		res = index_descriptor_fcntl(fd, cmd, data);
		if (res < 0) {
			return SET_ERRNO(-res);
		}
	}

	return 0;
}

