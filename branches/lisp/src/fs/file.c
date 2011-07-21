/**
 * @file
 *
 * @date 06.08.09
 * @author Anton Bondarev
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <lib/list.h>
#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <util/array.h>

typedef struct lsof_map {
	struct list_head *next;
	struct list_head *prev;
	const char        path[CONFIG_MAX_LENGTH_FILE_NAME];
	FILE             *fd;
	int 			  id;
	char 			  unchar;
} lsof_map_t;

static lsof_map_t lsof_pool[CONFIG_QUANTITY_NODE];
static LIST_HEAD(free_list);
static LIST_HEAD(fd_cache);

#define fd_to_head(file) (uint32_t)(file - offsetof(lsof_map_t, fd))

void lsof_map_init(void) {
	size_t i;
	for (i = 0; i < ARRAY_SIZE(lsof_pool); i++) {
		list_add((struct list_head *) &lsof_pool[i], &free_list);
	}
}
static int file_id = 10;
static int cache_fd(const char *path, FILE *file) {
	lsof_map_t *head;
	int fid = file_id++;
	if (list_empty(&free_list)) {
		return -1;
	}
	head = (lsof_map_t *) free_list.next;
	head->fd = file;
	head->id = fid;
	strcpy((void*) head->path, path);
	list_move((struct list_head*) head, &fd_cache);
	return fid;
}

static void uncache_fd(FILE *file) {
	list_move((struct list_head*) fd_to_head(file), &free_list);
}

#if 1
static lsof_map_t *find_fd(FILE *file) {
	struct list_head *p;
	list_for_each(p, &fd_cache) {
		if (((lsof_map_t *) p)->fd == file) {
			return (lsof_map_t *) p;
		}
	}
	TRACE("File maybe not opened\n");
	return NULL;
}
int fileno(FILE *stream) {
	return find_fd(stream)->id;
}

FILE *file_struct(int fd) {
	struct list_head *p;
	list_for_each(p, &fd_cache) {
		if (((lsof_map_t *) p)->id == fd) {
			return ((lsof_map_t *) p)->fd;
		}
	}
	return NULL;
}
int getc(FILE *stream) {
	char buf;
	lsof_map_t *map = find_fd(stream);
	if (((int) (buf = map->unchar) )!= EOF) {
		map->unchar = EOF;
		return buf;
	}
	fread(&buf, 1, 1, stream);
	return (int) buf;
}

int ungetc(int c, FILE *stream) {
	lsof_map_t *map = find_fd(stream);
	map->unchar = (char) c;
	return c;
}

#endif

FILE *fopen(const char *path, const char *mode) {
	node_t *nod;
	file_system_driver_t *drv;
	file_operations_t *fop;
	FILE *file;

	nod = vfs_find_node(path, NULL);

	if (nod == NULL) {
		//FIXME: ahtung! workaround.
		ramfs_create_param_t param;
		strcpy(param.name, path);
		param.size = 0;
		param.mode = 0;
		param.start_addr = 0x44100000;
		drv = find_filesystem("ramfs");
		drv->fsop->create_file(&param);
		nod = vfs_find_node(path, NULL);
	}

	if (NULL != nod->file_info) {
		/*if fop set*/
		fop = (file_operations_t *) nod->file_info;
		if (NULL == fop->fopen(path, mode)) {
			return NULL;
		}
		return (FILE *) nod;
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->fopen) {
		LOG_ERROR("fop->fopen is NULL handler\n");
		return NULL;
	}
	file = drv->file_op->fopen(path, mode);
	cache_fd(path, file);
	return file;
}
int open(const char *path, const char *mode) {
	FILE *file = fopen(path, mode);
	return fileno(file);
}
size_t write(int fd, void *buf, size_t count) {
	FILE *file = file_struct(fd);
	return fwrite(buf, 1, count, file);
}

size_t fwrite(const void *buf, size_t size, size_t count, FILE *file) {
	node_t *nod;
	file_system_driver_t *drv;
	nod = (node_t *) file;
	if (NULL == nod) {
		return -EBADF;
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->fwrite) {
		LOG_ERROR("fop->fwrite is NULL handler\n");
		return -1;
	}
	return drv->file_op->fwrite(buf, size, count, file);
}

size_t read(int fd, void *buf, size_t count) {
	FILE *file = file_struct(fd);
	lsof_map_t *map = find_fd(file);
	char ch;
	if ((ch = map->unchar) != EOF) {
		map->unchar = EOF;
		*((char *) buf) = ch;
		return 1 + fread((char *) buf + 1, 1, count - 1, file);
	}
	return fread(buf, 1, count, file);
}

/* FIXME doesn't handle ungetch */
size_t fread(void *buf, size_t size, size_t count, FILE *file) {
	node_t *nod;
	file_system_driver_t *drv;
	nod = (node_t *) file;
	if (NULL == nod) {
		return -EBADF;
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->fread) {
		LOG_ERROR("fop->fread is NULL handler\n");
		return -1;
	}
	return drv->file_op->fread(buf, size, count, file);
}

int fclose(FILE *fp) {
	node_t *nod;
	file_system_driver_t *drv;
	file_operations_t *fop;

	nod = (node_t *) fp;
	if (NULL == nod) {
		return -EBADF;
	}
	if (NULL != nod->file_info) {
		/*if fop set*/
		fop = (file_operations_t *) nod->file_info;
		return fop->fclose(fp);
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->fclose) {
		return -EOF;
	}
	uncache_fd(fp);
	return drv->file_op->fclose(fp);
}

int fseek(FILE *stream, long int offset, int origin) {
	node_t *nod;
	file_system_driver_t *drv;
	nod = (node_t *) stream;

	if (NULL == nod) {
		return -EBADF;
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->fseek) {
		LOG_ERROR("fop->fseek is NULL handler\n");
		return -1;
	}

	return drv->file_op->fseek(stream, offset, origin);
}

int fioctl(FILE *fp, int request, ...) {
	node_t *nod;
	file_system_driver_t *drv;
	va_list args;
	va_start(args, request);

	nod = (node_t *) fp;
	if (NULL == nod) {
		return -EBADF;
	}
	drv = nod->fs_type;
	if (NULL == drv->file_op->ioctl) {
		return -1;
	}
	return drv->file_op->ioctl(fp, request, args);
}

int remove(const char *pathname) {
	node_t *nod = vfs_find_node(pathname, NULL);
	file_system_driver_t *drv = nod->fs_type;
	if (NULL == drv->fsop->delete_file) {
		LOG_ERROR("fsop->delete_file is NULL handler\n");
		return -1;
	}
	return drv->fsop->delete_file(pathname);
}

int fstat(const char *path, stat_t *buf) {
	//FIXME: workaround, ramfs depend.
	node_t *nod;
	ramfs_file_description_t *desc;
	nod = vfs_find_node(path, NULL);
	desc = (ramfs_file_description_t *) nod->attr;
	buf->st_size = desc->size;
	buf->st_mode = desc->mode;
	buf->st_mtime = desc->mtime;
	return 0;
}
