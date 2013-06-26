/**
 * @file
 * @brief
 *
 * @date 24.03.12
 * @author Ilia Vaprol
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <net/l3/ipv4/ip.h>
#include <sys/socket.h>
#include <framework/example/self.h>
#include <kernel/printk.h>
#include <stdio.h>

EMBOX_EXAMPLE(exec);

static int exec(int argc, char **argv) {
	int sockfd, port;
	struct sockaddr_in dst;

	if (argc != 3) {
		printk("Usage: %s <remote ip> <port>", argv[0]);
		return -1;
	}

	if (!inet_aton(argv[1], &dst.sin_addr)) {
		printk("Error...Invalid ip address '%s'", argv[1]);
		return -1;
	}

	if (sscanf(argv[2], "%d", &port) != 1) {
		printk("Error...Invalid port '%s'", argv[2]);
		return -1;
	}

	dst.sin_family = AF_INET;
	dst.sin_port = htons((unsigned short)port);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0) {
		printk("can't create socket!");
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&dst, sizeof dst) < 0) {
		printk("Error... Cant connect to remote address %s:%d\n",
				inet_ntoa(dst.sin_addr), (unsigned short)port);
		close(sockfd);
		return -1;
	}

	printk("Connection established\n");
	close(sockfd);

	return 0;
}
