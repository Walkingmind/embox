/**
 * @file
 * @brief
 *
 * @date 20.09.10
 * @author Batyukov Alexander
 */

#include <embox/cmd.h>
#include <getopt.h>
#include <fs/partition.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: lspart [-h]\n");
}

static int exec(int argc, char **argv) {
	int opt;
	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			return 0;
		}
	}

	fs_print_all_partitions();

	return 0;
}
