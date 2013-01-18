/**
 * @file
 * @brief
 *
 * @date 03.04.12
 * @author Ilia Vaprol
 */

#include <string.h>
#include <net/ip.h>
#include <arpa/inet.h>
#include <net/socket.h>
#include <framework/example/self.h>
#include <prom/prom_printf.h>

EMBOX_EXAMPLE(exec);

#define LISTENING_PORT 21

static int exec(int argc, char **argv) {
	int sock, client, res;
	struct sockaddr_in addr;
	struct sockaddr_in dst;
	int dst_addr_len = 0;
	char buff[1024];

	prom_printf("Hello, I'm tcp_sender at %d port. I will send all your messages to my client.\n",
			LISTENING_PORT);


	res = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (res < 0) {
		prom_printf("can't create socket %d!\n", res);
		return res;
	}
	sock = res;

	addr.sin_family = AF_INET;
	addr.sin_port= htons(LISTENING_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	res = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0) {
		prom_printf("error at bind() %d!\n", res);
		return res;
	}

	res = listen(sock, 1);
	if (res < 0) {
		prom_printf("error at listen() %d!\n", res);
		return res;
	}

	res = accept(sock, (struct sockaddr *)&dst, &dst_addr_len);
	if (res < 0) {
		prom_printf("error at accept() %d\n", res);
		return res;
	}
	client = res;

	prom_printf("client from %s:%d was connected\n",
			inet_ntoa(dst.sin_addr), ntohs(dst.sin_port));

	/* read from sock, print */
	while (1) {
		scanf("%s", buff);
		prom_printf("send: '%s'\n", buff);
		if (strncmp(buff, "quit", 4) == 0) {
			break;
		}
		if (sendto(client, buff, strlen(buff), 0, (struct sockaddr *)&dst,
				dst_addr_len) < 0) {
			break;
		}
	}

	close(client);
	close(sock);

	prom_printf("Bye bye!\n");

	return 0;
}
