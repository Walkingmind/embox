/**
 * @file
 * @brief table of configured filesystems
 *
 * @date 05.10.10
 * @author Nikolay Korotky
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <embox/unit.h>

#include <mem/misc/pool.h>
#include <util/dlist.h>

#include <util/array.h>
#include <fs/fs_driver.h>
#include <util/member.h>

EMBOX_UNIT_INIT(fs_driver_init);

typedef struct fs_driver_head {
	struct dlist_head link;
	struct fs_driver *drv;
} fs_driver_head_t;

POOL_DEF(fs_driver_pool, struct fs_driver_head, OPTION_GET(NUMBER,drivers_quantity));

ARRAY_SPREAD_DEF(const struct fs_driver *, __fs_drivers_registry);

static DLIST_DEFINE(file_systems);


static fs_driver_head_t *fs_driver_alloc(struct fs_driver *drv) {
	fs_driver_head_t *head;

	head = pool_alloc(&fs_driver_pool);
	head->drv = drv;

	dlist_add_next(dlist_head_init(&head->link), &file_systems);

	return head;
}

static void fs_driver_free(struct fs_driver *drv) {
	fs_driver_head_t *head = member_cast_out(drv, fs_driver_head_t, drv);

	dlist_del((struct dlist_head *)head);
	pool_free(&fs_driver_pool, head);
	return;
}

static int fs_driver_init(void) {
	fs_driver_head_t *head;
	size_t i;

	for (i = 0; i < ARRAY_SPREAD_SIZE(__fs_drivers_registry); i++) {
		if (NULL == (head = fs_driver_alloc(
				(struct fs_driver *) __fs_drivers_registry[i]))) {
			return -EINVAL;
		}

		if (NULL != __fs_drivers_registry[i]->fsop->init) {
			__fs_drivers_registry[i]->fsop->init(NULL);
		}
	}

	return ENOERR;
}

struct fs_driver *fs_driver_find_drv(const char *name) {
	struct fs_driver_head *tmp;
	struct fs_driver_head *fs_driver;

	dlist_foreach_entry(fs_driver, tmp, &file_systems, link) {
		if (0 == strcmp(fs_driver->drv->name, name)) {
			return fs_driver->drv;
		}
	}
	return NULL;
}

int ffs_driver_register_drv(struct fs_driver *fs) {
	int res = 0;
	struct fs_driver *p;

	if (NULL == fs) {
		return EINVAL;
	}

	p = fs_driver_find_drv(fs->name);
	if (NULL != p) {
		return -EBUSY;
	}

	return res;
}

int fs_driver_unregister_drv(struct fs_driver *fs) {
	if (NULL == fs) {
		return -EINVAL;
	}
	fs_driver_free(fs);

	return ENOERR;
}