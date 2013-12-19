/**
 * @file
 * @brief
 *
 * @date 27.03.2012
 * @author Andrey Gazukin
 */

#include <types.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <fs/ramfs.h>
#include <drivers/ramdisk.h>
#include <fs/fat.h>
#include <embox/cmd.h>
#include <mem/page.h>
#include <cmd/mkfs.h>


#define MIN_ARGS_OF_MKFS 3 /* <mkfs -q /dev/ram0> must create ramdisk*/
#define DEFAULT_BLOCK_QTTY  0x20
#define DEFAULT_FS_NAME  "vfat"
#define DEFAULT_FS_TYPE  12


EMBOX_CMD(exec);

static int mkfs_do_operation(size_t blocks, char *path, const char *fs_name,
		unsigned int fs_type, unsigned int operation_flag);

static void print_usage(void) {
	printf("Usage: mkfs [ -t type ] file [ blocks ]\n");
}

static int check_invalid(int min_argc, int argc, char **argv) {
	if (min_argc > argc){
		printf("Invalid option `-%c' `%s'\n", optind, argv[optind]);
		print_usage();
		return EINVAL;
	}
	else {
		return 0;
	}
}

static int exec(int argc, char **argv) {
	int opt;
	int min_argc;
	unsigned int operation_flag;
	size_t       blocks;
	char         *path;
	const char   *fs_name;
	unsigned int fs_type;

	min_argc = MIN_ARGS_OF_MKFS;

	operation_flag = 0;
	fs_name = DEFAULT_FS_NAME;
	fs_type = DEFAULT_FS_TYPE;
	blocks = DEFAULT_BLOCK_QTTY;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "ht:q:"))) {
		switch (opt) {
		case 't':
			min_argc = 4;
			fs_name = optarg;
			if(check_invalid(min_argc, argc, argv)){
				return -EINVAL;
			}
			operation_flag |= MKFS_FORMAT_DEV;
			break;
		case 'q':
			min_argc += 1;
			operation_flag |= MKFS_CREATE_RAMDISK;
			if(check_invalid(min_argc, argc, argv)){
				return -EINVAL;
			}
			break;
		case '?':
			if(check_invalid(min_argc, argc, argv)){
				return -EINVAL;
			}
			break;
		case 'h':
			print_usage();
			return 0;
		default:
			return 0;
		}
	}

	if (argc > 1) {
		if (argc > min_argc) {/** last arg should be block quantity*/
			if(0 >= sscanf(argv[argc - 1], "%d", &blocks)){
				print_usage();
				return -EINVAL;
			}
			path = argv[argc - 2];
		}
		else {/** last arg should be diskname*/
			path = argv[argc - 1];
		}

		return mkfs_do_operation(blocks, path,
				                 fs_name, fs_type, operation_flag);
	}
	return 0;
}

static int mkfs_do_operation(size_t blocks, char *path, const char *fs_name,
						unsigned int fs_type, unsigned int operation_flag) {
	ramdisk_create_params_t new_ramdisk;
	struct fs_drv *fs_drv;
	int rezult;

	if(operation_flag & MKFS_CREATE_RAMDISK) {
		new_ramdisk.size = blocks * PAGE_SIZE();
		new_ramdisk.path = path;
		new_ramdisk.fs_name = fs_name;
		new_ramdisk.fs_type = fs_type;

		if(0 > (rezult = ramdisk_create((void *) &new_ramdisk))) {
			return rezult;
		}
	}

	if(operation_flag & MKFS_FORMAT_DEV) {
		/* find filesystem driver by name */
		if(NULL == (fs_drv =
				filesystem_find_drv((const char *) fs_name))) {
			return -EINVAL;
		}

		/* format filesystem */
		if (0 != (rezult = fs_drv->fsop->format((void *) path))) {
			return rezult;
		}
	}
	return 0;
}