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
	printf("Usage: %s use only smac_socket_server\n", cmd);
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

static int create_server_connection(struct sockaddr_in *sockaddr) {
	int res, sock;

	/* Create listen socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		printf("Error.. can't create socket. errno=%d\n", errno);
		return sock;
	}

	res = bind(sock, (struct sockaddr *)&sockaddr, sizeof(*sockaddr));
	if (res < 0) {
		printf("Error.. bind() failed. errno=%d\n", errno);
		return res;
	}

	res = listen(sock, 1);
	if (res < 0) {
		printf("Error.. listen() failed. errno=%d\n", errno);
		return res;
	}
	while (1) {
		res = accept(sock,(struct sockaddr *)&addr, &addr_len);
		if (res <= 0) {
			/* error code in client, now */
			printf("Error.. accept() failed. errno=%d\n", errno);
			continue;
		}

	}
	close(sock);
    return 0;
}

static int smac_socket_main(int argc, char *argv[]) {
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

	create_server_connection(sockaddr_p);

	return 0;
}
