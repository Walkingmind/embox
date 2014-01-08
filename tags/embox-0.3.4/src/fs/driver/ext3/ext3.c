/**
 * @file
 * @brief ext3 file system
 *
 * @date 12.03.2013
 * @author Andrey Gazukin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <fs/fs_driver.h>
#include <fs/vfs.h>
#include <fs/ext2.h>
#include <fs/path.h>
#include <util/array.h>
#include <embox/unit.h>
#include <embox/block_dev.h>
#include <mem/misc/pool.h>
#include <mem/phymem.h>
#include <drivers/ramdisk.h>
#include <fs/file_system.h>
#include <fs/file_desc.h>

#define EXT2_NAME "ext2"
#define EXT3_NAME "ext3"

/* TODO link counter */

static int ext3fs_open(struct node *node, struct file_desc *file_desc,
		int flags);
static int ext3fs_close(struct file_desc *desc);
static size_t ext3fs_read(struct file_desc *desc, void *buf, size_t size);
static size_t ext3fs_write(struct file_desc *desc, void *buf, size_t size);
static int ext3fs_ioctl(struct file_desc *desc, int request, ...);

static struct kfile_operations ext3_fop = {
	.open = ext3fs_open,
	.close = ext3fs_close,
	.read = ext3fs_read,
	.write = ext3fs_write,
	.ioctl = ext3fs_ioctl,
};

/*
 * file_operation
 */
static int ext3fs_open(struct node *node, struct file_desc *desc, int flags) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->file_op->open(node, desc, flags);
}

static int ext3fs_close(struct file_desc *desc) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->file_op->close(desc);
}

static size_t ext3fs_read(struct file_desc *desc, void *buff, size_t size) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->file_op->read(desc, buff, size);
}

static size_t ext3fs_write(struct file_desc *desc, void *buff, size_t size) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->file_op->write(desc, buff, size);
}

static int ext3fs_ioctl(struct file_desc *desc, int request, ...) {
	return 0;
}

static int ext3fs_init(void * par);
static int ext3fs_format(void *path);
static int ext3fs_mount(void *dev, void *dir);
static int ext3fs_create(struct node *parent_node, struct node *node);
static int ext3fs_delete(struct node *node);
static int ext3fs_truncate(struct node *node, off_t length);
static int ext3fs_umount(void *dir);


static struct fsop_desc ext3_fsop = {
	.init	     = ext3fs_init,
	.format	     = ext3fs_format,
	.mount	     = ext3fs_mount,
	.create_node = ext3fs_create,
	.delete_node = ext3fs_delete,

	.getxattr    = ext2fs_getxattr,
	.setxattr    = ext2fs_setxattr,
	.listxattr   = ext2fs_listxattr,

	.truncate    = ext3fs_truncate,
	.umount      = ext3fs_umount,
};

static int ext3fs_init(void * par) {

	return 0;
};

static struct fs_driver ext3fs_driver = {
	.name = EXT3_NAME,
	.file_op = &ext3_fop,
	.fsop = &ext3_fsop,
};

static int ext3fs_create(struct node *parent_node, struct node *node) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->fsop->create_node(parent_node, node);
}

static int ext3fs_delete(struct node *node) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->fsop->delete_node(node);
}

static int ext3fs_format(void *dev) {

	return 0;
}

static int ext3fs_mount(void *dev, void *dir) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->fsop->mount(dev, dir);
}

static int ext3fs_truncate (struct node *node, off_t length) {
	struct nas *nas = node->nas;

	nas->fi->ni.size = length;

	return 0;
}

static int ext3fs_umount(void *dir) {
	struct fs_driver *drv;

	if(NULL == (drv = fs_driver_find_drv(EXT2_NAME))) {
		return -1;
	}

	return drv->fsop->umount(dir);
}

DECLARE_FILE_SYSTEM_DRIVER(ext3fs_driver);