/**
 * @file
 * @brief mount a filesystem
 *
 * @date 29.09.10
 * @author Nikolay Korotky
 * @author Andrey Gazukin
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <embox/cmd.h>
#include <fs/fsop.h>
#include <fs/file_system.h>
#include <fs/mount.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <fs/fs_driver.h>

#include <embox/block_dev.h>

#include <mem/phymem.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: mount [-h] [-t fstype] dev dir\n");
}

static int show_mount_list(void) {
	struct dlist_head *mount_list;
	struct mount_descriptor *mdesc, *tmp;
	char mount_path[PATH_MAX];
	const char *fs_name;
	const char *bdev_path;

	if(NULL == (mount_list = mount_table())) {
		return 0;
	}
	dlist_foreach_entry(mdesc, tmp, mount_list, mount_link) {
		vfs_get_path_by_node(mdesc->dir_node, mount_path);
		fs_name = mdesc->dir_node->nas->fs->drv->name;
		bdev_path = mdesc->dir_node->nas->fs->bdev->name;

		printf("%s on %s type %s\n", bdev_path, mount_path, fs_name);
	}
	return 0;
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
		if (argc > 3) {
			if (opt_cnt) {
				fs_type = argv[argc - 3];
			} else {
				print_usage();
				return 0;
			}
		}

		if (0 == fs_type) {
			print_usage();
			printf("try to set \"-t [fstype]\" option\n");
			return 0;
		}

		if(0 > mount(dev, dir, fs_type)) {
			return -errno;
		}
		return 0;
	}

	show_mount_list();

	return 0;
}
