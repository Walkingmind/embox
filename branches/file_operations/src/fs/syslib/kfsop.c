/*
 * @file
 *
 * @date Nov 29, 2012
 * @author: Anton Bondarev
 */

#include <unistd.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#include <fs/vfs.h>
#include <fs/path.h>
#include <fs/fs_drv.h>

static node_t *create_filechain(const char *name, uint8_t node_type) {
	int newnode_cnt;
	fs_drv_t *drv;
	struct node *node, *new_node;
	struct nas *nas;
	char path[MAX_LENGTH_PATH_NAME];
	char tail[MAX_LENGTH_PATH_NAME];

	strncpy(path, name, MAX_LENGTH_PATH_NAME);
	newnode_cnt = 0;
	tail[0] = '\0';


	/* find last node in the path */
	do {
		if (path_nip_tail(path, tail)) {
			return NULL;
		}
		newnode_cnt ++;
	} while (NULL == (node = vfs_find_node(path, NULL)));

	/* check drv of parents */
	nas = node->nas;
	drv = nas->fs->drv;
	if ((NULL == drv) || (NULL == drv->fsop->create_node)) {
		return NULL;
	}

	/* add one directory and assign the parameters of the parent */
	do {
		path_increase_tail(path, tail);

		if (NULL == (new_node = vfs_add_path(path, NULL))) {
			return NULL;
		}

		new_node->type = NODE_TYPE_DIRECTORY;
		if ((LAST_IN_PATH == newnode_cnt) && (NODE_TYPE_FILE == node_type)) {
			new_node->type = NODE_TYPE_FILE;
		}

		if(0 > drv->fsop->create_node(node, new_node)) {
			vfs_del_leaf(new_node);
			return NULL;
		}

		node = new_node;
		newnode_cnt--;

	} while (0 < newnode_cnt);

	return node;
}

int kcreate(const char *pathname, mode_t mode) {
	node_t *nod;

	/* if node already exist return error */
	if (NULL != (nod = vfs_find_node(pathname, NULL))) {
		errno = EBUSY;
		return -1;
	}

	/* get last exist node */

	/* set permission */

	if (NULL == (nod = create_filechain(pathname, NODE_TYPE_FILE))) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

int kmkdir(const char *pathname, mode_t mode) {
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

int kremove(const char *pathname) {
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

int kunlink(const char *pathname) {
	node_t *node;
	fs_drv_t *drv;
	struct nas *nas;

	node = vfs_find_node(pathname, NULL);
	if(0 == (node->type & S_IWRITE)) {
		return -EPERM;
	}
	nas = node->nas;
	drv = nas->fs->drv;

	return drv->fsop->delete_node (node);
}

int krmdir(const char *pathname) {
	node_t *node;
	fs_drv_t *drv;
	struct nas *nas;

	node = vfs_find_node(pathname, NULL);
	nas = node->nas;
	drv = nas->fs->drv;

	return drv->fsop->delete_node(node);
}


int klstat(const char *path, stat_t *buf) {
	return 0;
}
