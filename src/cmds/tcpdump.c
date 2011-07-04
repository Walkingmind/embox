/**
 * @file
 * @brief dump traffic on a network
 *
 * @date 23.03.09
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

static int exec(int argc, char **argv) {
	int opt;
	char *name;
	int count;

	getopt_init();
	do {
		opt = getopt(argc, argv, "i:c:h");
		switch(opt) {
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
	} while (-1 != opt);

	//eth_listen(eth_get_if (name), 0 /*??*/, NULL);
	//printf("not realized\n");

	return 0;
}
