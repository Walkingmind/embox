//control_srv.c

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#include <security/seculog.h>

#include <pthread.h>

#include <embox/cmd.h>

EMBOX_CMD(control_srv);

static struct seculog_desc slog_desc;

static int getMsg(struct seculog_desc *slog_desc, char* buf, size_t len){

	if (0 > seculog_get(slog_desc, buf, len)) {
		*buf = 0;
		return 0;
	}

	return strlen(buf);
}

static void * client_process(void * args) {

	char buf[1024];
	struct timeval tv;

	fd_set fds;
	int bytes;

	int sock, actn, len;

	sock=(int)args;
//	printf("control_srv: Wait request...\n");

	while(1){
		FD_ZERO(&fds);
		FD_SET(sock,&fds);
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		actn = select(sock + 1, &fds, NULL, NULL, &tv);
		if (actn <= 0) {
			break;
		}

		bytes=0;
		memset(buf,0,sizeof(buf));
		bytes = recv( sock, buf, sizeof(buf)-1, 0);
		if(bytes>0) {

			if((!strncmp(buf,"test",4)) && (strlen(buf) == 4)){
//				printf("control_srv: Correct request\n");
				memset(buf,0,sizeof(buf));
				buf[0]='$';
				buf[1]=1;

				send(sock,buf,2,0);
			}
			else if((!strncmp(buf,"next",4)) && (strlen(buf) == 4)){
				memset(buf,0,sizeof(buf));

				len=getMsg(&slog_desc, buf, 1024);
				send(sock,buf,len+1,0);
				if(!len) break;
			}
			else{
				printf("control_srv: Incorrect request\n");
				break;
			}
		}
		else{
			printf("control_srv: len=0\n");
			break;
		}

	}

//	printf("control_srv: closing socket\n");

	close(sock);

	return (void*)0;
}

static int control_srv(int argc, char **argv){
	int res, host;
	socklen_t addr_len;
	struct sockaddr_in addr;
	pthread_t tr;
	int ret;

	addr.sin_family = AF_INET;
	addr.sin_port= htons(7780);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	seculog_open(SECULOG_LABEL_MANDATORY | SECULOG_LABEL_LOGIN_ACT, &slog_desc);

	/* Create listen socket */
	host = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (host < 0) {
		printf("control_srv: Error.. can't create socket. errno=%d\n", errno);
		return host;
	}

	res = bind(host, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0) {
		printf("control_srv: Error.. bind() failed. errno=%d\n", errno);
		return res;
	}

	res = listen(host, 10);
	if (res < 0) {
		printf("control_srv: Error.. listen() failed. errno=%d\n", errno);
		return res;
	}

	while (1) {
		addr_len = sizeof addr;
		res = accept(host,(struct sockaddr *)&addr, &addr_len);
		if (res <= 0) {
			/* error code in client, now */
			printf("control_srv: Error.. accept() failed. errno=%d\n", errno);
			continue;
		} else {
//			printf("control_srv: accept ok\n");
		}

		if(0 != (ret = pthread_create(&tr, 0, client_process, (void *) res))) {
			printf("control_srv: Error.. thread_create() failed. errno=%d\n", ret);
			continue;
		}
		pthread_detach(tr);
	}

	close(host);
	seculog_close(&slog_desc);

	return 0;
}
