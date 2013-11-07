/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    09.06.2012
 */

#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#include <drivers/diag.h>
#include <drivers/tty.h>
#include <kernel/task.h>
#include <kernel/task/idx.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(iodev_env_init);

static int iodev_read(struct idx_desc *data, void *buf, size_t nbyte) {
	char *cbuf = (char *) buf;

	while (nbyte--) {
		*cbuf++ = diag_getc();
	}

	return (int) cbuf - (int) buf;

}

static int iodev_write(struct idx_desc *data, const void *buf, size_t nbyte) {
	char *cbuf = (char *) buf;

	while (nbyte--) {
		diag_putc(*cbuf++);
	}

	return (int) cbuf - (int) buf;
}

static int iodev_close(struct idx_desc *idx) {
	return 0;
}

static int iodev_ioctl(struct idx_desc *desc, int request, void *data) {
	struct tty *tty = desc->data->fd_struct;

	if(NULL == tty) {
		return -EINVAL;
	}
	if(request == F_SETFD) {
		int flags = (int) data;
		desc->flags = flags;
		tty->file_flags = flags;
	}

	return tty_ioctl(tty, request, data);
}

static int iodev_fstat(struct idx_desc *data, void *buff) {
	struct stat *st = buff;

	st->st_mode = S_IFCHR;

	return 0;
	
}

static const struct task_idx_ops iodev_idx_ops = {
	.read = iodev_read,
	.write = iodev_write,
	.close = iodev_close,
	.ioctl = iodev_ioctl,
	.fstat = iodev_fstat,
};

static int iodev_env_init(void) {
	int fd;

	fd = task_self_idx_alloc(&iodev_idx_ops, NULL, NULL);
	if (fd < 0) {
		return fd;
	}

	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	if (fd > 2) {
		close(fd);
	}

	return 0;
}
