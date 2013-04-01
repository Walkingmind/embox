/**
 * @file
 * @brief unmount a filesystem
 *
 * @date 21.02.13
 * @author Andrey Gazukin
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <embox/cmd.h>
#include <fs/sys/fsop.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: umount [-h] dir\n");
}

static int exec(int argc, char **argv) {
	int opt;
	char *dir;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "h:"))) {
		switch (opt) {
		case '?':
			break;
		case 'h':
			print_usage();
			return 0;
			/* FALLTHROUGH */
		default:
			return 0;
		}
	}

	if (argc != 2) {
		print_usage();
		return EINVAL;
	}
	dir = argv[argc - 1];

	return umount(dir);
}
