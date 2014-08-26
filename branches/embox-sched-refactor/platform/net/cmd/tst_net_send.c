/*
 * tst_net_send.c
 **В файле приведены функции, обеспечивающие проверку передачи пакета  ОБИ по протоколу UDP.
 * Создается сокет для обмена с ОБИ в протоколе UDP.
 * Порт обмена 44559 Адрес получателя 192.168.0.105
 * Функция tst_net_s(int argc, char **argv) включает последовательность функций, обеспечивающих
 * работу передачи пакета (10 байт 0x61) данных  ОБИ .
 * запуск tst_net_send
 */
#include <stdlib.h>
#include <stdio.h>
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
#include <hal/clock.h>
#include <kernel/time/ktime.h>
#include <kernel/time/clock_source.h>

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

#define SECONDS_1900_1970 2208988800L

int main(int argc, char **argv) {
	unsigned char str[2000];
	int sock1;
	unsigned int len_str;
	struct sockaddr_in addr_out, *addr_out_p;
	char buf[256];

	printf("tst_net_s\n");
	memset(buf, 0, sizeof(buf));
	memset(str, 0x39, 10);
	len_str = 10;

	sock1 = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock1 < 0) {
		printf("Error.. can't create socket1. errno=%d\n", errno);
		return 0;
	}

	addr_out_p = get_ip_addr(argv[argc - 1], &addr_out);
	if (sendto(sock1, str, len_str, 0, (struct sockaddr *) addr_out_p,
			sizeof(*addr_out_p)) < 0) {
		printf("Error.. sendto\n");
	}

	close(sock1);

	return 0;

}

