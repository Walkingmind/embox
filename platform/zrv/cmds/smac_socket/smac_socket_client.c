/**
 * @file
 *
 * @date Jun 10, 2014
 * @author: Anton Bondarev
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>


static void usage(char *cmd) {
	printf("Usage: %s use for connect to smac_socket_server\n", cmd);
}

static struct sockaddr_in *get_ip_addr(char *addr, struct sockaddr_in *sockaddr) {
	char *port_str;
	char tmp_addr[0x20];


	strncpy(tmp_addr, addr, sizeof(tmp_addr));

	port_str = strchr(tmp_addr, ':');
	*port_str++ = 0;

	sockaddr->sin_port = htons(atoi(port_str));

	inet_aton(tmp_addr, &sockaddr->sin_addr);

	sockaddr->sin_family = AF_INET;

	return sockaddr;
}

static int create_client_connection(struct sockaddr_in *sockaddr) {
	int res, sock;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	res = connect(sock, (struct sockaddr *)sockaddr, sizeof(*sockaddr));
	if (res < 0) {
		printf("Error... connection refused\n");
	} else { 
		printf("OK... connection succeded\n");
	}

	close(sock);

	return 0;
}

int main(int argc, char *argv[]) {
	int opt;
	struct sockaddr_in sockaddr, *sockaddr_p;

	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch(opt) {
		case '?':
		case 'h': /* show help */
			usage(argv[0]);
			return ENOERR;

		}
	}

	sockaddr_p = get_ip_addr(argv[argc - 1], &sockaddr);

	create_client_connection(sockaddr_p);

	return 0;
}
