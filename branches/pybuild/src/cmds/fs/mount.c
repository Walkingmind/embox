/**
 * @file
 * @brief mount a filesystem
 *
 * @date 29.09.10
 * @author Nikolay Korotky
 */

#include <embox/cmd.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>

#include <fs/vfs.h>
#include <fs/mount.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: mount [-h] [-t fstype] dev dir\n");
}

#define NO_DEV_STR "\0\0"
static int mount_dev(char *dev, char *fs_type, char *dir) {
	mount_params_t param;
	node_t *dev_node;
	node_t virt_dev;
	fs_drv_t * drv = NULL;

	param.dev = dev;
	param.dir = dir;

	if(NULL == (dev_node = vfs_find_node((const char *) dev, NULL))) {
		if(0 != strcmp((const char *) fs_type, "nfs")) {
			printf("mount: no such device\n");
			return -ENODEV;
		}
		else {
			dev_node = &virt_dev;
			param.dev = NO_DEV_STR;
			param.ext = dev;
		}
	}
	param.dev_node = dev_node;

	if(0 != fs_type) {
		drv = filesystem_find_drv((const char *) fs_type);
		if(NULL == drv) {
			return -EINVAL;
		}
		else {
			if(NULL != dev_node) {
				dev_node->fs_type = drv;
			}
		}
	}

	if(NULL != dev_node) {
		drv = dev_node->fs_type;
	}
	if (NULL == drv->fsop->mount) {
		if(0 == fs_type) {
			printf("try to set \"-t [fstype]\" option\n");
		}
		return  -ENODEV;
	}
	return drv->fsop->mount((void *) &param);
}

static int exec(int argc, char **argv) {
	int opt;
	int opt_cnt;
	char *dev, *dir;
	char *fs_type;

	opt_cnt = 0;
	fs_type = 0;
	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "ht:"))) {
		switch (opt) {
		case 't':
			opt_cnt++;
			break;
		case '?':
			break;
		case 'h':
			print_usage();
			/* FALLTHROUGH */
		default:
			return 0;
		}
	}

	if (argc > 2) {
		dev = argv[argc - 2];
		dir = argv[argc - 1];
		if(argc > 3) {
			if(opt_cnt) {
				fs_type = argv[argc - 3];
			}
			else {
				print_usage();
				return 0;
			}
		}
		return mount_dev(dev, fs_type, dir);
	}
	return 0;
}