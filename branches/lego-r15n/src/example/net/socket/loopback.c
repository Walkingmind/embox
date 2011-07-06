/**
 * @file
 * @brief Example demonstrate the work of sockets and loopback interface
 *
 * @date 29.03.11
 * @author Dmitry Zubarevich
 */

#include <stdio.h>
#include <embox/test.h>
#include <net/ip.h>
#include <net/socket.h>

EMBOX_TEST(run);

static int run(void) {
	char msg_send[] = "Test_message\n";
	int sock;
	ssize_t msg_size = sizeof(msg_send);
	socklen_t addr_size;
	char msg_recv[msg_size];
	struct sockaddr_in addr;

	/* creation of socket */
	if (0 > (sock = socket(AF_INET, SOCK_DGRAM, 0))) {
		TRACE("Can't create socket");
		return 0;
	}

	/* define of addres */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr_size = sizeof(addr);

	/* transmiting of test message */
	if (0 > (sendto(sock, msg_send, msg_size, 0, (struct sockaddr *) &addr, addr_size))) {
		TRACE("Can't send message");
		return 0;
	}

	/* receiving of test message */
	if (0 > (recvfrom(sock, &msg_recv ,msg_size, 0,
			(struct sokaddr *) &addr, addr_size))) {
		TRACE("Can't recive message");
		return 0;
	} else {
		TRACE("It was recived message: %s", msg_recv);
	}

	/* close of socket */
	if (0 > close(sock)) {
		TRACE("It was bad close of socket");
		return 0;
	}

	return 0;
}
