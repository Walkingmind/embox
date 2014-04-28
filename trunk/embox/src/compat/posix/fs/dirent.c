/**
 * @file
 * @brief
 *
 * @date 04.02.13
 * @author Alexander Kalmuk
 * @author Anton Kozlov
 */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <fs/perm.h>
#include <fs/vfs.h>
#include <mem/objalloc.h>
#include <util/dlist.h>
#include <fs/flags.h>
#include <framework/mod/options.h>

#include <dirent.h>
#include <dirent_impl.h>

#define MAX_DIR_QUANTITY OPTION_GET(NUMBER, dir_quantity)

OBJALLOC_DEF(dir_pool, DIR, MAX_DIR_QUANTITY);

DIR *opendir(const char *path) {
	struct path node_path, leaf;
	DIR *d;
	int res;

	if (!strcmp(path, ".")) {
		char cur_path[PATH_MAX];

		path = getcwd(cur_path, PATH_MAX);
	}

	vfs_get_leaf_path(&leaf);
	if (0 != (res = fs_perm_lookup(&leaf, path, NULL, &node_path))) {
		SET_ERRNO(-res);
		return NULL;
	}

	if (!node_is_directory(node_path.node)) {
		SET_ERRNO(ENOTDIR);
		return NULL;
	}

	if (0 != fs_perm_check(node_path.node, FS_MAY_READ)) {
		SET_ERRNO(EACCES);
		return NULL;
	}

	if (NULL == (d = objalloc(&dir_pool))) {
		SET_ERRNO(ENOMEM);
		return NULL;
	}

	d->path = node_path;
	d->current.d_ino = 0;

	return d;
}

int closedir(DIR *dir) {
	if (NULL == dir) {
		SET_ERRNO(EBADF);
		return -1;
	}

	objfree(&dir_pool, dir);

	return 0;
}

struct dirent *readdir(DIR *dir) {
	struct path child;

	SET_ERRNO(0);

	if (NULL == dir) {
		SET_ERRNO(EBADF);
		return NULL;
	}

	if ( 0 != vfs_get_child_next(&dir->path,
			(struct node *)dir->current.d_ino, &child)) {
		return NULL;
	}

	strcpy(dir->current.d_name, child.node->name);

	dir->current.d_ino = (ino_t)child.node;

	return &dir->current;
}
