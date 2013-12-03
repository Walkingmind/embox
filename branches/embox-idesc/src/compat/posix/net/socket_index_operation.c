/*
 * @file
 * @brief
 *
 * @date 26.06.13
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <stddef.h>
#include <errno.h>

#include <net/socket/ksocket.h>

#include <sys/socket.h>
#include <poll.h>


static ssize_t socket_read(struct idesc *desc, void *buff,
		size_t size) {
	int ret;
	struct msghdr msg;
	struct iovec iov;
	struct sock *sk = (struct sock *)desc;

	assert(desc != NULL);

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;

	iov.iov_base = buff;
	iov.iov_len = size;

	ret = krecvmsg(sk, &msg, desc->idesc_flags);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return iov.iov_len;
}

static ssize_t socket_write(struct idesc *desc, const void *buff,
		size_t size) {
	int ret;
	struct msghdr msg;
	struct iovec iov;
	struct sock *sk = (struct sock *)desc;

	assert(desc != NULL);

#if 0
	if (sk->shutdown_flag & (SHUT_WR + 1))
		return SET_ERRNO(EPIPE);
#endif

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;

	iov.iov_base = (void *)buff;
	iov.iov_len = size;

	ret = ksendmsg(sk, &msg, desc->idesc_flags);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return iov.iov_len;
}

static int socket_close(struct idesc *desc) {
	int ret;
	struct sock *sk = (struct sock *)desc;

	assert(desc != NULL);

	ret = ksocket_close(sk);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

static int socket_status(struct idesc *desc, int status_nr) {
	struct sock *sk = (struct sock *)desc;

	assert(sk != NULL);

	if (!status_nr)
		return 0;

	switch (status_nr) {
	case POLLIN:
		return sk->rx_data_len;
	case POLLOUT:
		return INT_MAX; // XXX it is so?
	case POLLERR:
		return 0; /* TODO */
	default:
		/* UNREACHABLE */
		assert(0);
	}

	return 0;
}

const struct idesc_ops task_idx_ops_socket = {
	.read = socket_read,
	.write = socket_write,
	.close = socket_close,
	.status = socket_status
};

