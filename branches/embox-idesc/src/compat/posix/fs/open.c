/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    04.10.2012
 */
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>

#include <kernel/task/idx.h>
#include <util/array.h>
#include <fs/posix.h>

#include <fs/kfile.h>

struct node *find_node(DIR *dir, char * node_name) {
	struct dirent * dent;

	while (NULL != (dent = readdir(dir))) {
		if (0 == strcmp(dent->d_name, node_name)) {
			return (struct node *)dent->d_ino;
		}
	}

	return NULL;
}
extern struct node *kcreat(struct node *dir, const char *path, mode_t mode);

int open(const char *path, int __oflag, ...) {
	struct file_desc *kfile;
	va_list args;	
	mode_t mode;
	int rc;
	char *parent_path;
	DIR *dir;
	char *name;
	struct node *node;

	if (strlen(path) > PATH_MAX) {
		return -ENAMETOOLONG;
	}

	va_start(args, __oflag);
	mode = va_arg(args, mode_t);
	va_end(args);

	parent_path = dirname((char *)path);
	if (NULL == (dir = opendir(parent_path))) {
		return -1;
	}
	name = basename((char *)path);
	node = find_node(dir, name);

	if (node == NULL) {
		if (__oflag & O_CREAT) {
			if(NULL == kcreat(dir->node, name, mode)) {
				rc =  -1;
				goto out;
			}
			__oflag &= ~(O_CREAT | O_EXCL);
		} else {
			SET_ERRNO(ENOENT);
			rc = -1;
			goto out;
		}
	}

	if (__oflag & O_EXCL) {
		/* If O_EXCL is set and O_CREAT is not set, the result is undefined.*/
		assert(__oflag & O_CREAT);
	}

	if (__oflag & O_EXCL) {
		SET_ERRNO(EEXIST);
		rc = -1;
		goto out;
	}

	kfile = kopen(path, __oflag, mode);
	if (NULL == kfile) {
		rc = -1;
		goto out;
	}

	rc = task_self_idx_alloc(&task_idx_ops_file, kfile, &kfile->ios);
out:
	closedir(dir);

	return rc;
}
