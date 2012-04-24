/**
 * @file
 * @brief 
 *
 * @date 24.04.2012
 * @author Andrey Gazukin
 */
#include <embox/cmd.h>
#include <getopt.h>
#include <fs/vfs.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: touch FILE ...\n");
}

static int exec(int argc, char **argv) {
	int opt;
	getopt_init();
	while (-1 != (opt = getopt(argc - 1, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			return 0;
		}
	}

	if (argc > 1) {
		vfs_create_filechain(argv[argc - 1], 0x01);
	}

	return 0;
}



