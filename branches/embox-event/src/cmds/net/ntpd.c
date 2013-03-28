/**
 * @file
 * @brief SNTPv4 client
 *
 * @date 13.07.2012
 * @author Alexander Kalmuk
 */

#include <stdio.h>
#include <errno.h>
#include <embox/cmd.h>
#include <unistd.h>

#include <kernel/task.h>
#include <net/ntp.h>
#include <arpa/inet.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: ntpdate [-q] server");
}

static int exec(int argc, char **argv) {
	int opt;
	struct in_addr sin_addr;

	getopt_init();
	while (-1 != (opt = getopt(argc - 1, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			break;
		}
	}

	if (!inet_aton(argv[argc - 1], &sin_addr)) {
		printf("Invalid ip address %s\n", argv[argc - 1]);
		return -ENOENT;
	}

	ntp_server_set(sin_addr.s_addr);
	ntp_start();

	printf("*Starting NTP daemon\n");

	return 0;
}
