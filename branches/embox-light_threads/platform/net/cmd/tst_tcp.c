
/*
 * tst_tcp.c
 *В файле приведены функции, обеспечивающие проверку работы с  ОБИ по протоколу TCP.
 * Создается сокет для обмена с ОБИ в протоколе TCP.
 * Порт обмена 44569 Адрес получателя 192.168.0.105
 * Функция tst_net_tcp(int argc, char **argv) включает последовательность функций, обеспечивающих
 * работу клента. Выполняется передача данных (10 байт 0x31) , ожидается
 * ответный пакет и выводится на экран.
 *запуск  - tst_net_tcp
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <netdb.h>

struct sockaddr_in localaddr_out;// struct for obmen s socket
int ssSocket1;//for prd info
unsigned int contr;
unsigned char creat_socket()
{
    unsigned int ret = 0;
    int reuse;
    localaddr_out.sin_family = AF_INET;
    localaddr_out.sin_port = htons(44569);
    localaddr_out.sin_addr.s_addr = htonl(INADDR_ANY);
    ssSocket1 = socket(PF_INET, SOCK_STREAM, 0);
    if (ssSocket1 < 0) {
    	printf("error open socket\n");
    	return -2;

    }
    reuse = 1;
    if (setsockopt(ssSocket1,SOL_SOCKET,SO_DONTROUTE,&reuse,sizeof(int))!=0) {

    	printf("*sSocket,SOL_SOCKET,SO_DONTROUTE err\n");
    	return -1;
	}

    ret = bind(ssSocket1, (const struct sockaddr *) &localaddr_out, (socklen_t)sizeof(localaddr_out));
    if (ret != 0) {
    	printf("error bind\n");
    	return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
	unsigned char  str[2000];
	unsigned char buff[2000];
	int rc;
	unsigned int len_str;
	unsigned char mas[4] = {0x7f, 0x0, 0x0, 0x1};
	if (creat_socket() != 0) {
    	printf("error creat_socket\n");

    	return 0;

	}

	memcpy ((unsigned char *)localaddr_out.sin_addr.s_addr8, mas, 4);
	printf("localaddr_out.sin_addr.s_addr8 %x\n", localaddr_out.sin_addr.s_addr8[0]);
	printf("localaddr_out.sin_addr.s_addr8 %x\n", localaddr_out.sin_addr.s_addr8[1]);
	printf("localaddr_out.sin_addr.s_addr8 %x\n", localaddr_out.sin_addr.s_addr8[2]);
	printf("localaddr_out.sin_addr.s_addr8 %x\n", localaddr_out.sin_addr.s_addr8[3]);

    rc = connect (ssSocket1, (struct sockaddr *)&localaddr_out, (socklen_t)sizeof(localaddr_out));
    if (rc ) {
    	printf("ошибка вызова  connect %d\n", rc);
    	close(ssSocket1);

    	return 1;
    }

	memset(str, 0x32, 10);
	len_str = 10;

	if ((send(ssSocket1, str , len_str, 0)) < 0) {
			printf("Error.. send\n");
			close(ssSocket1);
			return 0;
	}
	printf("recv\n");
	rc = 0;
	while (1) {
		rc = recv(ssSocket1, buff , 2000, 0);
		if (rc < 0) {
			printf("Error.. recv\n");
			close(ssSocket1);
			return 0;
		}
		if (rc == 10) {
			printf("rc %d\n", rc);
			printf ("buff_rc %x %x %x %x %x %x %x %x %x %x\n",
					buff[0], buff[1], buff[2], buff[3],buff[4],buff[5],
					buff[6], buff[7], buff[8], buff[9]);

			break;
		}
	}

	close(ssSocket1);

	return 0;

}

