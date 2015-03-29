/**
 * @file
 *
 * @author  Denis Deryugin
 * @date    29 Mar 2015
 */

#include <fs/dvfs.h>
#include <kernel/task.h>
#include <kernel/task/resource/file_table.h>

ssize_t write(int fd, const void *buf, size_t nbyte) {
	struct file *file;
	struct file_table *ft;

	ft = task_resource_file_table(task_self());
	if (fd < FILE_TABLE_SZ && ft->file[fd] != NULL) {
		file = ft->file[fd];
		return dvfs_write(file, (char *) buf, nbyte);
	} else {
		return -1;
	}
}

