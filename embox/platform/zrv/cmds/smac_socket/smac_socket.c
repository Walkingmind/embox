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
#include <string.h>
#include <arpa/inet.h>


#include <embox/cmd.h>

EMBOX_CMD(smac_socket_main);

static void usage(char *cmd) {
	printf("Usage: %s [-s] start as server\n ip_addr:port\n", cmd);
}
static struct sockaddr_in *get_ip_addr(char *addr, struct sockaddr_in *sockaddr) {
	char *port_str;
	char tmp_addr[0x20];


	strncpy(tmp_addr, addr, sizeof(tmp_addr));

	port_str = strchr(tmp_addr, ':');
	*port_str++ = 0;

	sockaddr->sin_port = htons(atoi(port_str));

	inet_aton(tmp_addr, &sockaddr->sin_addr);

	return sockaddr;
}

static int start_client(struct sockaddr_in *sockaddr) {
	return 0;
}

static int start_server(struct sockaddr_in *sockaddr) {
	return 0;
}

static int smac_socket_main(int argc, char *argv[]) {
	int opt;
	int server = 0;
	struct sockaddr_in sockaddr, *sockaddr_p;


	while (-1 != (opt = getopt(argc, argv, "hs"))) {
		switch(opt) {
		case '?':
		case 'h': /* show help */
				usage(argv[0]);
				return ENOERR;
		case 's':
			server = 1;
			break;
		}
	}

	sockaddr_p = get_ip_addr(argv[argc - 1], &sockaddr);
	if (server) {
		return start_server(sockaddr_p);
	}

	start_client(sockaddr_p);

	return 0;
}
