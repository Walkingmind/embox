/**
 * @file
 * @brief dump traffic on a network
 *
 * @date 23.03.2009
 * @author Alexandr Batyukov
 */
#include <embox/cmd.h>
#include <getopt.h>
#include <net/etherdevice.h>
#include <net/socket.h>
#include <net/ip.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: tcpdump [-i] [-c] [-h]\n");
}

static int exec(int argsc, char **argsv) {
	int nextOption;
	char *name;
	int count;

	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "i:c:h");
		switch(nextOption) {
		case 'h':
			print_usage();
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
