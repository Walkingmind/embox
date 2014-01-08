/**
 * @file
 * @brief Rlogin client
 * @date 10.09.2012
 * @author Alexander Kalmuk
 */

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <embox/cmd.h>
#include <stdio.h>

#include <termios.h>

EMBOX_CMD(exec);

#define RLOGIN_ADDR INADDR_ANY

/* rlogin port */
#define RLOGIN_PORT 513

/* control bytes */
#define R_DISCARD_All 0x02
#define R_RAW         0x10
#define R_RESUME      0x20
#define R_WINDOW_SZ   0x80

/* start, stop output on local terminal */
#define R_START       0x11
#define R_STOP        0x13

/* client mode */
#define MODE_COOKED   0
#define MODE_RAW      R_RAW

/* FIXME cheat for now */
static const char *client = "embox";
static const char *term = "dumb/38000";

static void print_usage(void) {
	printf("Usage: rlogin [-l username] <server> \n");
}

	/* Allow to turn off/on extra debugging information */
#if 0
#	define RLOGIN_DEBUG(x) do {\
		x;\
	} while (0);
#else
#	define RLOGIN_DEBUG(x) do{\
	} while (0);
#endif

/**
 * @brief handle code if it is control byte
 * @return result if @c code is control byte
 * @retval -1 if not
 * @retval 0 if it is
 */
static int handle_cntl_byte(unsigned char code, int *state, int *mode) {
	switch (code) {
	case R_DISCARD_All:
		*state = R_STOP;
		break;
	case R_RAW:
		*mode = MODE_RAW;
		break;
	case R_RESUME:
		if (*mode == MODE_RAW) {
			*state = R_START;
			*mode = MODE_COOKED;
			break;
		}
		return -EINVAL;
	case R_WINDOW_SZ:
		break;
	case R_START:
		if (*mode != MODE_RAW) {
			*state = R_START;
			break;
		}
		return -EINVAL;
	case R_STOP:
		if (*mode != MODE_RAW) {
			*state = R_STOP;
		} else {
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int rlogin_handle(int sock) {
	int sock_data_len = 0, stdin_data_len = 0;
	unsigned char c;
	unsigned char buf[128];
	unsigned char *s = buf;
	int state = R_START, mode = MODE_COOKED;
	int stdin_flags = fcntl(STDIN_FILENO, F_GETFL);
	struct termios tios;
	int c_lflags;
	int err = 0;

	tcgetattr(STDIN_FILENO, &tios);
	c_lflags = tios.c_lflag;
	tios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &tios);

	fcntl(STDIN_FILENO, F_SETFD, stdin_flags | O_NONBLOCK);
	fcntl(sock, F_SETFD, O_NONBLOCK);

	while (1) {
		if (stdin_data_len > 0) {
			if (write(sock, &c, 1) == 1) {
				stdin_data_len -= 1;
			}
		} else {
			stdin_data_len = read(STDIN_FILENO, &c, 1);
			/* XXX NVT terminal requires '\r' as enter */
			if ( c == '\n') {
				c = '\r';
			}
		}

		if (sock_data_len > 0) {
			/* Try to handle each byte of server data. */
			do {
				if (!handle_cntl_byte(*s, &state, &mode) || state == R_STOP
						|| (write(STDOUT_FILENO, s, 1) == 1)) {
					sock_data_len -= 1;
					s += 1;
				}
			} while (sock_data_len > 0);
		} else {
			s = buf;
			sock_data_len = read(sock, s, 128);

			if (!sock_data_len) {
				err = 0;
				goto reset_out;
			}

			if (sock_data_len == -1) {
				err = -errno;
				if (err != -EAGAIN && err != -EWOULDBLOCK) {
					goto reset_out;
				}

			}
		}
	} /* while (1) */

reset_out:

	fcntl(STDIN_FILENO, F_SETFD, stdin_flags);
	tios.c_lflag = c_lflags;
	tcsetattr(STDIN_FILENO, TCSANOW, &tios);

	return err;
}

static int exec(int argc, char **argv) {
	static int tries = 0;
	int res = -1, sock, opt;
	struct sockaddr_in our, dst;
	int len;
	char *buf;
	char *server = (char*)client;

	if (argc < 2) {
		print_usage();
		return 0;
	}

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "hl:"))) {
		switch (opt) {
		case 'h':
			print_usage();
			return 0;
		case 'l':
			server = optarg;
			break;
		default:
			printf("error: unsupported option %c\n", optopt);
			return -EINVAL;
		}
	}

	if (!inet_aton(argv[argc -1], &dst.sin_addr)) {
		printf("Invalid ip address %s\n", argv[argc -1]);
		return -EINVAL;
	}
	dst.sin_family = AF_INET;
	dst.sin_port = htons(RLOGIN_PORT);

	len = strlen(client) + strlen(server) + strlen(term) + 3;
	buf = malloc(len);
	if (buf == NULL) {
		return -ENOMEM;
	}
	memset(buf, 0, len);

	our.sin_family = AF_INET;
	our.sin_port= htons(RLOGIN_PORT + tries++);
	our.sin_addr.s_addr = htonl(RLOGIN_ADDR);

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("can not allocate socket\n");
		return -errno;
	}

	if ((res = bind(sock, (struct sockaddr *)&our, sizeof(our))) < 0) {
		printf("can not bind socket\n");
		goto exit;
	}

	if (connect(sock, (struct sockaddr *)&dst, sizeof dst) < 0) {
		printf("Error... Cant connect to remote address %s:%d\n",
				inet_ntoa(dst.sin_addr), RLOGIN_PORT);
		res = -errno;
		goto exit;
	}
	RLOGIN_DEBUG(printf("connected\n"));

	/* send Handshake */
	if (write(sock, buf, 1) < 0) {
		res = -errno;
		goto exit;
	}

	len = 0;
	memcpy(buf, client, strlen(client));
	len += strlen(client) + 1;

	memcpy(buf + len, server, strlen(server));
	len += strlen(server) + 1;

	memcpy(buf + len, term, strlen(term));
	len += strlen(term) + 1;
	/* send user info */
	if (write(sock, buf, len) < 0) {
		res = -errno;
		goto exit;
	}

	res = rlogin_handle(sock);

exit:
	free(buf);
	close(sock);
	return res;
}