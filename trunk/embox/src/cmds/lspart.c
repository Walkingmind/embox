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
	do {
		opt = getopt(argc, argv, "h");
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != opt);

	fs_print_all_partitions();

	/* for debugging */
/*
	TRACE("\n\n");
	fs_add_new_partition("user_partition_1", 0x40000, 0x20000, 1);
	fs_print_all_partitions();
*/
	return 0;
}
