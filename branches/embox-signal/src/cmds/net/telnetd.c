/**
 * @file
 * @brief Tiny telnetd server
 *
 * @date 18.04.2012
 * @author Vladimir Sokolov
 */

#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <arpa/inet.h>

#include <utmp.h>

#include <net/l3/ipv4/ip.h>
#include <sys/socket.h>
#include <net/inetdevice.h>

#include <util/ring.h>
#include <util/ring_buff.h>
#include <util/math.h>


#include <kernel/task.h>

#include <embox/cmd.h>
#include <cmd/shell.h>

EMBOX_CMD(exec);

	/* Upper limit of concurent telnet connections.
	 * ToDo: move those into config files
	 */
#define TELNETD_MAX_CONNECTIONS 5
static struct {
	int fd;
	struct sockaddr_in addr_in;
} clients[TELNETD_MAX_CONNECTIONS];
	/* Telnetd address bind to */
#define TELNETD_ADDR INADDR_ANY
	/* Telnetd port bind to */
#define TELNETD_PORT 23

	/* Allow to turn off/on extra debugging information */
#if 0
#	define MD(x) do {\
		x;\
	} while (0);
#else
#	define MD(x) do{\
	} while (0);
#endif

#if 0
	/* Out a bunch of different error messages to the output and to the socket */
static void out_msgs(const char *msg, const char *msg2, const char *msg3,
			int client_descr, struct sockaddr_in *client_socket) {
	const int m_len = strlen(msg) + 1;
	MD(printf("%s", msg2));
	if (m_len != sendto(client_descr, msg, m_len, 0,
			(struct sockaddr *)client_socket, sizeof(*client_socket))) {
		MD(printf("Can't write to the socket (%s)\n", msg3));
	}
}
#endif

#define T_WILL		251
#define T_WONT		252
#define T_DO		253
#define T_DONT		254
#define T_IAC		255
#define T_INTERRUPT 244

#define O_ECHO		1		/* Manage ECHO, RFC 857 */
#define O_GO_AHEAD	3		/* Disable GO AHEAD, RFC 858 */

static void telnet_cmd(int sock, unsigned char op, unsigned char param) {
	unsigned char cmd[3];

	cmd[0] = T_IAC;
	cmd[1] = op;
	cmd[2] = param;
	write(sock, cmd, 3);
}

	/* Skip management session */
static void ignore_telnet_options(int msg[2]) {
	unsigned char ch, op_type, param;
	int sock = msg[0];

	read(sock, &ch, 1);
	while ((ch & (1 << 7)) && (ch != T_IAC)) {
		read(sock, &ch, 1);
	}

	while (1) {
		if (ch == T_IAC) {
			read(sock, &op_type, 1);

			if (op_type == T_WILL || op_type == T_DO ||
			    op_type == T_WONT || op_type == T_DONT) {
				read(sock, &param, 1);
			}

			if (op_type == T_WILL) {
				if (param == O_GO_AHEAD) {
					telnet_cmd(sock, T_DO, param);
				} else {
					telnet_cmd(sock, T_DONT, param);
				}
			} else if (op_type == T_DO) {
				if ((param == O_GO_AHEAD) || (param == O_ECHO)) {
					telnet_cmd(sock, T_WILL, param);
				} else {
					telnet_cmd(sock, T_WONT, param);
				}
			} else {
				/* Currently do nothing, probably it's an answer for our request */
			}
		} else {
			/* Get this symbol to shell, it belongs to usual traffic */
			write(msg[1], &ch, 1);
			return;
		}

		/* We use here nonblock socket */
		if (read(sock, &ch, 1) <= 0) {
			return;
		}
	}
}

static int utmp_login(short ut_type, const char *host) {
	struct utmp utmp;
	struct timeval tv;

	utmp.ut_type = ut_type;
	utmp.ut_pid = getpid();
	snprintf(utmp.ut_id, UT_IDSIZE, "/%hd", utmp.ut_pid);
	snprintf(utmp.ut_line, UT_LINESIZE, "pty/%d", utmp.ut_pid);
	strncpy(utmp.ut_host, host, UT_HOSTSIZE);
	memset(&utmp.ut_exit, 0, sizeof(struct exit_status));

	gettimeofday(&tv, NULL);

	utmp.ut_tv.tv_sec = tv.tv_sec;
	utmp.ut_tv.tv_usec = tv.tv_usec;

	if (NULL == pututline(&utmp)) {
		return errno;
	}

	return 0;

}

extern int kill(int tid, int sig);

static void *shell_hnd(void* args) {
	int ret;
	int *msg = (int*)args;

	struct sockaddr_in *addr_in = &clients[msg[2]].addr_in;

	ret = utmp_login(LOGIN_PROCESS, inet_ntoa(addr_in->sin_addr));
	if (ret != 0) {
		MD(printf("utmp_login LOGIN error: %d\n", ret));
	}

	if (-1 == close(STDIN_FILENO)) {
		MD(printf("close STDIN_FILENO error: %d\n", errno));
	}
	if (-1 == close(STDOUT_FILENO)) {
		MD(printf("close STDOUT_FILENO error: %d\n", errno));
	}

	if (-1 == dup2(msg[0], STDIN_FILENO)) {
		MD(printf("dup2 STDIN_FILENO error: %d\n", errno));
	}
	if (-1 == dup2(msg[1], STDOUT_FILENO)) {
		MD(printf("dup2 STDOUT_FILENO error: %d\n", errno));
	}

	ret = shell_run(shell_lookup("tish"));
	if (ret != 0) {
		MD(printf("shell_run error: %d\n", ret));
	}


	ret = utmp_login(DEAD_PROCESS, "");
	if (ret != 0) {
		MD(printf("utmp_login DEAD error: %d\n", ret));
	}

	return NULL;
}

#include <termios.h>
extern int pipe_pty(int pipe[2], const struct termios *tio);
static const struct termios pipetio = {
	.c_lflag = ICANON,
	.c_oflag = ONLCR,
};


#define XBUFF_LEN 128

/* Shell thread for telnet */
static void *telnet_thread_handler(void* args) {
	/* Choose tmpbuff size a half of size of pbuff to make
	 * replacement: \n\n...->\r\n\r\n... */
	unsigned char sbuff[XBUFF_LEN], pbuff[XBUFF_LEN];
	unsigned char *s = sbuff, *p = pbuff;
	int sock_data_len = 0; /* len of rest of socket data in local buffer sbuff */
	int pipe_data_len = 0; /* len of rest of pipe data in local buffer pbuff */
	int client_num = (int) args;
	int sock = clients[client_num].fd;
	int pipefd1[2], pipefd2[2], msg[3];
	int tid;
	int nfds;
	fd_set readfds, writefds;
	struct timeval timeout;
	int ret;

	MD(printf("starting telnet_thread_handler\n"));
	/* Set socket to be nonblock. See ignore_telnet_options() */
	fcntl(sock, F_SETFD, O_NONBLOCK);

	if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0) {
		MD(printf("new pipe error: %d\n", errno));
		goto out;
	}

	/* Send our parameters */
	telnet_cmd(sock, T_WILL, O_GO_AHEAD);
	telnet_cmd(sock, T_WILL, O_ECHO);

	ret = pipe_pty(pipefd1, NULL);
	if (ret != 0) {
		MD(printf("pipe_pty pipedf1 error: %d\n", ret));
	}
	ret = pipe_pty(pipefd2, &pipetio);
	if (ret != 0) {
		MD(printf("pipe_pty pipedf1 error: %d\n", ret));
	}

	msg[0] = sock;
	msg[1] = pipefd1[1];
	/* handle options from client */
	ignore_telnet_options(msg);

	fcntl(sock, F_SETFD, 0);

	msg[0] = pipefd1[0];
	msg[1] = pipefd2[1];
	msg[2] = client_num;
	if ((tid = new_task("telnetd user", shell_hnd, &msg)) < 0) {
		MD(printf("new task error: %d\n", -tid));
		goto out;
	}

	/* Preparations for select call */
	nfds = max(sock, pipefd2[0]);
	nfds = max(pipefd1[1], nfds) + 1;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	/* Try to read/write into/from pipes. We write raw data from socket into pipe,
	 * and than receive from it the result of command running, and send it back to
	 * client. */
	while(1) {
		int len;
		int fd_cnt;

		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(sock, &readfds);
		FD_SET(pipefd2[0], &readfds);
		if (pipe_data_len > 0) {
			FD_SET(sock, &writefds);
		}
		if (sock_data_len > 0) {
			FD_SET(pipefd1[1], &writefds);
		}

		MD(printf("."));

		fd_cnt = select(nfds, &readfds, &writefds, NULL, &timeout);

		/* XXX telnet must receive signal on socket closing, but now
		 * alternatively here is this check */
		if (!fd_cnt) {
			fcntl(sock, F_SETFD, O_NONBLOCK);
			len = read(sock, s, XBUFF_LEN);
			if ((len == 0) || ((len == -1) && (errno != EAGAIN))) {
				MD(printf("read on sock: %d %d\n", len, errno));
				goto kill_and_out;
			}
			fcntl(sock, F_SETFD, 0);

			/* preventing further execution since some fds is set,
 			 * but they are not active and will block (fd_cnt == 0)
			 */
			continue;
		}

		if ((pipe_data_len > 0) && FD_ISSET(sock, &writefds)) {
			if ((len = write(sock, p, pipe_data_len)) > 0) {
				pipe_data_len -= len;
				p += len;
			}
			else {
				MD(printf("write on sock: %d %d\n", len, errno));
			}
		} else if (FD_ISSET(pipefd2[0], &readfds)){
			struct ring pbuf_r;
			ring_init(&pbuf_r);
			p = pbuff;
			pipe_data_len = read(pipefd2[0], pbuff, XBUFF_LEN);
			if (pipe_data_len <= 0) {
				MD(printf("read on pipefd2: %d %d\n", pipe_data_len, errno));
			}
		}

		if ((sock_data_len > 0) && FD_ISSET(pipefd1[1], &writefds)) {
			if ((len = write(pipefd1[1], s, sock_data_len)) > 0) {
				sock_data_len -= len;
				s += len;
			} else {
				MD(printf("write on pipefd1: %d %d\n", len, errno));
				if (errno == EPIPE) {
					goto kill_and_out; /* this means that pipe was closed by shell */
				}
			}
		} else if (FD_ISSET(sock, &readfds)){
			s = sbuff;
			sock_data_len = read(sock, s, XBUFF_LEN);
			if (sock_data_len <= 0) {
				MD(printf("read on sock: %d %d\n", sock_data_len, errno));
			}
			if (errno == ECONNREFUSED) {
				goto kill_and_out;
			}
		}
	} /* while(1) */

kill_and_out:
	kill(tid, 9);
out:
	close(pipefd1[0]);
	close(pipefd2[1]);
	close(pipefd1[1]);
	close(pipefd2[0]);
	close(sock);
	clients[client_num].fd = -1;

	MD(printf("exiting from telnet_thread_handler\n"));

	return NULL;
}

static int exec(int argc, char **argv) {
	int res;
	int listening_descr;
	struct sockaddr_in listening_socket;

	for (res = 0; res < TELNETD_MAX_CONNECTIONS; res++) {
		clients[res].fd = -1;
	}

	listening_socket.sin_family = AF_INET;
	listening_socket.sin_port= htons(TELNETD_PORT);
	listening_socket.sin_addr.s_addr = htonl(TELNETD_ADDR);

	if ((listening_descr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("can't create socket\n");
		return -errno;
	}

	if ((res = bind(listening_descr, (struct sockaddr *)&listening_socket,
					sizeof(listening_socket))) < 0) {
		printf("bind() failed\n");
		goto listen_failed;
	}

	if ((res = listen(listening_descr, TELNETD_MAX_CONNECTIONS)) < 0) {
		printf("listen() failed\n");
		goto listen_failed;
	}

	MD(printf("telnetd is ready to accept connections\n"));
	while (1) {
		struct sockaddr_in client_socket;
		int client_socket_len = sizeof(client_socket);
		int client_descr = accept(listening_descr, (struct sockaddr *)&client_socket,
								  &client_socket_len);
		struct thread *thread;
		size_t i;

		if (client_descr < 0) {
			MD(printf("accept() failed. code=%d\n", -errno));
			continue;
		} 

		MD(printf("Attempt to connect from address %s:%d\n",
			inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port)));

		for (i = 0; i < TELNETD_MAX_CONNECTIONS; i++) {
			if (clients[i].fd == -1) {
				break;
			} 
		}

		if (i >= TELNETD_MAX_CONNECTIONS) {
			telnet_cmd(client_descr, T_INTERRUPT, 0);
			MD(printf("limit of connections exceded\n"));
			continue;
		}

		clients[i].fd = client_descr;
		memcpy(&clients[i].addr_in, &client_socket, sizeof(struct sockaddr_in));

		if (0 != pthread_create(&thread, 0, telnet_thread_handler, (void *) i)) {
			telnet_cmd(client_descr, T_INTERRUPT, 0);
			MD(printf("thread_create() returned with code=%d\n", res));
			clients[i].fd = -1;
		}
	} 

	assert(0);
	{
		/* Free resources, don't touch threads, but close socket decriptor
		 * So it'll influence to them
		 */
		for (size_t i = 0; i < TELNETD_MAX_CONNECTIONS; i++) {
			if (clients[i].fd != -1) {
				close(clients[i].fd);
			}
		}
		close(listening_descr);
	}

	return ENOERR;

listen_failed:
	res = -errno;
	close(listening_descr);
	return res;
}
