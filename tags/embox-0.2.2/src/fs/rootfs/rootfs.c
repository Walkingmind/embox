/**
 * @file
 * @details realize file operation function in line address space
 *
 * @date 29.06.09
 * @author Anton Bondarev
 */

#include <string.h>
#include <assert.h>
#include <fs/ramfs.h>
#include <fs/fs.h>
#include <linux/init.h>
#include <fs/node.h>
#include <util/array.h>

static void   *rootfs_open(struct file_desc *desc);
static int     rootfs_close(struct file_desc *desc);
static size_t  rootfs_read(void *buf, size_t size, size_t count, void *file);
static size_t  rootfs_write(const void *buf, size_t size, size_t count, void *file);
static int     rootfs_seek(void *file, long offset, int whence);
static int rootfs_ioctl(void *file, int request, va_list args);

static file_operations_t rootfs_fop = {
	rootfs_open,
	rootfs_close,
	rootfs_read,
	rootfs_write,
	rootfs_seek,
	rootfs_ioctl,
};

static node_t *root_node;

static int rootfs_init(void * par) {
	root_node = alloc_node("/");

	return 0;
}

node_t *rootfs_get_node(void) {
	assert(NULL != root_node);
	return root_node;
}

static int rootfs_create(void *params) {
	return 0;
}

static int rootfs_delete(const char *file_name) {
	return 0;
}

static int rootfs_mount(void *par) {
	fs_drv_t *fsdrv;
	if (NULL != (fsdrv = filesystem_find_drv("ramfs"))) {
		fsdrv->fsop->mount(NULL);
	}
	if (NULL != (fsdrv = filesystem_find_drv("devfs"))) {
		fsdrv->fsop->mount(NULL);
	}
	return 0;
}

static fsop_desc_t rootfs_fsop = {
	rootfs_init,
	rootfs_create,
	rootfs_delete,
	rootfs_mount
};

static const fs_drv_t rootfs_drv = {
	"rootfs",
	&rootfs_fop,
	&rootfs_fsop
};

DECLARE_FILE_SYSTEM_DRIVER(rootfs_drv);

static void *rootfs_open(struct file_desc *desc) {
	return NULL;
}

static int rootfs_close(struct file_desc *desc) {
	return 0;
}

static size_t rootfs_read(void *buf, size_t size, size_t count, void *file) {
	return 0;
}

static size_t rootfs_write(const void *buf, size_t size, size_t count, void *file) {
	return 0;
}

static int rootfs_seek(void *file, long offset, int whence) {
	return 0;
}

static int rootfs_ioctl(void *file, int request, va_list args) {
	return 0;
}