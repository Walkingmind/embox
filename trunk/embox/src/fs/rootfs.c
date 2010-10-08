/**
 * @file
 *
 * @date 29.06.2009
 * @author Anton Bondarev
 */
#include <string.h>
#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <fs/romfs.h>
#include <fs/fs.h>
#include <linux/init.h>
#include <embox/unit.h>
#include <util/array.h>




#if 0
static int file_list_cnt;

static FILE_INFO * file_list_iterator(FILE_INFO *finfo){
	if (NUMBER_OF_FS  <= file_list_cnt)
		return NULL;
	strncpy (finfo->file_name, fs_list[file_list_cnt].name,
					array_len(finfo->file_name));
	finfo->mode = FILE_MODE_RO;
	finfo->size_in_bytes = 0;
	finfo->size_on_disk = 0;
	file_list_cnt ++;
	return finfo;
}

static FS_FILE_ITERATOR get_file_list_iterator(void){
	file_list_cnt = 0;
	return file_list_iterator;
}

static fsop_desc_t rootfs_op = {
	.get_file_list_iterator = get_file_list_iterator
};

#endif


#if 0
FILE_NAME_STRUCT *parse_file_name(const char *file_name,
					FILE_NAME_STRUCT *file_name_struct) {
	size_t i;
	if ('/' != file_name[0]) {
		return NULL;
	}
	file_name_struct->fs_name[0] = '/';
	for (i = 1; i < array_len(file_name_struct->fs_name); i ++) {
		if ('/' == file_name[i]) {
			file_name_struct->fs_name[i] = 0;
			file_name_struct->file_name = (char *)&file_name[i + 1];
			return file_name_struct;
		}
		file_name_struct->fs_name[i] = file_name[i];
	}
	return NULL;
}

fsop_desc_t *rootfs_get_fsopdesc(char *fs_name){
	size_t i;

	if (0 == strncmp(fs_name, "/", CONFIG_FS_MAX_DISK_NAME_LENGTH)) {
		return &rootfs_op;
	}
	for (i = 0; i < NUMBER_OF_FS; i++){
		if (0 == strncmp(fs_list[i].name, fs_name + 1, array_len(fs_list[i].name))) {
			return (fsop_desc_t *)fs_list[i].fsop;
		}
	}
	return NULL;
}

void *rootfs_fopen(const char *file_name, const char *mode) {
	FILE_NAME_STRUCT fname_struct;
	fsop_desc_t *fsop;
	if (NULL == parse_file_name(file_name, &fname_struct)) {
		TRACE("can't parse file name %s\n (may be wrong format)\n", file_name);
		return NULL;
	}

	if (NULL == (fsop = rootfs_get_fsopdesc((char*)fname_struct.fs_name))) {
		TRACE("can't find file system description for file %s\n"
				"(may be file %s didn't create)\n", file_name, file_name);
		return NULL;
	}
	if (NULL == fsop->open_file) {
		TRACE("can't find open_file function wrong fs operation "
				"descriptor for file %s\n", file_name);
		return NULL;
	}
	return fsop->open_file(fname_struct.file_name, mode);
}
#endif
