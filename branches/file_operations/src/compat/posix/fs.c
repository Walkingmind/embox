/**
 * @file
 *
 * @brief
 *
 * @date 16.09.2011
 * @author Anton Bondarev
 */

#include <fs/fs_drv.h>
#include <unistd.h>
#include <fcntl.h>
#include <fs/file_operation.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <fs/file_desc.h>
#include <util/array.h>
#include <fs/path.h>

node_t *create_filechain(const char *path, uint8_t node_type){
	int count_dir;
	file_create_param_t param;
	fs_drv_t *drv;
	struct node *node, *new_node;
	struct nas *nas, *new_nas;
	char tail[MAX_LENGTH_FILE_NAME];

	count_dir = 0;
	tail[0] = '\0';
	strncpy (param.path, path, MAX_LENGTH_PATH_NAME);

	/* find last node in the path */
	do {
		if (path_nip_tail(param.path, tail)) {
			return NULL;
		}
		count_dir ++;
	} while (NULL == (node = vfs_find_node(param.path, NULL)));
	/* check drv of parents */
	nas = node->nas;
	drv = nas->fs->drv;

	if ((NULL == drv) || (NULL == drv->fsop->create_node)) {
		return NULL;
	}

	/* add one directory and assign the parameters of the parent */
	do {
		path_increase_tail(param.path, tail);

		if (NULL == (new_node = vfs_add_path(param.path, NULL))) {
			return NULL;
		}

		new_nas = new_node->nas;
		new_nas->fs->drv = nas->fs->drv;
		new_node->properties = NODE_TYPE_DIRECTORY;
		if ((LAST_IN_PATH == count_dir) && (NODE_TYPE_FILE == node_type)) {
			new_node->properties = NODE_TYPE_FILE;
		}

		param.node = (void *) new_node;
		param.parents_node = (void *) node;
		new_node->nas = &param;
		if(0 > drv->fsop->create_node(node, new_node)) {
			vfs_del_leaf(new_node);
			return NULL;
		}

		node = new_node;
		count_dir--;

	} while (0 < count_dir);

	return node;
}

int create(const char *pathname, mode_t mode) {
	node_t *nod;

	if (NULL != (nod = vfs_find_node(pathname, NULL))) {
		errno = EBUSY;
		return -1;
	}

	/* set permission */

	if (NULL == (nod = create_filechain(pathname, NODE_TYPE_FILE))) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

int mkdir(const char *pathname, mode_t mode) {
	node_t *nod;

	if (NULL != (nod = vfs_find_node(pathname, NULL))) {
		errno = EBUSY;
		return -1;
	}

	/* set permission */


	if (NULL == (nod = create_filechain(pathname, NODE_TYPE_DIRECTORY))) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

int remove(const char *pathname) {
	node_t *node;
	struct nas *nas;
	fs_drv_t *drv;

	if (NULL == (node = vfs_find_node(pathname, NULL))) {
		errno = ENOENT;
		return -1;
	}

	nas = node->nas;
	drv = nas->fs->drv;
	if (NULL == drv->fsop->delete_node) {
		errno = EINVAL;
		return -1;
	}

	if (node_is_directory(node)) {
		return rmdir(pathname);
	}
	else {
		return unlink(pathname);
	}
}

int unlink(const char *pathname) {
	node_t *node;
	fs_drv_t *drv;
	struct nas *nas;

	node = vfs_find_node(pathname, NULL);
	if(0 == (node->properties & S_IWRITE)) {
		return -EPERM;
	}
	nas = node->nas;
	drv = nas->fs->drv;

	return drv->fsop->delete_node (node);
}

int rmdir(const char *pathname) {
	node_t *node;
	fs_drv_t *drv;
	struct nas *nas;

	node = vfs_find_node(pathname, NULL);
	nas = node->nas;
	drv = nas->fs->drv;

	return drv->fsop->delete_node(node);
}

int stat(const char *path, stat_t *buf) {
	return lstat(path, buf);
}

int lstat(const char *path, stat_t *buf) {
	//node_t *node;


	//node = vfs_find_node(path, NULL);
//	drv = node->fs_type;

	return 0;//drv->file_op->fstat (node->fi, buf);
}

