/*
 * tst_net_recv.c
 *В файле приведены функции, обеспечивающие проверку приема пакетов от ОБИ по протоколу UDP.
 * Создается сокет для обмена с ОБИ в протоколе UDP.
 * Порт обмена 44559
 * Функция tst_net_r(int argc, char **argv) включает последовательность функций, обеспечивающих
 * работу приема пакета данных от ОБИ и вывод принятой информации на экран.
 *запуск функции tst_net_recv
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <drivers/diag.h>
#include <util/macro.h>

#define SIZE_BUF_IN 2000
static unsigned char buf_in[SIZE_BUF_IN];

int main(int argc, char **argv) {
	int res, sock;
	struct sockaddr_in addr;
	struct sockaddr addr2;
	socklen_t addr_len;
	int ret;
	int ch;
	unsigned int i;
	fd_set readfds;
	struct timeval tv;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[argc-1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	addr_len = sizeof addr2;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		printf("Error.. can't create socket. errno=%d\n", errno);
		return 0;
	}

	res = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (res < 0) {
		printf("Error.. bind() failed. errno=%d\n", errno);
		return 0;
	}

	while (1) {
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);

		res = select(sock + 1, &readfds, NULL, NULL, &tv);
		if (res > 0) {
			if (FD_ISSET(sock, &readfds)) {
				ret = recvfrom(sock, buf_in, SIZE_BUF_IN, 0, &addr2, &addr_len);
				if ((ret != -1) && (ret != 0)) {
					printf("\n");
					for (i = 0; i < ret; i++)
						printf("%c", buf_in[i]);
					printf("\n");
				}
			}
		}

		if (diag_kbhit() == KBHIT_CAN_GETC) {
			ch = getchar();
			if (ch == 0x1b)
				break;
		}
	}
	close(sock);
	return 0;

}

