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
#include <err.h>
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

	/* check permissions */

	/* allocate new descriptor */
	if (NULL == (desc = file_desc_alloc())) {
		errno = ENOMEM;
		return NULL;
	}

	desc->node = nod;

	/*TODO set cursor by flag */
	desc->cursor = 0;


	drv = nod->fs->drv;
	assert(drv != NULL);

	/*
	 * if (NULL != nod->node_info) {
	 * 		desc->ops = (struct kfile_operations *)nod->node_info;
	 * } else {
	 * 		desc->ops = (struct kfile_operations *)drv->file_op;
	 * }
	 */
	desc->ops = (struct kfile_operations *)drv->file_op;

	if (NULL == desc->ops->open) {
		//TODO free file_desc
		errno = EBADF;
		LOG_ERROR("fop->fopen is NULL handler\n");
		return NULL;
	}
	if(0 < desc->ops->open(nod, desc, flag)) {
		//TODO free file_desc
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
		LOG_ERROR("fop->fwrite is NULL handler\n");
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
		LOG_ERROR("fop->fread is NULL handler\n");
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
		LOG_ERROR("fop->fclose is NULL handler\n");
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
#if 0
	if (NULL == desc->ops->fseek) {
		errno = EBADF;
		LOG_ERROR("fop->fseec is NULL handler\n");
		return -1;
	}

	return desc->ops->fseek(desc, offset, origin);
#endif
	return -1;
}

int kstat(struct file_desc *desc, void *buff) {
	if (NULL == desc) {
		errno = EBADF;
		return -1;
	}
	//FIXME now we wouldn't have special stat function (it common for every file system)
#if 0
	if (NULL == desc->ops->fstat) {
		errno = EBADF;
		LOG_ERROR("fop->fstat is NULL handler\n");
		return -1;
	}

	return desc->ops->fstat(desc->node->fi, buff); //FIXME Not much pretty -Anton Kozlov
#endif
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
		LOG_ERROR("fop->ioctl is NULL handler\n");
		return -1;
	}
	return desc->ops->ioctl(fp, request, args);
}
