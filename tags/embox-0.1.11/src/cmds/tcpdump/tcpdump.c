/**
 * @file
 * @brief dump traffic on a network
 *
 * @date 23.03.2009
 * @author Alexandr Batyukov
 */
#include <shell_command.h>
#include <net/etherdevice.h>
#include <net/socket.h>
#include <net/ip.h>

#define COMMAND_NAME     "tcpdump"
#define COMMAND_DESC_MSG "dump traffic on a network"
#define HELP_MSG         "Usage: tcpdump [-i] [-c] [-h]"
static const char *man_page =
	#include "tcpdump_help.inc"
	;

DECLARE_SHELL_COMMAND(COMMAND_NAME, exec, COMMAND_DESC_MSG, HELP_MSG, man_page);

static int exec(int argsc, char **argsv) {
	int nextOption;
	char *name;
	int count;

	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "i:c:h");
		switch(nextOption) {
		case 'h':
			show_help();
			return 0;
		case 'i':
			name = optarg;
			break;
		case 'c':
			if (1 != sscanf(optarg,"%d", &count)) {
				LOG_ERROR("Parsing: enter validly count '-c'\n");
			}
			break;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != nextOption);

	//eth_listen(eth_get_if (name), 0 /*??*/, NULL);
	//printf("not realized\n");

	return 0;
}
