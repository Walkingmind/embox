/**
 * @file
 *
 * @date 06.08.09
 * @author Anton Bondarev
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <fs/fs_drv.h>
#include <fs/file_operation.h>
#include <fs/file_desc.h>
#include <fs/kfile.h>

struct file_desc *kopen(const char *path, int flag) {
	struct node *node;
	struct nas *nas;
	struct file_desc *desc;
	struct kfile_operations *ops;
	int res;


	if (NULL == (node = vfs_find_node(path, NULL))) {
		if ((O_WRONLY != flag) && (O_APPEND != flag)) {
			errno = ENOENT;
			return NULL;
		}

		if (create(path, 0) < 0) {
			return NULL;
		}

		if (NULL == (node = vfs_find_node(path, NULL))) {
			return NULL;
		}
	}

	if (node_is_directory(node)) {
		errno = EISDIR;
		return NULL;
	}

	nas = node->nas;
	/* if we try open a file (not special) we must have the file system */
	if(NULL == nas->fs ) {
		errno = ENOSUPP;
		return NULL;
	}

	if(node_is_file(node)) {
		if(NULL == nas->fs->drv) {
			errno = ENOSUPP;
			return NULL;
		}
		ops = (struct kfile_operations *)nas->fs->drv->file_op;
	} else {
		ops = nas->fs->file_op;
	}

	/* allocate new descriptor */
	if (NULL == (desc = file_desc_alloc())) {
		errno = ENOMEM;
		return NULL;
	}

	desc->node = node;
	desc->ops = ops;

	if((flag & O_APPEND) && node_is_file(node)) {
		desc->cursor = kseek(desc, 0, SEEK_END);
	} else {
		desc->cursor = 0;
	}

	if(0 < (res = desc->ops->open(node, desc, flag))) {
		file_desc_free(desc);
		errno = -res;
		return NULL;
	}
	return desc;
}

size_t kwrite(const void *buf, size_t size, size_t count, struct file_desc *file) {
	struct node *node;

	if (NULL == file) {
		errno = EBADF;
		return -1;
	}

	node = file->node;
	if(node != NULL) {
		if(node->properties & S_IREAD) {
			return -EPERM;
		}
	}


	if (NULL == file->ops->write) {
		errno = EBADF;
		return -1;
	}

	return file->ops->write(file, (void *)buf, size, count);
}

size_t kread(void *buf, size_t size, size_t count, struct file_desc *desc) {

	if (NULL == desc) {
		errno = EBADF;
		return -1;
	}

	if (NULL == desc->ops->read) {
		errno = EBADF;
		return -1;
	}

	return desc->ops->read(desc, buf, size, count);
}


int kclose(struct file_desc *desc) {

	if (NULL == desc) {
		errno = EBADF;
		return -1;
	}

	if (NULL == desc->ops->close) {
		errno = EBADF;
		return -1;
	}

	desc->ops->close(desc);
	file_desc_free(desc);

	return 0;
}

int kseek(struct file_desc *desc, long int offset, int origin) {

	if (NULL == desc) {
		errno = EBADF;
		return -1;
	}
//FIXME now we wouldn't have special fseek function (it common for every file system)
	return -1;
}

int kstat(struct file_desc *desc, void *buff) {
	if (NULL == desc) {
		errno = EBADF;
		return -1;
	}
	//FIXME now we wouldn't have special stat function (it common for every file system)
	return -1;
}

int kioctl(struct file_desc *fp, int request, ...) {
	struct file_desc *desc = (struct file_desc *) fp;
	va_list args;
	va_start(args, request);

	if (NULL == fp) {
		errno = EBADF;
		return -1;
	}

	if (NULL == desc->ops->ioctl) {
		errno = EBADF;
		return -1;
	}
	return desc->ops->ioctl(fp, request, args);
}
