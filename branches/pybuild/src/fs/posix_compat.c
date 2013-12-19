/**
 * @file
 * @brief File descriptor (fd) abstraction over FILE *
 * @details Provide POSIX kernel support to operate with flides (int)
 *	instead of FILE *
 * @date 06.09.11
 * @author Anton Kozlov
 */

#include <kernel/task.h>
#include <kernel/task/idx.h>
#include <assert.h>

#include <fs/kfile.h>

static inline struct file_desc *from_data(struct idx_desc *data) {
	return (struct file_desc *) task_idx_desc_data(data);
}

static int this_close(struct idx_desc *data) {
	return kclose(from_data(data));
}

static ssize_t this_read(struct idx_desc *data, void *buf, size_t nbyte) {
	return kread(buf, 1, nbyte, from_data(data));
}

static ssize_t this_write(struct idx_desc *data, const void *buf, size_t nbyte) {
	assert(data);
	return kwrite(buf, 1, nbyte, from_data(data));
}

static int this_lseek(struct idx_desc *data, long int offset, int origin) {
	return kseek(from_data(data), offset, origin);
}

static int this_stat(struct idx_desc *data, void *buff) {
	return kstat(from_data(data), buff);
}

static int this_ioctl(struct idx_desc *data, int request, va_list args) {
	return kioctl(from_data(data), request, args);
}

const struct task_idx_ops task_idx_ops_file = {
	.close = this_close,
	.read  = this_read,
	.write = this_write,
	.fseek = this_lseek,
	.ioctl = this_ioctl,
	.fstat = this_stat,
};