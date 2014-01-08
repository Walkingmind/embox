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

#include <module/embox/fs/driver/initfs.h>

/* file description pool */
POOL_DEF (fdesc_pool, struct _ramfs_file_info,
			OPTION_GET(NUMBER,fdesc_quantity));

/* File operations */

static void *ramfs_fopen(struct file_desc *desc, int flag);
static int ramfs_fclose(struct file_desc *desc);
static size_t ramfs_fread(void *buf, size_t size, size_t count, void *file);
static size_t ramfs_fwrite(const void *buf, size_t size, size_t count,
		void *file);
static int ramfs_fseek(void *file, long offset, int whence);
static int ramfs_ioctl(void *file, int request, va_list args);

static file_operations_t ramfs_fop = { ramfs_fopen, ramfs_fclose, ramfs_fread,
		ramfs_fwrite, ramfs_fseek, ramfs_ioctl, NULL };

static void *ramfs_fopen(struct file_desc *desc, int flag) {
	node_t *nod;
	ramfs_file_info_t *fi;


	nod = desc->node;
	fi = (ramfs_file_info_t*) nod->fi;
	fi->cur_pointer = 0;
	fi->lock = 1;
	return desc;
}

static int ramfs_fclose(struct file_desc *desc) {
//	ramfs_file_info_t *fi;

//	node_t *nod = (node_t *) file;
//	fi = (ramfs_file_info_t*) nod->fi;
//	fi->lock = 0;
	return 0;
}

static size_t ramfs_fread(void *buf, size_t size, size_t count, void *file) {
	ramfs_file_info_t *fi;
	struct file_desc *desc;
	size_t size_to_read;

	size_to_read = size * count;
	desc = (struct file_desc *) file;
	fi = (ramfs_file_info_t*) desc->node->fi;

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

static size_t ramfs_fwrite(const void *buf, size_t size, size_t count,
		void *file) {
	ramfs_file_info_t *fi;
	node_t *nod;
	size_t size_to_write = size * count;
	nod = (node_t *) file;
	fi = (ramfs_file_info_t*) nod->fi;

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
		return -1; /*Non-valid offset*/
	}

	fi->cur_pointer = new_offset;
	return 0;
}

static int ramfs_ioctl(void *file, int request, va_list ar) {
	ramfs_file_info_t *fi;
	node_t *nod;
	uint32_t *addr;
	va_list args;
	//TODO: switch through "request" ID.
	va_copy(args, ar);
	addr = (uint32_t *) va_arg(args, unsigned long);
	va_end(args);
	nod = (node_t *) file;
	fi = (ramfs_file_info_t*) nod->fi;
	*addr = fi->start_addr;
	return 0;
}

/* File system operations */

static int ramfs_init(void * par);
static int ramfs_format(void * par);
static int ramfs_mount(void * par);
static int ramfs_create(void *params);
static int ramfs_delete(const char *fname);


static fsop_desc_t ramfs_fsop = { ramfs_init, ramfs_format, ramfs_mount,
		ramfs_create, ramfs_delete };

static fs_drv_t ramfs_drv = { "ramfs", &ramfs_fop, &ramfs_fsop };

DECLARE_FILE_SYSTEM_DRIVER(ramfs_drv);

static int ramfs_format(void *par) {
	return 0;
}
static int ramfs_create(void *params) {
	ramfs_create_param_t *par;
	node_t *nod;
	ramfs_file_info_t *fi;

	par = (ramfs_create_param_t *) params;
	if (NULL == (nod = vfs_add_path(par->name, NULL))) {
		return 0;/*file already exist*/
	}

	fi = pool_alloc(&fdesc_pool);
	nod->fs_type = &ramfs_drv;
	nod->node_info = (void *) &ramfs_fop;
	nod->fi = (void *) fi;

	fi->start_addr = par->start_addr;
	fi->size = par->size;
	fi->mode = par->mode;
	fi->mtime = par->mtime;

	return 0;
}

static int ramfs_delete(const char *fname) {
	ramfs_file_info_t *fi;
	node_t *nod = vfs_find_node(fname, NULL);
	fi = nod->fi;

	pool_free(&fdesc_pool, fi);
	vfs_del_leaf(nod);
	return 0;
}

static int ramfs_init(void * par) {
	return 0;
}

static int ramfs_mount(void * par) {
	struct mount_params *mp;

	assert(par);
	mp = par;

	cpio_unpack(mp->dir);
	return 0;
}