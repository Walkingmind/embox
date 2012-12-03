/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    04.10.2012
 */

#include <fcntl.h>
#include <kernel/task/idx.h>
#include <util/array.h>
#include <fs/posix.h>
#include <fs/kfile.h>

int open(const char *path, int __oflag, ...) {

	struct file_desc *kfile;

	kfile = kopen(path, __oflag);

	if (NULL == kfile) {
		return -1;
	}

	return task_self_idx_alloc(&task_idx_ops_file, kfile);
}
