/**
 * @file
 * @brief
 *
 * @date 26.11.2012
 * @author Andrey Gazukin
 */

#include <string.h>
#include <embox/unit.h>
#include <util/array.h>

#include <fs/file_system.h>
#include <fs/fs_drv.h>

#include <mem/misc/pool.h>

POOL_DEF(filesystem_pool, struct filesystem, OPTION_GET(NUMBER,fs_quantity));

EMBOX_UNIT_INIT(filesystem_init);

static int filesystem_init(void) {
	return 0;
}

struct filesystem *alloc_filesystem(const char *drv_name) {
	struct filesystem *fs;

	fs = pool_alloc(&filesystem_pool);
	if(NULL == fs) {
		return NULL;
	}

	if(0 != *drv_name) {
		fs->drv = fs_driver_find_drv(drv_name);
	}

	return fs;
}

void free_filesystem(struct filesystem *fs) {
	if (NULL == fs) {
		return;
	}
	pool_free(&filesystem_pool, fs);
}
