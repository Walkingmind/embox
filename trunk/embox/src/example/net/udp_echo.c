/**
 * @file
 * @brief UDP echo server
 *
 * @date 17.10.11
 * @author Alexander Kalmuk
 *	- Receive
 * @author Anton Kozlov
 *	- Sending back
 *
 * @see example/net/sender.c
 */

#include <net/l3/ipv4/ip.h>
#include <sys/socket.h>
#include <framework/example/self.h>
#include <kernel/printk.h>
#include <unistd.h>

EMBOX_EXAMPLE(exec);

#define LOCAL_PORT 1
#define REMOTE_PORT 31337
#define REMOTE_IP 0x0A00020f
#define RECEIVE_BUF_LEN 1024

static int exec(int argc, char **argv) {
	int sock;
	//int sock2;
	struct sockaddr_in addr;
	char buf[RECEIVE_BUF_LEN];
	int bytes_read;
	socklen_t sklen = 14;

	/* Create UDP socket for getting IP packets
	 * AF_INET - protocol type (IP in this case)
	 * SOCK_DGRAM - socket type (UDP in this case)
	 * @return On success, a file descriptor for the new socket is returned.*/
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	//sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	/* check if file descriptor is positive*/
	if (sock < 0) {
		printk("%s", "can't create socket!");
		return sock;
	}

	/* form address socket assign to*/
	addr.sin_family = AF_INET;
	addr.sin_port= htons(LOCAL_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* assigns the address specified to by addr to the socket referred to
	 * by the file descriptor sock. You can bind only one socket on port of concrete type */
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		printk("%s","sock can't bind!");
		return -1;
	}

	/*if(bind(sock2, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	     printk("%s","sock2 can't bind!");
	}*/

	//FIXME should go away since add struct addr in recvfrom
	addr.sin_port = htons(REMOTE_PORT);
	addr.sin_addr.s_addr = htonl((in_addr_t) REMOTE_IP);

	/* write data form socket in buffer buf. And then print buffer data */
	while (1) {
		sklen = sizeof addr;
		if ((bytes_read = recvfrom(sock, buf, RECEIVE_BUF_LEN, 0,
			 (struct sockaddr *)&addr, &sklen)) <= 0) {
			break;
		}

		sendto(sock, buf, bytes_read, 0,
			(struct sockaddr *)&addr, sklen);
		buf[bytes_read] = '\0';
		printk("%s",buf);
	}

	close(sock);

	return 0;
}
