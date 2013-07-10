/**
 * @file
 * @brief An implementation of the SOCKET network access protocol.
 *
 * @date 19.03.09
 * @author Anton Bondarev
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 */

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <sys/uio.h>

#include <net/socket/ksocket.h>
#include <net/socket/socket.h>
#include <net/sock.h>
#include <sys/socket.h>
#include <util/array.h>
#include <kernel/task.h>
#include <kernel/task/idx.h>
#include <net/l3/arp_queue.h>

#include <kernel/thread.h>
#include <kernel/event.h>
#include <kernel/task/io_sync.h>
#include <net/socket/socket_registry.h>

extern const struct task_idx_ops task_idx_ops_socket;

static inline struct socket * idx2socket(int idx) {
	struct idx_desc *desc = task_self_idx_get(idx);
	return desc != NULL ? task_idx_desc_data(desc) : NULL;
}

static inline int idx2flags(int idx) {
	struct idx_desc *desc = task_self_idx_get(idx);
	return desc != NULL ? *task_idx_desc_flags_ptr(desc) : 0;
}

int socket(int domain, int type, int protocol) {
	int ret, sockfd;
	struct socket *sock;

	ret = ksocket(domain, type, protocol, &sock);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	sockfd = task_self_idx_alloc(&task_idx_ops_socket, sock);
	if (sockfd < 0) {
		ksocket_close(sock);
		SET_ERRNO(EMFILE);
		return -1;
	}

	assert(sock != NULL);
	assert(sock->sk != NULL);
	sock->sk->ios = &task_idx_indata(task_self_idx_get(sockfd))->ios;

	if (type != SOCK_STREAM) {
		io_sync_enable(sock->sk->ios, IO_SYNC_WRITING); /* TODO move to ksocket */
	}

	return sockfd;
}

int bind(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kbind(sock, addr, addrlen);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int connect(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kconnect(sock, addr, addrlen, idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int listen(int sockfd, int backlog) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = klisten(sock, backlog);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	int ret, new_sockfd;
	struct socket *sock, *new_sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kaccept(sock, addr, addrlen, idx2flags(sockfd), &new_sock);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	new_sockfd = task_self_idx_alloc(&task_idx_ops_socket, new_sock);
	if (new_sockfd < 0) {
		ksocket_close(new_sock);
		SET_ERRNO(EMFILE);
		return -1;
	}

	assert(new_sock != NULL);
	assert(new_sock->sk != NULL);
	new_sock->sk->ios = &task_idx_indata(task_self_idx_get(new_sockfd))->ios;

	/* TODO move to kaccept */
	io_sync_enable(new_sock->sk->ios, IO_SYNC_WRITING);
	if (NULL != skb_queue_front(&new_sock->sk->rx_queue)) {
		io_sync_enable(new_sock->sk->ios, IO_SYNC_READING);
	}

	return new_sockfd;
}

int sendmsg_sock(struct socket *sock, struct msghdr *msg, int flags) {
	int ret;

	if (sock == NULL) {
		return -EBADF;
	}

	ret = ksendmsg(sock, msg, flags);
	if (ret != 0) {
		return ret;
	}

	return 0;
}

ssize_t send(int sockfd, const void *buff, size_t size,
		int flags) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = flags;

	iov.iov_base = (void *)buff;
	iov.iov_len = size;

	ret = sendmsg_sock(idx2socket(sockfd), &msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return iov.iov_len;
}

ssize_t sendto(int sockfd, const void *buff, size_t size,
		int flags, const struct sockaddr *addr,
		socklen_t addrlen) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = (void *)addr;
	msg.msg_namelen = addrlen;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = flags;

	iov.iov_base = (void *)buff;
	iov.iov_len = size;

	ret = sendmsg_sock(idx2socket(sockfd), &msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return iov.iov_len;
}

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags) {
	int ret;
	struct msghdr _msg;

	memcpy(&_msg, msg, sizeof _msg);
	_msg.msg_flags = flags;

	ret = sendmsg_sock(idx2socket(sockfd), &_msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return _msg.msg_iov->iov_len;
}

int recvmsg_sock(struct socket *sock, struct msghdr *msg, int flags) {
	int ret;

	if (sock == NULL) {
		return -EBADF;
	}

	ret = krecvmsg(sock, msg, flags);
	if (ret != 0) {
		return ret;
	}

	return 0;
}

ssize_t recv(int sockfd, void *buff, size_t size,
		int flags) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = flags;

	iov.iov_base = (void *)buff;
	iov.iov_len = size;

	ret = recvmsg_sock(idx2socket(sockfd), &msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return iov.iov_len;
}

ssize_t recvfrom(int sockfd, void *buff, size_t size,
		int flags, struct sockaddr *addr,
		socklen_t *addrlen) {
	int ret;
	struct msghdr msg;
	struct iovec iov;

	msg.msg_name = (void *)addr;
	msg.msg_namelen = addrlen != NULL ? *addrlen : 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = flags;

	iov.iov_base = (void *)buff;
	iov.iov_len = size;

	ret = recvmsg_sock(idx2socket(sockfd), &msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	if (addrlen != NULL) {
		*addrlen = msg.msg_namelen;
	}

	return iov.iov_len;
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
	int ret;
	struct msghdr _msg;

	memcpy(&_msg, msg, sizeof _msg);
	_msg.msg_flags = flags;

	ret = recvmsg_sock(idx2socket(sockfd), &_msg,
			idx2flags(sockfd));
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	msg->msg_name = _msg.msg_name;
	msg->msg_namelen = _msg.msg_namelen;
	msg->msg_flags = _msg.msg_flags;

	return _msg.msg_iov->iov_len;
}

int shutdown(int sockfd, int how) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kshutdown(sock, how);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int getsockname(int sockfd, struct sockaddr *addr,
		socklen_t *addrlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kgetsockname(sock, addr, addrlen);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int getpeername(int sockfd, struct sockaddr *addr,
		socklen_t *addrlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kgetpeername(sock, addr, addrlen);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int getsockopt(int sockfd, int level, int optname, void *optval,
		socklen_t *optlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = kgetsockopt(sock, level, optname, optval, optlen);
	if (ret != 0){
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}

int setsockopt(int sockfd, int level, int optname,
		const void *optval, socklen_t optlen) {
	int ret;
	struct socket *sock;

	sock = idx2socket(sockfd);
	if (sock == NULL) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = ksetsockopt(sock, level, optname, optval, optlen);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return -1;
	}

	return 0;
}
