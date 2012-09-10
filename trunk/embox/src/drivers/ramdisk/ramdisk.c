/**
 * @file
 * @brief
 *
 * @date 27.03.2012
 * @author Andrey Gazukin
 */

#include <errno.h>
#include <string.h>
#include <cmd/mkfs.h>
#include <embox/unit.h>
#include <fs/vfs.h>
#include <drivers/ramdisk.h>
#include <mem/page.h>
#include <mem/misc/pool.h>
#include <embox/block_dev.h>

/*
static int ioctl(void *dev);
static int flush(void *dev);
static size_t read_sectors(void *dev, char *buffer,
		uint32_t sector, uint32_t count);
static size_t write_sectors(void *dev, char *buffer,
		uint32_t sector, uint32_t count);

static block_dev_operations_t block_dev_op = {
		.blk_read = read_sectors,
		.blk_write = write_sectors,
		.ioctl = ioctl,
		.flush = flush
};
*/
static int read_sectors(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno);
static int write_sectors(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno);
static int ioctl(block_dev_t *dev, int cmd, void *args, size_t size);

block_dev_driver_t ramdisk_pio_driver = {
  "ramdisk_drv",
  DEV_TYPE_BLOCK,
  ioctl,
  read_sectors,
  write_sectors
};

typedef struct dev_ramdisk_head {
	dev_ramdisk_t param;
} dev_ramdisk_head_t;

POOL_DEF(ramdisk_pool, struct dev_ramdisk_head, OPTION_GET(NUMBER,ramdisk_quantity));

EMBOX_UNIT_INIT(unit_init);

int ramdisk_create(void *mkfs_params) {
	node_t *ramdisk_node;
	mkfs_params_t *p_mkfs_params;
	dev_ramdisk_t *ram_disk;
	//block_dev_module_t *block_dev;
	//dev_t devnum;

	p_mkfs_params = (mkfs_params_t *)mkfs_params;

	if (NULL == (ramdisk_node = vfs_add_path(p_mkfs_params->path, NULL))) {
		return -EBUSY;
	}

	ram_disk = pool_alloc(&ramdisk_pool);
	if(0 > (ram_disk->devnum =
			dev_make("ramdisk", &ramdisk_pio_driver, ram_disk))) {
		dev_destroy (ram_disk->devnum);
		return -EIO;
	}

	ram_disk->dev_node = ramdisk_node;

	/*if(NULL == (block_dev = block_dev_find("ramdisk"))) {
		return -ENODEV;
	}
	ramdisk_node->dev_type = (void *) block_dev->dev_ops;*/
	ramdisk_node->dev_type = (void *)device(ram_disk->devnum)->driver;
	ramdisk_node->dev_attr = (void *)&ram_disk->devnum;
	device(ram_disk->devnum)->dev_node = ramdisk_node;

	if(NULL == (ram_disk->p_start_addr =
			page_alloc(p_mkfs_params->blocks))) {
		return -ENOMEM;
	}

	strcpy ((void *)&ram_disk->path, (const void *)p_mkfs_params->path);
	ram_disk->size = p_mkfs_params->blocks * PAGE_SIZE();
	device(ram_disk->devnum)->size = ram_disk->size;
	ram_disk->blocks = p_mkfs_params->blocks;
	ram_disk->sector_size = 512;

	strcpy ((void *)&ram_disk->fs_name,
			(const void *)p_mkfs_params->fs_name);

	return 0;
}

dev_ramdisk_t *ramdisk_get_param(char *name) {
	node_t *ramdisk_node;
	dev_t devnum;

	if (NULL == (ramdisk_node = vfs_find_node(name, NULL))) {
		return NULL;
	}
	devnum = *((dev_t *)ramdisk_node->dev_attr);
	return (dev_ramdisk_t *) device(devnum)->privdata;
}

int ramdisk_delete(const char *name) {
	node_t *ramdisk_node;
	dev_ramdisk_t *ram_disk;
	dev_t devnum;

	if (NULL == (ramdisk_node = vfs_find_node(name, NULL))) {
		return -1;
	}
	devnum = *((dev_t *)ramdisk_node->dev_attr);
	if(NULL != (ram_disk = (dev_ramdisk_t *) device(devnum)->privdata)) {
		pool_free(&ramdisk_pool, ram_disk);
		vfs_del_leaf(ramdisk_node);
	}
	return dev_destroy (devnum);
}

static int unit_init(void) {
	//init_ramdisk_info_pool();
	return 0;
}

/*static size_t read_sectors(void *dev, char *buffer,
		uint32_t sector, uint32_t count)*/
static int read_sectors(block_dev_t *dev,
		char *buffer, size_t count, blkno_t blkno) {
	dev_ramdisk_t *ram_disk;
	char *read_addr;
	//uint32_t size;

	ram_disk = (dev_ramdisk_t *) dev->privdata;

	//size = ram_disk->sector_size * count;
	read_addr = ram_disk->p_start_addr + (blkno * ram_disk->sector_size);

	memcpy(buffer, read_addr, count);
	return count;
}


/*static size_t write_sectors(void *dev, char *buffer,
		uint32_t sector, uint32_t count) {*/
static int write_sectors(block_dev_t *dev,
		char *buffer, size_t count, blkno_t blkno) {
	dev_ramdisk_t *ram_disk;
	char *write_addr;
	//uint32_t size;

	ram_disk = (dev_ramdisk_t *) dev->privdata;

	//size = ram_disk->sector_size * count;
	write_addr = ram_disk->p_start_addr + (blkno * ram_disk->sector_size);

	memcpy(write_addr, buffer, count);
	return count;
}

/*static int ioctl(void *dev) {*/
static int ioctl(block_dev_t *dev, int cmd, void *args, size_t size) {

	return 0;
}

/*
static int flush(void *dev) {

	return 0;
}
*/

//EMBOX_BLOCK_DEV("ramdisk", &block_dev_op);
