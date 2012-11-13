/**
 * @file
 * @brief
 *
 * @date 31.07.2012
 * @author Andrey Gazukin
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <embox/unit.h>
#include <embox/block_dev.h>
#include <fs/vfs.h>
#include <mem/phymem.h>
#include <mem/misc/pool.h>
#include <util/array.h>
#include <util/indexator.h>

#define MAX_DEV_QUANTITY OPTION_GET(NUMBER,dev_quantity)

POOL_DEF(blockdev_pool, struct block_dev, MAX_DEV_QUANTITY);
POOL_DEF(cache_pool, struct block_dev_cache, MAX_DEV_QUANTITY);
INDEX_DEF(block_dev_idx,0,MAX_DEV_QUANTITY);

static unsigned int num_devs = 0;
static block_dev_t *devtab[64];

/*
static block_dev_module_t *block_dev_find(char *name) {
	block_dev_module_t *b_dev;
	size_t i;

	for(i = 0; i < ARRAY_SPREAD_SIZE(__block_dev_registry); i++) {
		if(!strcmp(__block_dev_registry[i].name, name)) {
			b_dev = (block_dev_module_t *) &(__block_dev_registry[i]);
			return b_dev;
		}
	}

	return NULL;
}
*/

block_dev_t *block_dev(void *dev_id) {
	dev_t devno;

	if (NULL == dev_id) {
		return NULL;
	}
	devno = *((dev_t *) dev_id);
	return devtab[devno];
}

/*
static dev_t block_devno(char *name) {
	dev_t devno;

	for (devno = 0; devno < num_devs; devno++) {
		if (strcmp(block_dev(&devno)->name, name) == 0) {
			return devno;
		}
	}
	return NODEV;
}
*/


static void create_name (char *name, dev_t *idx) {
	char *p;
	unsigned int n, m;
	int exists;
	p = name;

	while (p[0] && p[1]) {
			p++;
		}

	if (*p == '#') {
		if(NULL != idx){
			sprintf(p, "%d", *idx);
			return;
		}
		n = 0;
		while (1) {
			sprintf(p, "%d", n);
			exists = 0;
			for (m = 0; m < num_devs; m++)  {
				if (strcmp(devtab[m]->name, name) == 0) {
					exists = 1;
					break;
				}
			}

			if (!exists) {
				break;
			}
			n++;
		}
	}
	else if(*p == '*') {
		if(NULL != idx){
			sprintf(p, "%c", 'a' + *idx);
			return;
		}
		n = 0;
		while (1) {
			sprintf(p, "%c", 'a' + n);
			exists = 0;
			for (m = 0; m < num_devs; m++)  {
				if (strcmp(devtab[m]->name, name) == 0) {
					exists = 1;
					break;
				}
			}

			if (!exists) {
				break;
			}
			n++;
		}
	}
}

static int block_dev_node_create(dev_t *dev_id, char *dev_path) {
	node_t *dev_node;

	strcat(dev_path, block_dev(dev_id)->name);

	if (NULL == (dev_node = vfs_add_path(dev_path, NULL))) {
		if (NULL == (dev_node = vfs_find_node(dev_path, NULL))) {
			return NODEV;
		}
	}

	dev_node->dev_id = (void *) dev_id;
	block_dev(dev_id)->dev_node = dev_node;

	return 0;
}

dev_t *block_dev_make(char *path, void *driver, void *privdata, dev_t *name_idx) {
	block_dev_t *dev;

	if (num_devs >= MAX_DEV_QUANTITY) {
	  return NULL;
	}

	dev = (block_dev_t *) pool_alloc(&blockdev_pool);
	if (!dev) {
		return NULL;
	}
	memset(dev, 0, sizeof(block_dev_t));

	dev->id = (dev_t) index_alloc(&block_dev_idx, INDEX_ALLOC_MIN);
	devtab[dev->id] = dev;

	nip_tail(path, dev->name);
	create_name (dev->name, name_idx);

	dev->driver = driver;
	dev->privdata = privdata;

	if(0 > block_dev_node_create(&dev->id, path)) {
		pool_free(&blockdev_pool, dev);
		index_free(&block_dev_idx, dev->id);
		return NULL;
	}
	num_devs++;
	return &dev->id;
}

/*
dev_t block_dev_open(char *name) {
	dev_t d = block_devno(name);
	if (d != NODEV) {
	  devtab[d]->refcnt++;
	}
	return d;
}


int block_dev_close(dev_t devno) {
	if(devno < 0 || devno >= num_devs) {
		return -ENODEV;
	}
	if(block_dev(devno)->refcnt == 0) {
		return -EPERM;
	}
	block_dev(devno)->refcnt--;
	return 0;
}
*/

int block_dev_read(void *p_dev, char *buffer, size_t count, blkno_t blkno) {
	block_dev_t *dev;

	if (NULL == p_dev) {
		return -ENODEV;
	}
	dev = block_dev(p_dev);
	if (!dev->driver->read) {
		return -ENOSYS;
	}


	return dev->driver->read(dev, buffer, count, blkno);
}

int block_dev_write(void *dev_id, char *buffer, size_t count, blkno_t blkno) {
	block_dev_t *dev;

	if (NULL == dev_id) {
		return -ENODEV;
	}
	dev = block_dev(dev_id);
	if (!dev->driver->write) {
		return -ENOSYS;
	}

	return dev->driver->write(dev, buffer, count, blkno);
}

int block_dev_ioctl(void *dev_id, int cmd, void *args, size_t size) {
	block_dev_t *dev;

	if (NULL == dev_id) {
		return -ENODEV;
	}
	dev = block_dev(dev_id);

	if (!dev->driver->ioctl) {
		return -ENOSYS;
	}

	return dev->driver->ioctl(dev, cmd, args, size);
}

block_dev_cache_t *block_dev_cache_init(void *dev_id, int blocks) {
	int pagecnt;
	block_dev_cache_t *cache;
	block_dev_t *dev;

		if (NULL == dev_id) {
			return NULL;
		}
		dev = block_dev(dev_id);

	if (NULL == dev->cache) {
		cache = (block_dev_cache_t *) pool_alloc(&cache_pool);
		dev->cache = cache;
	}
	else {
		cache = dev->cache;
	}
	cache->lastblkno = -1;
	cache->buff_cntr = -1;

	if(0 >= (cache->blksize =
			block_dev_ioctl(dev, IOCTL_GETBLKSIZE, NULL, 0))) {
		return NULL;
	}

	pagecnt = 1;
	if(cache->blksize > PAGE_SIZE()) {
		pagecnt = cache->blksize / PAGE_SIZE();
		if(cache->blksize % PAGE_SIZE()) {
			pagecnt++;
		}
	}
	cache->blkfactor = pagecnt;

	if(NULL == (cache->pool = page_alloc(__phymem_allocator, blocks * pagecnt))) {
		return NULL;
	}
	cache->depth = blocks;

	return  cache;
}

block_dev_cache_t *block_dev_cached_read(void *dev_id, blkno_t blkno) {
	block_dev_cache_t *cache;
	block_dev_t *dev;

	if (NULL == dev_id) {
		return NULL;
	}
	dev = block_dev(dev_id);

	if(NULL == (cache = dev->cache)) {
		return NULL;
	}

	/* set pointer to the buffer in pool */
	if(cache->lastblkno != blkno) {
		cache->buff_cntr++;
		cache->buff_cntr %= cache->depth;

		cache->data = cache->pool + cache->buff_cntr * PAGE_SIZE() * cache->blkfactor;
		cache->blkno = blkno;

		block_dev_read(dev, cache->data, cache->blksize, cache->blkno);
		cache->lastblkno = blkno;
	}

	return cache;
}

static int block_dev_cache_free(void *dev_id) {
	block_dev_t *dev;
	block_dev_cache_t *cache;

	if (NULL == dev_id) {
		return -1;
	}
	dev = block_dev(dev_id);

	if (NULL == dev->cache) {
		return 0;
	}
	else {
		cache = dev->cache;
	}

	page_free(__phymem_allocator, cache->pool, cache->depth * cache->blkfactor);
	pool_free(&cache_pool, cache);

	return  0;
}

int block_dev_destroy (void *dev_id) {
	block_dev_t *dev;

	if(NULL ==(dev = block_dev(dev_id))) {
		return NODEV;
	}
	else {
		block_dev_cache_free(dev);
		//index_free(dev->indexator, (int) dev->idx);

		pool_free(&blockdev_pool, dev);
		num_devs--;
		return 0;
	}
}
