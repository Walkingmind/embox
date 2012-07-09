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
#include <lib/list.h>
#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <fs/file_desc.h>

#include <kernel/prom_printf.h>

FILE *fopen(const char *path, const char *mode) {
	node_t *nod;
	fs_drv_t *drv;
	FILE *file;
	struct file_desc *desc;

	if (NULL == (nod = vfs_find_node(path, NULL))) {
		if ('w' != *mode) {
			errno = -ENOENT;
			return NULL;
		}

		if (-1 == creat(path, 0)) {
			errno = -EINVAL;
			return NULL;
		}

		if (NULL == (nod = vfs_find_node(path, NULL))) {
			return NULL;
		}
	}
	/* check permissions */

	/* allocate new descriptor */
	if (NULL == (desc = file_desc_alloc())) {
		errno = -EINVAL;
		return NULL;
	}

	desc->cursor = 0;
	desc->node = nod;

	drv = nod->fs_type;
	if(NULL != nod->file_info) {
		desc->ops = (struct file_operations *)nod->file_info;
	} else {
		desc->ops = (struct file_operations *) drv->file_op;
	}

	/*if (NULL == drv->file_op->fopen) {
		errno = -EINVAL;
		LOG_ERROR("fop->fopen is NULL handler\n");
		return NULL;
	}
	file = drv->file_op->fopen(desc, mode);*/

	if (NULL == desc->ops->fopen) {
			errno = -EBADF;
			LOG_ERROR("fop->fopen is NULL handler\n");
			return NULL;
		}
	file = desc->ops->fopen(desc, mode);

	return file;
}

FILE *freopen(const char *path, const char *mode, FILE *file) {
	//TODO:
	return NULL;
}

int feof(FILE *file) {
	//TODO:
	return 0;
}

int ferror(FILE *file) {
	//TODO:
	return 0;
}

size_t fwrite(const void *buf, size_t size, size_t count, FILE *file) {
	struct file_desc *desc;

	if(NULL == file) {
		return -EBADF;
	}

	desc = (struct file_desc *)file;

	if (NULL == desc->ops->fwrite) {
		errno = -EBADF;
		LOG_ERROR("fop->fwrite is NULL handler\n");
		return errno;
	}

	return desc->ops->fwrite(buf, size, count, file);
}

size_t fread(void *buf, size_t size, size_t count, FILE *file) {
	struct file_desc *desc;
	char *cbuff;
	uint addon = 0;

	if(NULL == file) {
		return -EBADF;
	}

	desc = (struct file_desc *)file;
	if(desc->has_ungetc) {
		desc->has_ungetc = 0;
		cbuff = buf;
		cbuff[0] = (char)desc->ungetc;
		count --;
		buf = &cbuff[1];
		addon = 1;
	}

	if (NULL == desc->ops->fread) {
		errno = -EBADF;
		LOG_ERROR("fop->fread is NULL handler\n");
		return errno;
	}

	return (addon + desc->ops->fread(buf, size, count, file));
}


int fclose(FILE *file) {
	struct file_desc *desc;

	if(NULL == file) {
		return -EBADF;
	}

	desc = (struct file_desc *)file;

	if (NULL == desc->ops->fclose) {
		errno = -EBADF;
		LOG_ERROR("fop->fclose is NULL handler\n");
		return errno;
	}

	desc->ops->fclose(desc);
	file_desc_free(desc);

	return 0;
}

int fseek(FILE *file, long int offset, int origin) {
	struct file_desc *desc;

	if(NULL == file) {
		return -EBADF;
	}

	desc = (struct file_desc *)file;

	if (NULL == desc->ops->fseek) {
		errno = -EBADF;
		LOG_ERROR("fop->fseec is NULL handler\n");
		return errno;
	}

	return desc->ops->fseek(file, offset, origin);
}

int fioctl(FILE *fp, int request, ...) {
	struct file_desc *desc = (struct file_desc *) fp;
	va_list args;
	va_start(args, request);

	if (NULL == fp) {
		return -EBADF;
	}

	if (NULL == desc->ops->ioctl) {
		errno = -EBADF;
		LOG_ERROR("fop->ioctl is NULL handler\n");
		return errno;
	}
	return desc->ops->ioctl(fp, request, args);
}

int ungetc(int ch, FILE *file) {
	struct file_desc *desc = (struct file_desc *) file;
	desc->ungetc = (char) ch;
	desc->has_ungetc = 1;
	return ch;
}
