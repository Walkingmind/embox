/**
 * @file
 * @details realize file operation function in line address space
 *
 * @date 29.06.09
 * @author Anton Bondarev
 *	- initial implementation
 * @author Nikolay Korotky
 *	- rework using vfs
 */

#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <fs/ramfs.h>
#include <fs/fs_drv.h>
#include <fs/vfs.h>
#include <fs/mount.h>
#include <fs/file_desc.h>

#include <mem/misc/pool.h>
#include <util/array.h>
#include <embox/unit.h>


/* file description pool */
POOL_DEF (fdesc_pool, struct _ramfs_file_info,
			OPTION_GET(NUMBER,fdesc_quantity));

/* File operations */

static int    ramfs_open(struct node *node, struct file_desc *desk, int flags);
static int    ramfs_close(struct file_desc *desc);
static size_t ramfs_read(struct file_desc *desc, void *buf, size_t size, size_t count);
static size_t ramfs_write(struct file_desc *desc, void *buf, size_t size, size_t count);
static int    ramfs_ioctl(struct file_desc *desc, int request, va_list args);

static struct kfile_operations ramfs_fop = { ramfs_open, ramfs_close, ramfs_read,
		ramfs_write,  ramfs_ioctl };

static int ramfs_open(struct node *nod, struct file_desc *desc, int flags) {
	node_t *node;
	ramfs_file_info_t *fi;
	struct nas *nas;

	node = nod;
	nas = node->nas;
	fi = (ramfs_file_info_t*) nas->fi;
	fi->cur_pointer = 0;
	fi->lock = 1;
	return 0;
}

static int ramfs_close(struct file_desc *desc) {
	return 0;
}

static size_t ramfs_read(struct file_desc *desc, void *buf, size_t size, size_t count) {
	ramfs_file_info_t *fi;
	size_t size_to_read;
	struct nas *nas;

	size_to_read = size * count;
	nas = desc->node->nas;
	fi = (ramfs_file_info_t*) nas->fi;

	if (fi == NULL) {
		return -ENOENT;
	}

	if (size * count >= (fi->size - fi->cur_pointer)) {
		size_to_read = fi->size - fi->cur_pointer;
	}

	memcpy((void*) buf, (const void *) (fi->start_addr + fi->cur_pointer),
			size_to_read);
	fi->cur_pointer += size_to_read;
	return size_to_read / size; /* number of item not characters */
}

static size_t ramfs_write(struct file_desc *desc, void *buf, size_t size, size_t count) {
	ramfs_file_info_t *fi;
	struct nas *nas;
	size_t size_to_write = size * count;
	nas = desc->node->nas;
	fi = (ramfs_file_info_t*) nas->fi;

	if (fi == NULL) {
		return -ENOENT;
	}

	//FIXME: don't expand memory, need file ramfs_resize.
	if (size * count >= (fi->size - fi->cur_pointer)) {
		fi->size += size * count;
	}

	memcpy((void *) (fi->start_addr + fi->cur_pointer), buf, size_to_write);
	fi->cur_pointer += size_to_write;
	return size_to_write;
}

/*
static int ramfs_fseek(void *file, long offset, int whence);
static int ramfs_fseek(void *file, long offset, int whence) {
	struct file_desc *desc;
	ramfs_file_info_t *fi;
	int new_offset;

	desc = (struct file_desc *) file;
	fi = (ramfs_file_info_t *)desc->node->fi;

	if (fi == NULL) {
		return -ENOENT;
	}

	switch (whence) {
	case SEEK_SET:
		new_offset = offset;
		break;
	case SEEK_CUR:
		new_offset = offset + fi->cur_pointer;
		break;
	case SEEK_END:
		new_offset = fi->size + offset;
		break;
	default:
		return -1;
		//new_offset = offset + whence;
	}

	if (new_offset >= fi->size) {
		return -1; //Non-valid offset
	}

	fi->cur_pointer = new_offset;
	return 0;
}
*/

static int ramfs_ioctl(struct file_desc *desc, int request, va_list arg) {
	ramfs_file_info_t *fi;
	uint32_t *addr;
	va_list args;
	struct nas *nas;
	//TODO: switch through "request" ID.
	va_copy(args, arg);
	addr = (uint32_t *) va_arg(args, unsigned long);
	va_end(args);
	nas = desc->node->nas;
	fi = (ramfs_file_info_t*) nas->fi;
	*addr = fi->start_addr;
	return 0;
}

/* File system operations */

static int ramfs_mount(void * par);
static int ramfs_create(struct node *parent_node, struct node *new_nodes);

static fsop_desc_t ramfs_fsop = { NULL, NULL, ramfs_mount,
		ramfs_create, NULL };

static fs_drv_t ramfs_drv = { "ramfs", &ramfs_fop, &ramfs_fsop };

DECLARE_FILE_SYSTEM_DRIVER(ramfs_drv);

static int ramfs_create(struct node *parent_node, struct node *new_node) {
	ramfs_create_param_t *par;
	struct nas *nas, *root_nas;
	ramfs_file_info_t *fi;


	nas = new_node->nas;
	par = (ramfs_create_param_t *) nas->fi;

	fi = pool_alloc(&fdesc_pool);


	root_nas = par->root_node->nas;
	nas->fs = root_nas->fs;
	nas->fi = (void *) fi;

	fi->start_addr = par->start_addr;
	fi->size = par->size;
	fi->mode = par->mode;
	fi->mtime = par->mtime;

	return 0;
}


static int ramfs_mount(void * par) {
	struct mount_params *mp;

	assert(par);
	mp = par;

	cpio_unpack(mp->dir);
	return 0;
}
