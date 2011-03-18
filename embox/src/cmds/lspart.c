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

static int exec(int argsc, char **argsv) {
	int nextOption;
	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "h");
		switch(nextOption) {
		case 'h':
			print_usage();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != nextOption);

	fs_print_all_partitions();

	/* for debugging */
/*
	TRACE("\n\n");
	fs_add_new_partition("user_partition_1", 0x40000, 0x20000, 1);
	fs_print_all_partitions();
*/
	return 0;
}
