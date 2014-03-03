/*
 * @file
 *
 * @date 28.11.12
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <embox/device.h>
#include <errno.h>
#include <fs/file_desc.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <fs/file_operation.h>
#include <stdlib.h>
#include <util/array.h>

ARRAY_SPREAD_DEF(const device_module_t, __device_registry);

int char_dev_init_all(void) {
	int ret;
	const device_module_t *dev_module;

	array_spread_foreach_ptr(dev_module, __device_registry) {
		if (dev_module->init != NULL) {
			ret = dev_module->init();
			if (ret != 0) {
				return ret;
			}
		}
	}

	return 0;
}

int char_dev_register(const char *name, const struct kfile_operations *ops) {
	struct node *node;
	struct nas *dev_nas;

	node = vfs_lookup(NULL, "/dev");
	if (node == NULL) {
		return -ENODEV;
	}

	node = vfs_create_child(node, name, S_IFCHR | S_IRALL | S_IWALL);
	if (!node) {
		return -1;
	}

	dev_nas = node->nas;
	dev_nas->fs = filesystem_create("empty");
	if (dev_nas->fs == NULL) {
		return -ENOMEM;
	}

	dev_nas->fs->file_op = ops;

	return 0;
}
