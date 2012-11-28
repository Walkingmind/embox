/**
 * @file
 * @brief Tmp file system
 *
 * @date 12.11.12
 * @author Andrey Gazukin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <fs/fs_drv.h>
#include <fs/vfs.h>
#include <fs/tmpfs.h>
#include <fs/mount.h>
#include <util/array.h>
#include <embox/unit.h>
#include <embox/block_dev.h>
#include <mem/misc/pool.h>
#include <mem/phymem.h>
#include <fs/mount.h>
#include <drivers/ramdisk.h>
#include <fs/file_system.h>
#include <fs/file_desc.h>

/* tmpfs filesystem description pool */
POOL_DEF(tmpfs_fs_pool, struct tmpfs_filesystem, OPTION_GET(NUMBER,tmpfs_descriptor_quantity));

/* tmpfs file description pool */
POOL_DEF(tmpfs_file_pool, struct tmpfs_file_info, OPTION_GET(NUMBER,tmpfs_inode_quantity));

INDEX_DEF(tmpfs_file_idx,0,OPTION_GET(NUMBER,tmpfs_inode_quantity));

/* define sizes in 4096 blocks */
#define MAX_FILE_SIZE OPTION_GET(NUMBER,tmpfs_file_size)
#define FILESYSTEM_SIZE OPTION_GET(NUMBER,tmpfs_filesystem_size)

#define TMPFS_NAME "tmpfs"
#define TMPFS_DEV  "/dev/ram0"
#define TMPFS_DIR  "/tmp"
static ramdisk_create_params_t new_ramdisk;
static mount_params_t mount_param;

static char sector_buff[PAGE_SIZE()];/* TODO */

static int tmpfs_format(void *path);
static int tmpfs_mount(void *par);

static int tmpfs_init(void * par) {
	ramdisk_create_params_t *new_ramdisk;

	if(NULL == par) {
		/* don't need init fs driver*/
		//mkfs_params = &tmpfs_mkfs_params;
		return 0;
	}
	else {
		new_ramdisk = (ramdisk_create_params_t *) par;
	}

	new_ramdisk->size = FILESYSTEM_SIZE * PAGE_SIZE();
	new_ramdisk->fs_type = 0;
	new_ramdisk->fs_name = TMPFS_NAME;
	new_ramdisk->path = TMPFS_DEV;

	if (0 != ramdisk_create((void *)new_ramdisk)) {
		return -1;
	}

	mount_param.dev = TMPFS_DEV;
	mount_param.dir = TMPFS_DIR;

	if(NULL == (mount_param.dev_node =
			vfs_find_node(mount_param.dev, NULL))) {
		return -1;
	}

	/* format filesystem */
	if(0 != tmpfs_format((void *)TMPFS_DEV)) {
		return -1;
	}

	/* mount filesystem */
	if(tmpfs_mount((void *) &mount_param)) {
		return -1;
	}
	return 0;
}

static int tmp_ramdisk_fs_init(void) {

	return tmpfs_init(&new_ramdisk);
}
EMBOX_UNIT_INIT(tmp_ramdisk_fs_init); /*TODO*/



static int    tmpfs_open(struct node *node, struct file_desc *file_desc, int flags);
static int    tmpfs_close(struct file_desc *desc);
static size_t tmpfs_read(struct file_desc *desc, void *buf, size_t size, size_t count);
static size_t tmpfs_write(struct file_desc *desc, void *buf, size_t size, size_t count);
static int    tmpfs_ioctl(struct file_desc *desc, int request, va_list args);

static struct kfile_operations tmpfs_fop = {
		tmpfs_open,
		tmpfs_close,
		tmpfs_read,
		tmpfs_write,
		tmpfs_ioctl
};

/*
 * file_operation
 */


static int tmpfs_open(struct node *node, struct file_desc *desc, int flags) {
	struct nas *nas;
	//char path [MAX_LENGTH_PATH_NAME];
	tmpfs_file_info_t *fi;

	nas = node->nas;
	fi = (tmpfs_file_info_t *)nas->fi;

	fi->pointer = 0;
	fi->mode = flags;
	if (O_WRONLY == fi->mode) {
		fi->filelen = 0;
	}
	else if(O_APPEND == fi->mode) {
		fi->pointer = fi->filelen;
	}

	return 0;
}

static int tmpfs_close(struct file_desc *desc) {
	return 0;
}

static int tmpfs_read_sector(void *finfo, char *buffer,
		uint32_t count, uint32_t sector) {
	tmpfs_file_info_t *fi;

	fi = (tmpfs_file_info_t *) finfo;

	if(0 > block_dev_read(fi->fs->bdev, (char *) buffer,
			count * fi->fs->block_size, sector)) {
		return -1;
	}
	else {
		return count;
	}
}

static int tmpfs_write_sector(void *finfo, char *buffer,
		uint32_t count, uint32_t sector) {
	tmpfs_file_info_t *fi;

	fi = (tmpfs_file_info_t *) finfo;

	if(0 > block_dev_write(fi->fs->bdev, (char *) buffer,
			count * fi->fs->block_size, sector)) {
		return -1;
	}
	else {
		return count;
	}
}

static size_t tmpfs_read(struct file_desc *desc, void *buf, size_t size, size_t count) {
	tmpfs_file_info_t *fi;
	size_t len;
	size_t current, cnt;
	uint32_t end_pointer;
	blkno_t blk;
	uint32_t bytecount;
	uint32_t start_block;		/* start of file */
	struct nas *nas;

	nas = desc->node->nas;
	fi = (tmpfs_file_info_t *)nas->fi;

	len = size * count;

	/* Don't try to read past EOF */
	if (len > fi->filelen - fi->pointer) {
		len = fi->filelen - fi->pointer;
	}

	end_pointer = fi->pointer + len;
	bytecount = 0;
	start_block = fi->index * fi->fs->block_per_file;

	while(len) {
		blk = fi->pointer / fi->fs->block_size;
		/* check if block over the file */
		if(blk >= fi->fs->block_per_file) {
			bytecount = 0;
			break;
		}
		else {
			blk += start_block;
		}
		/* check if block over the filesystem */
		if(blk >= fi->fs->numblocks) {
			bytecount = 0;
			break;
		}
		/* calculate pointer in scratch buffer */
		current = fi->pointer % fi->fs->block_size;

		/* set the counter how many bytes read from block */
		if(end_pointer - fi->pointer > fi->fs->block_size) {
			if(current) {
				cnt = fi->fs->block_size - current;
			}
			else {
				cnt = fi->fs->block_size;
			}
		}
		else {
			cnt = end_pointer - fi->pointer;
		}

		/* one 4096-bytes block read operation */
		if(1 != tmpfs_read_sector(fi, sector_buff, 1, blk)) {
			bytecount = 0;
			break;
		}
		/* get data from block */
		memcpy (buf, sector_buff + current, cnt);

		bytecount += cnt;
		/* shift the pointer */
		fi->pointer += cnt;
		if(end_pointer >= fi->pointer) {
			break;
		}
	}
	return bytecount;
}


static size_t tmpfs_write(struct file_desc *desc, void *buf, size_t size, size_t count) {
	tmpfs_file_info_t *fi;
	size_t len;
	size_t current, cnt;
	uint32_t end_pointer;
	blkno_t blk;
	uint32_t bytecount;
	uint32_t start_block;
	struct nas *nas;

	nas = desc->node->nas;
	fi = (tmpfs_file_info_t *)nas->fi;
	bytecount = 0;

	/* Don't allow writes to a file that's open as readonly */
	if (!(fi->mode & O_WRONLY) && !(fi->mode & O_APPEND)) {
		return 0;
	}

	len = size * count;
	end_pointer = fi->pointer + len;
	start_block = fi->index * fi->fs->block_per_file;

	while(1) {
		blk = fi->pointer / fi->fs->block_size;
		/* check if block over the file */
		if(blk >= fi->fs->block_per_file) {
			bytecount = 0;
			break;
		}
		else {
			blk += start_block;
		}
		/* calculate pointer in scratch buffer */
		current = fi->pointer % fi->fs->block_size;

		/* set the counter how many bytes written in block */
		if(end_pointer - fi->pointer > fi->fs->block_size) {
			if(current) {
				cnt = fi->fs->block_size - current;
			}
			else {
				cnt = fi->fs->block_size;
			}
		}
		else {
			cnt = end_pointer - fi->pointer;
		}

		/* one 4096-bytes block read operation */
		if(1 != tmpfs_read_sector(fi, sector_buff, 1, blk)) {
			bytecount = 0;
			break;
		}
		/* set new data in block */
		memcpy (sector_buff + current, buf, cnt);

		/* write one block to device */
		if(1 != tmpfs_write_sector(fi, sector_buff, 1, blk)) {
			bytecount = 0;
			break;
		}
		bytecount += cnt;
		/* shift the pointer */
		fi->pointer += cnt;
		if(end_pointer >= fi->pointer) {
			break;
		}
	}
	/* if we write over the last EOF, set new filelen */
	if (fi->filelen < fi->pointer) {
		fi->filelen = fi->pointer;
	}

	return bytecount;
}

static int tmpfs_ioctl(struct file_desc *desc, int request, va_list args) {
	return 0;
}

/*
static int tmpfs_seek(void *file, long offset, int whence);
static int tmpfs_stat(void *file, void *buff);

static int tmpfs_fseek(void *file, long offset, int whence) {
	struct file_desc *desc;
	tmpfs_file_info_t *fi;
	uint32_t curr_offset;

	curr_offset = offset;

	desc = (struct file_desc *) file;
	fi = (tmpfs_file_info_t *)desc->node->fi;

	switch (whence) {
	case SEEK_SET:
		break;
	case SEEK_CUR:
		curr_offset += fi->pointer;
		break;
	case SEEK_END:
		curr_offset = fi->filelen + offset;
		break;
	default:
		return -1;
	}

	if (curr_offset > fi->filelen) {
		curr_offset = fi->filelen;
	}
	fi->pointer = curr_offset;
	return 0;
}
static int tmpfs_stat(void *file, void *buff) {
	struct file_desc *desc;
	tmpfs_file_info_t *fi;
	stat_t *buffer;

	desc = (struct file_desc *) file;
	fi = (tmpfs_file_info_t *)desc->node->fi;
	buffer = (stat_t *) buff;

	if (buffer) {
			memset(buffer, 0, sizeof(stat_t));

			buffer->st_mode = fi->mode;
			buffer->st_ino = fi->index;
			buffer->st_nlink = 1;
			buffer->st_dev = *(int *) fi->fs->bdev;
			buffer->st_atime = buffer->st_mtime = buffer->st_ctime = 0;
			buffer->st_size = fi->filelen;
			buffer->st_blksize = fi->fs->block_size;
			buffer->st_blocks = fi->fs->numblocks;
		}

	return fi->filelen;
}
*/


static int tmpfs_init(void * par);
static int tmpfs_format(void *path);
static int tmpfs_mount(void *par);
static int tmpfs_create(void *params);
static int tmpfs_delete(const char *fname);

static fsop_desc_t tmpfs_fsop = {
		tmpfs_init,
		tmpfs_format,
		tmpfs_mount,
		tmpfs_create,
		tmpfs_delete
};

static fs_drv_t tmpfs_drv = {
	.name = TMPFS_NAME,
	.file_op = &tmpfs_fop,
	.fsop = &tmpfs_fsop
};

static tmpfs_file_info_t *tmpfs_create_file(void *fs) {
	tmpfs_file_info_t *fi;

	if(NULL == (fi = pool_alloc(&tmpfs_file_pool))) {
		return NULL;
	}

	fi->fs = fs;
	fi->index = index_alloc(&tmpfs_file_idx, INDEX_ALLOC_MIN);
	fi->filelen = fi->pointer = 0;

	return fi;
}

static int tmpfs_create(void *params) {
	file_create_param_t *param;
	tmpfs_file_info_t *fi, *parent_fi;
	node_t *node, *parents_node;
	struct nas *nas, *parents_nas;
	int node_quantity;

	param = (file_create_param_t *) params;

	node = (node_t *)param->node;
	parents_node = (node_t *)param->parents_node;
	parents_nas = parents_node->nas;
	parent_fi = (tmpfs_file_info_t *) parents_nas->fi;

	if (NODE_TYPE_DIRECTORY == (node->properties & NODE_TYPE_DIRECTORY)) {
		node_quantity = 3; /* need create . and .. directory */
	}
	else {
		node_quantity = 1;
	}

	for (int count = 0; count < node_quantity; count ++) {
		if(0 < count) {
			if(1 == count) {
				strcat(param->path, "/.");
			}
			else if(2 == count) {
				strcat(param->path, ".");
			}
			if(NULL == (node = vfs_add_path (param->path, NULL))) {
				return -ENOMEM;
			}
		}

		//node->fs_type = &tmpfs_drv;
		//node->node_info = parents_node->node_info;
		nas = node->nas;
		nas->fs = parents_nas->fs;
		/* don't need create fi for directory - take root node fi */
		nas->fi = parents_nas->fi;

		if((0 >= count) & (NODE_TYPE_DIRECTORY !=
				(node->properties & NODE_TYPE_DIRECTORY))) {
			if(NULL == (fi = tmpfs_create_file(parent_fi->fs))) {
				return -ENOMEM;
			}
			nas->fi = (void *) fi;
		}
	}
	/* cut /.. from end of PATH, if need */
	if (1 < node_quantity) {
		param->path[strlen(param->path) - 3] = '\0';
	}

	return 0;
}

static int tmpfs_delete(const char *fname) {
	tmpfs_file_info_t *fi;
	node_t *node, *pointnod;
	struct nas *nas;
	char path [MAX_LENGTH_PATH_NAME];

	if(NULL == (node = vfs_find_node(fname, NULL))) {
		return -1;
	}
	nas = node->nas;
	fi = (tmpfs_file_info_t *)nas->fi;

	vfs_get_path_by_node(node, path);

	/* need delete "." and ".." node for directory */
	if (node_is_directory(node)) {

		strcat(path, "/.");
		pointnod = vfs_find_node(path, NULL);
		vfs_del_leaf(pointnod);

		strcat(path, ".");
		pointnod = vfs_find_node(path, NULL);
		vfs_del_leaf(pointnod);

		path[strlen(path) - 3] = '\0';
	}

	if (node_is_directory(node)) {
		index_free(&tmpfs_file_idx, fi->index);
		pool_free(&tmpfs_file_pool, fi);
	}

	/* root node - have fi, but haven't index*/
	if(0 == strcmp((const char *) path, (const char *) fi->fs->root_name)){

		pool_free(&tmpfs_fs_pool, fi->fs);
		pool_free(&tmpfs_file_pool, fi);
	}

	vfs_del_leaf(node);

	return 0;
}

static int tmpfs_format(void *path) {
	node_t *node;
	struct nas *nas;
	tmpfs_filesystem_t *fsi;
	tmpfs_file_info_t *fi;

	if (NULL == (node = vfs_find_node((char *) path, NULL))) {
		return -ENODEV;/*device not found*/
	}

	if(!node_is_block_dev(node)) {
		return -ENODEV;
	}
	nas = node->nas;

	if((NULL == (fsi = pool_alloc(&tmpfs_fs_pool))) ||
			(NULL == (fi = pool_alloc(&tmpfs_file_pool)))) {
		/* nary memory to enemy */
		if(NULL != fsi){
			pool_free(&tmpfs_fs_pool, fsi);
		}
		return -ENOMEM;
	}

	fsi->bdev = nas->fs->bdev;
	strcpy((char *) fsi->root_name, "\0");
	fsi->block_per_file = MAX_FILE_SIZE;
	fsi->block_size = PAGE_SIZE();


	fsi->numblocks = block_dev(nas->fs->bdev)->size / PAGE_SIZE();

	nas->fs->fsi = fi->fs = fsi;
	//nod->fs_type = &tmpfs_drv;
	nas->fs->drv = &tmpfs_drv;
	//nod->node_info = (void *) &tmpfs_fop;
	nas->fi = (void *)fi;

	return 0;
}

static int tmpfs_mount(void *par) {
	mount_params_t *params;
	node_t *dir_node, *dev_node;
	struct nas *dir_nas, *dev_nas;
	tmpfs_file_info_t *fi, *dev_fi;

	params = (mount_params_t *) par;
	dev_node = params->dev_node;
	if (NULL == (dir_node = vfs_find_node(params->dir, NULL))) {
		/*FIXME: usually mount doesn't create a directory*/
		if (NULL == (dir_node = vfs_add_path (params->dir, NULL))) {
			return -ENODEV;/*device not found*/
		}
		dir_node->properties = NODE_TYPE_DIRECTORY;
	}

	dir_nas = dir_node->nas;
	dev_nas = dev_node->nas;

	/* If dev_node created, but not attached to the filesystem driver */
	if (NULL == (dev_fi = (tmpfs_file_info_t *) dev_nas->fi)) {
		if((NULL == (dev_fi = pool_alloc(&tmpfs_file_pool))) ||
				(NULL == (dev_fi->fs = pool_alloc(&tmpfs_fs_pool)))) {
			if(NULL != dev_fi){
				pool_free(&tmpfs_file_pool, dev_fi);
			}
			return -ENOMEM;
		}
		dev_nas->fi = dev_fi;
		dev_nas->fs->fsi = dev_fi->fs;
		dev_fi->fs->bdev = dev_nas->fs->bdev;
	}

	strncpy((char *) dev_fi->fs->root_name, params->dir, MAX_LENGTH_PATH_NAME);

	if(NULL == (fi = pool_alloc(&tmpfs_file_pool))) {
		return -ENOMEM;
	}

	fi->fs = dev_fi->fs;
	//dir_node->fs_type = &tmpfs_drv;
	dir_nas->fs = dev_nas->fs;
	dir_nas->fi = (void *) fi;

	return 0;
}

DECLARE_FILE_SYSTEM_DRIVER(tmpfs_drv);

