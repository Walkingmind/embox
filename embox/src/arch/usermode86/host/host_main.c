/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    12.12.2013
 */

#include "host_defs.h"
#include <assert.h>
#include <unistd.h>
#include <termios.h>

HOST_FNX(int, write, 
		CONCAT(int fd, const void *buf, int c), 
		fd, buf, c)
HOST_FNX(int, getchar, void)
HOST_FNX(int, pause, void)

int host_putchar(int c) {
	char ch = c;
	return host_write(STDOUT_FILENO, &ch, 1);
}

static HOST_FNX(int, tcgetattr, 
		CONCAT(int fd, struct termios *tio),
		fd, tio)
static HOST_FNX(int, tcsetattr, 
		CONCAT(int fd, int opt_act, const struct termios *tio),
		fd, opt_act, tio)

static void host_set_input_mode(int fd) {
	struct termios tio;
	int res;

	res = host_tcgetattr(fd, &tio);
	assert(res == 0);
	tio.c_lflag &= ~(ICANON | ECHO);
	res = host_tcsetattr(fd, TCSANOW, &tio);
	assert(res == 0);
}

int main(int argc, char *argv[]) {


	host_set_input_mode(STDIN_FILENO);

	kernel_start();

	return 0;
}

#include <setjmp.h>
#include <host.h>
static_assert(HOST_JMPBUF_LEN >= sizeof(jmp_buf), "HOST_JMPBUF_LEN less that sizeof(jmp_buf)");
