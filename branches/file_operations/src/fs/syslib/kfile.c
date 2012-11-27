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

#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <fs/file_desc.h>
#include <fs/kfile.h>

struct file_desc *kopen(const char *path, int flag) {
	node_t *nod;
	fs_drv_t *drv;
	struct file_desc *desc;

	if (NULL == (nod = vfs_find_node(path, NULL))) {
		if ((O_WRONLY != flag) && (O_APPEND != flag)) {
			errno = ENOENT;
			return NULL;
		}

		if (create(path, 0) < 0) {
			return NULL;
		}

		if (NULL == (nod = vfs_find_node(path, NULL))) {
			return NULL;
		}
	}

	if (node_is_directory(nod)) {
		errno = EISDIR;
		return NULL;
	}

	drv = nod->fs->drv;
	if(drv == NULL) {
		errno = ENOENT;
		return NULL;
	}


	/* allocate new descriptor */
	if (NULL == (desc = file_desc_alloc())) {
		errno = ENOMEM;
		return NULL;
	}

	desc->node = nod;
	desc->ops = (struct kfile_operations *)drv->file_op;

	if(flag & O_APPEND) {
		desc->cursor = kseek(desc, 0, SEEK_END);
	} else {
		desc->cursor = 0;
	}

	if (NULL == desc->ops->open) {
		file_desc_free(desc);
		errno = EBADF;
		return NULL;
	}
	if(0 < desc->ops->open(nod, desc, flag)) {
		file_desc_free(desc);
		return NULL;
	}
	return desc;
}

size_t kwrite(const void *buf, size_t size, size_t count, struct file_desc *file) {
	if (NULL == file) {
		errno = EBADF;
		return -1;
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
