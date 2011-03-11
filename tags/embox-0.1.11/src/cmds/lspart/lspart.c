/**
 * @file
 * @brief
 *
 * @date 20.09.2010
 * @author Batyukov Alexander
 */
#include <shell_command.h>
#include <fs/partition.h>

#define COMMAND_NAME     "lspart"
#define COMMAND_DESC_MSG "prints all existing kernel and user partitions"
#define HELP_MSG         "Usage: lspart [-h]"

static const char *man_page =
	#include "lspart_help.inc"
;

DECLARE_SHELL_COMMAND(COMMAND_NAME, exec, COMMAND_DESC_MSG, HELP_MSG, man_page);

static int exec(int argsc, char **argsv) {
	int nextOption;
	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "h");
		switch(nextOption) {
		case 'h':
			show_help();
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
