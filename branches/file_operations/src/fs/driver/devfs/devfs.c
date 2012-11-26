/**
 * @file
 * @brief Device file system
 *
 * @date 14.10.10
 * @author Nikolay Korotky
 */

#include <stdio.h>
#include <drivers/ide.h>

#include <fs/fs_drv.h>
#include <fs/vfs.h>
#include <util/array.h>
#include <embox/device.h>
#include <embox/block_dev.h>

ARRAY_SPREAD_DEF(const device_module_t, __device_registry);
ARRAY_SPREAD_DEF(const block_dev_module_t, __block_dev_registry);

static const fs_drv_t devfs_drv;

static struct kfile_operations devfs_fop;

const fs_drv_t *devfs_get_fs(void) {
    return &devfs_drv;
}

static int devfs_init(void * par) {
	return 0;
}

static int devfs_format(void *par) {
	return 0;
}

static int devfs_mount(void *par) {
	node_t *nod, *devnod;
	size_t i;

	if (NULL == (nod = vfs_find_node("/dev", NULL))) {
		if (NULL == (nod = vfs_add_path("/dev", NULL))) {
			return 0;
		}
	}
	nod->properties = DIRECTORY_NODE_TYPE;

	for (i = 0; i < ARRAY_SPREAD_SIZE(__device_registry); i++) {
		if (NULL != (devnod = vfs_add_path(__device_registry[i].name, nod))) {
			if(NULL != __device_registry[i].init) {
				__device_registry[i].init();
			}
			devnod->node_info = (void*) __device_registry[i].fops;
			devnod->fs_type = (fs_drv_t *) &devfs_drv;
		}
	}

	for (i = 0; i < ARRAY_SPREAD_SIZE(__block_dev_registry); i++) {
		if (NULL != __block_dev_registry[i].init) {
			__block_dev_registry[i].init(NULL);
		}
	}

	return 0;
}

static int devfs_create(void *params) {
	return 0;
}

static int devfs_delete(const char *fname) {
	return 0;
}

/*
 * file_operation
 */
static int devfs_open(struct node *node, struct file_desc *desc, int flags) {
	return desc->ops->open(node, desc, flags);
}

static int devfs_close(struct file_desc *desc) {
	return desc->ops->close(desc);
}

static size_t devfs_read(struct file_desc *desc, void *buf, size_t size, size_t count) {
	return 0;
}

static size_t devfs_write(struct file_desc *desc, void *buf, size_t size, size_t count) {
	return 0;
}

static int devfs_ioctl(struct file_desc *file, int request, va_list args) {
	return 0;
}

static fsop_desc_t devfs_fsop = { devfs_init, devfs_format, devfs_mount,
		devfs_create, devfs_delete};

static kfile_operations_t devfs_fop = {
       .open = devfs_open,
       .close = devfs_close,
       .read = devfs_read,
       .write = devfs_write,
       .ioctl = devfs_ioctl,
};

static const fs_drv_t devfs_drv = {
	.name = "devfs",
	.file_op = &devfs_fop,
	.fsop = &devfs_fsop
};

DECLARE_FILE_SYSTEM_DRIVER(devfs_drv);
