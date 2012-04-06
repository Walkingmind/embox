/**
 * @file
 * @brief File descriptor (fd) abstraction over FILE *
 * @details Provide POSIX kernel support to operate with flides (int) 
 *	instead of FILE *
 * @date 06.09.11
 * @author Anton Kozlov
 */

#include <kernel/task.h>
#include <util/array.h>

extern const struct task_res_ops * __task_res_ops[];

static int this_open(const char *path, int __oflag, va_list args) {
	return task_res_idx_alloc(task_self_res(), TASK_IDX_TYPE_FILE, fopen(path, "rw"));
}

static int this_close(int fd) {
	FILE *file = task_self_idx_get(fd)->file;
	return fclose(file);
}

static ssize_t this_read(int fd, const void *buf, size_t nbyte) {
	FILE *file = task_self_idx_get(fd)->file;
	return fread((void *) buf, 1, nbyte, file);
}

static ssize_t this_write(int fd, const void *buf, size_t nbyte) {
	FILE *file = task_self_idx_get(fd)->file;
	return fwrite(buf, 1, nbyte, file);
}

static int this_ioctl(int fd, int request, va_list args) { 
	return fioctl(task_self_idx_get(fd)->file, request, args);
}
static struct task_res_ops ops = {
	.type  = TASK_IDX_TYPE_FILE,
	.open  = this_open,
	.close = this_close,
	.read  = this_read,
	.write = this_write,
	.ioctl = this_ioctl,
};

ARRAY_SPREAD_ADD(__task_res_ops, &ops);
