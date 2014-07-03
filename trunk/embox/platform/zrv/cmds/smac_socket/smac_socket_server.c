/**
 * @file
 *
 * @date Jun 9, 2014
 * @author: Anton Bondarev
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void usage(char *cmd) {
	printf("Usage: %s start as server\n ip_addr:port\n", cmd);
}

static int smac_socket_start_server(char *argv[]) {
	int res;

	res = vfork();

	if (-1 == res) {
		printf("error: couldn't vfork()\n");
		return -1;
	}
	if (0 == res) {
		execv("smac_socket_daemon", argv);
	}

	return 0;
}

int main(int argc, char *argv[]) {
	int opt;

	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch(opt) {
		case '?':
		case 'h': /* show help */
			usage(argv[0]);
			return ENOERR;
		}
	}

	return smac_socket_start_server(argv);
}
