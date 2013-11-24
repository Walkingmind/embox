/*
 * grid.c
 *
 *  Created on: 2013 6 6
 *      Author: alexander
 */

#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <kernel/thread.h>
#include <kernel/printk.h>

#include <utmp.h>

#include <net/l3/ipv4/ip.h>
#include <sys/socket.h>
#include <net/inetdevice.h>

#include <util/ring_buff.h>
#include <util/math.h>

#include <kernel/task.h>

#include <embox/cmd.h>
#include <cmd/shell.h>
#include <util/dlist.h>
#include <kernel/thread/sync/mutex.h>
#include <kernel/thread/sync/cond.h>
#include <mem/misc/pool.h>
#include <readline/readline.h>
#include <kernel/time/ktime.h>
#include "grid_types.h"
#include <stdlib.h>

static int grid_do_int(int num, int client_num);
static void grid_do_info(int client_num);

EMBOX_CMD(exec);

struct grid_task;


	/* Upper limit of concurent telnet connections.
	 * ToDo: move those into config files
	 */
#define MD(x) 
#define GRID_MAX_CONNECTIONS 5
static struct {
	int fd;
	struct grid_task *grid_task;
	struct sockaddr_in addr_in;
	struct mutex mutex;
} clients[GRID_MAX_CONNECTIONS];
	/* Telnetd address bind to */
#define GRID_ADDR INADDR_ANY
	/* Telnetd port bind to */
#define GRID_PORT 40000
#define GRID_TASK_MAX_COUNT 0x10

struct grid_task {
	struct dlist_head link;
	int task_num;
	int client_num;
};

static DLIST_DEFINE(grid_pending_task_list);
/*static DLIST_DEFINE(grid_running_task_list);*/
POOL_DEF(grid_task_pool, struct grid_task, GRID_TASK_MAX_COUNT);

static cond_t pending_cond;
static struct mutex pending_mutex;
static struct timespec calc_time;

static void gtask_free(struct grid_task *task) {
	pool_free(&grid_task_pool, task);
}

static void *grid_connection_handler(void* args) {
	fd_set readfds;
	struct timeval timeout;
	int client_num = (int) args;
	int sock = clients[client_num].fd;

	MD(printk("grid_connection_handler\n"));
	/* Set socket to be nonblock. See ignore_telnet_options() */
	//fcntl(sock, F_SETFD, O_NONBLOCK);

	timeout.tv_sec = 100;
	timeout.tv_usec = 0;

	while(1) {
		int fd_cnt;
		int buf[3], inbuf[3];
		int fd;
		struct grid_task *gtask;

		FD_ZERO(&readfds);

		FD_SET(sock, &readfds);

		fd_cnt = select(sock + 1, &readfds, NULL, NULL, &timeout);

		if (fd_cnt <= 0) {
			continue;
		}

		gtask = clients[client_num].grid_task;

		read(sock, &inbuf, sizeof(inbuf));

		switch(inbuf[0]) {
		case GRID_MSG_INFO:
			grid_do_info(client_num);
			break;
		case GRID_MSG_CALC:

			grid_do_int(inbuf[1], client_num);

			break;
		case GRID_MSG_INTERMEDIATE_RESULT:

			fd = clients[gtask->client_num].fd;

			buf[0] = GRID_MSG_FINISH_RESULT;
			buf[1] = gtask->task_num;
			buf[2] = inbuf[1];

			write(fd, buf, sizeof(buf));

			clients[client_num].grid_task = NULL;

			gtask_free(gtask);
			break;
		default:
			break;
		}
	}

	close(sock);
	clients[client_num].fd = -1;

	MD(printk("exiting from grid_connection_handler\n"));

	return NULL;
}

static void *grid_server_hnd(void* args) {
	int res;
	int listening_descr;
	struct sockaddr_in listening_socket;

	listening_socket.sin_family = AF_INET;
	listening_socket.sin_port= htons(GRID_PORT);
	listening_socket.sin_addr.s_addr = htonl(GRID_ADDR);

	if ((listening_descr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printk("can't create socket\n");
		return NULL;
	}

	if ((res = bind(listening_descr, (struct sockaddr *)&listening_socket,
					sizeof(listening_socket))) < 0) {
		printk("bind() failed\n");
		goto listen_failed;
	}

	if ((res = listen(listening_descr, GRID_MAX_CONNECTIONS)) < 0) {
		printk("listen() failed\n");
		goto listen_failed;
	}

	MD(printk("grid_sched is ready to accept connections\n"));
	while (1) {
		struct sockaddr_in client_socket;
		int client_socket_len = sizeof(client_socket);
		int client_descr = accept(listening_descr, (struct sockaddr *)&client_socket,
								  &client_socket_len);
		struct thread *thread;
		size_t i;

		if (client_descr < 0) {
			MD(printk("accept() failed. code=%d\n", -errno));
			continue;
		}

		MD(printk("Attempt to connect from address %s:%d\n",
			inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port)));

		for (i = 0; i < GRID_MAX_CONNECTIONS; i++) {
			if (clients[i].fd == -1) {
				break;
			}
		}

		if (i >= GRID_MAX_CONNECTIONS) {
			MD(printk("limit of connections exceded\n"));
			close(client_descr);
			continue;
		}

		clients[i].fd = client_descr;
		memcpy(&clients[i].addr_in, &client_socket, sizeof(struct sockaddr_in));

		if (0 != thread_create(&thread, 0, grid_connection_handler, (void *) i)) {
			MD(printk("thread_create error \n"));
		}
	}

	assert(0);
	{
		/* Free resources, don't touch threads, but close socket decriptor
		 * So it'll influence to them
		 */
		for (size_t i = 0; i < GRID_MAX_CONNECTIONS; i++) {
			if (clients[i].fd != -1) {
				close(clients[i].fd);
			}
		}
		close(listening_descr);
	}

	return NULL;

listen_failed:
	res = -errno;
	close(listening_descr);
	return NULL;
}

static int grid_do_int(int num, int client_num) {
	struct grid_task *new_task = pool_alloc(&grid_task_pool);

	if (!new_task) {
		return -1;
	}

	new_task->task_num = num;
	new_task->client_num = client_num;

	dlist_head_init(&new_task->link);
	mutex_lock(&pending_mutex);
	dlist_add_next(&new_task->link, &grid_pending_task_list);
	cond_signal(&pending_cond);
	mutex_unlock(&pending_mutex);
	return 0;
}

static void grid_do_info(int client_num) {
	char *info = malloc(201);
	int off = 0;
	int buf[3];
	if (info == NULL) {
		printk("malloc() failed\n");
		return;
	}
	off = sizeof(buf);
	off += sprintf(info+off, "node %s", "10.0.2.16");
	for (int i = 1; i < GRID_MAX_CONNECTIONS; i++) {
		if (clients[i].fd != -1) {
			off += sprintf(info+off, ", node %s", /*ind++,*/
					inet_ntoa(clients[i].addr_in.sin_addr));
					/*ntohs(clients[i].addr_in.sin_port));*/
		}
	}
	assert(off < 200);
	buf[0] = GRID_MSG_PRINT;
	buf[1] = off - sizeof(buf);
	memcpy(info, buf, sizeof buf);
	send(clients[client_num].fd, info, off, 0);
	free(info);
}

static void *grid_mainloop_hnd(void* args) {
	struct grid_task *gtask;
	struct dlist_head *gtask_link;

	while (1) {
		mutex_lock(&pending_mutex);
		if (dlist_empty(&grid_pending_task_list)) {
			cond_wait(&pending_cond, &pending_mutex);
		}

		while((gtask_link = grid_pending_task_list.next) != &grid_pending_task_list) {
			int i;
			gtask = (struct grid_task *) gtask_link;

			for (i = 0; i < GRID_MAX_CONNECTIONS; i++) {
				int check;

				mutex_lock(&clients[i].mutex);
				check = (clients[i].fd != -1) && !clients[i].grid_task;
				mutex_unlock(&clients[i].mutex);

				if (!check) {
					thread_yield();
					continue;
				}

				dlist_del(&gtask->link);

				clients[i].grid_task = gtask;

				MD(printk("Going to do %d task on %d\n", gtask->task_num, i));

				{
					int buf[3];
					buf[0] = GRID_MSG_CALC;
					buf[1] = gtask->task_num;
					write(clients[i].fd, buf, sizeof(buf));
				}

				break;
			}

			if (i >= GRID_MAX_CONNECTIONS) {
				//assert(0);
			}
		}
		mutex_unlock(&pending_mutex);
	}

	return NULL;
}

static int A(void) {
	sleep(1);
	return 111111;
}

static int B(void) {
	sleep(1);
	return 2222222;
}

static int C(void) {
	sleep(1);
	return 3333333;
}

typedef int (*grid_fn_t)(void);

grid_fn_t __grid_fn_table[] = {
		A,
		B,
		C
};

static void write_buf(int sock, enum grid_msg_type type, int num) {
	int buf[3];
	buf[0] = type;
	buf[1] = num;

	write(sock, buf, sizeof(buf));
}

static char task_mask;
static int task_res[3];

static char client_list[200];
static char list_print;

static void *client_handler(void *args) {
	int sock = * (int *) args;
	while (1) {
		fd_set readfds;
		int res;
		int buf[3];

		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);

		select(sock + 1, &readfds, NULL, NULL, NULL );

		if (FD_ISSET(sock, &readfds)) {
			read(sock, buf, sizeof(buf));

			switch(buf[0]) {
			case GRID_MSG_FINISH_RESULT:

				task_res[buf[1]] = buf[2];

				task_mask |= 1 << buf[1];

				if (task_mask == 0xf) {
					struct timespec curtime;

					ktime_get_timespec(&curtime);
					calc_time = timespec_sub(curtime, calc_time);

					printk("a+b+c = %d; time=%d,%03d; %s\ngrid> ",
							task_res[0] + task_res[1] + task_res[2], 
							(int)calc_time.tv_sec, (int)(calc_time.tv_nsec / 1000000),
							client_list);

				}

				break;
			case GRID_MSG_CALC:
				res = __grid_fn_table[buf[1]]();
				buf[0] = GRID_MSG_INTERMEDIATE_RESULT;
				buf[1] = res;
				write(sock, buf, sizeof(buf));
				break;
			case GRID_MSG_PRINT:
				read(sock, client_list, buf[1]);

				if (list_print) {
					write(1, client_list, buf[1]);
					printk("\ngrid> ");
				}

				task_mask |= 0x8;
				break;
			}
		}
	}

	return NULL;
}

static int exec(int argc, char *argv[]) {
	struct thread *thread;
	int sock = 0;
	const int port = 40000;
	char *addr = argv[1];
	char *uline;
	struct thread *client_thd;

	struct sockaddr_in dst;

	if (argc == 1) {
		int i;
		mutex_init(&pending_mutex);
		cond_init(&pending_cond, NULL);

		for (i = 0; i < GRID_MAX_CONNECTIONS; i++) {
			clients[i].fd = -1;
			mutex_init(&clients[i].mutex);
			clients[i].grid_task = NULL;
		}

		thread_create(&thread, 0, grid_server_hnd, NULL);
		thread_create(&thread, 0, grid_mainloop_hnd, NULL);
		addr = "127.0.0.1";

		sleep(1);

	}

	if (!inet_aton(addr, &dst.sin_addr)) {
		printk("Error...Invalid ip address '%s'", argv[1]);
		return -1;
	}

	dst.sin_family = AF_INET;
	dst.sin_port = htons((unsigned short)port);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		printk("can't create socket!");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&dst, sizeof dst) < 0) {
		printk("Error... Cant connect to remote address %s:%d\n",
				inet_ntoa(dst.sin_addr), (unsigned short)port);
		close(sock);
		return -1;
	}

	printk("Connection established\n");

	thread_create(&client_thd, 0, client_handler, &sock);

	while ((uline = readline("grid> "))) {
		if (!strcmp(uline, "calc")) {
			task_mask = 0;
			list_print = 0;
			ktime_get_timespec(&calc_time);

			write_buf(sock, GRID_MSG_CALC, 0);
			write_buf(sock, GRID_MSG_CALC, 1);
			write_buf(sock, GRID_MSG_CALC, 2);
			write_buf(sock, GRID_MSG_INFO, 0);
		} else if (!strcmp(uline, "exit")) {
			free(uline);
			break;
		}
		else if (!strcmp(uline, "info")) {
			list_print = 1;
			write_buf(sock, GRID_MSG_INFO, 0);
		}
		free(uline);
	}

	close(sock);

	return 0;
}
