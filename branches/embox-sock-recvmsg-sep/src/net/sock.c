/**
 * @file
 * @brief Generic socket support routines.
 *
 * @date 12.08.09
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 */
#include <poll.h>
#include <errno.h>
#include <string.h>

#include <util/math.h>

#include <embox/net/family.h>
#include <embox/net/pack.h>
#include <embox/net/sock.h>


#include <kernel/time/time.h>
#include <kernel/sched.h>

#include <hal/ipl.h>
#include <kernel/sched/sched_lock.h>
#include <fs/idesc_event.h>
#include <mem/misc/pool.h>
#include <net/sock.h>
#include <net/skbuff.h>
#include <net/socket/inet_sock.h>
#include <net/socket/inet6_sock.h>
#include <net/sock_wait.h>

extern size_t skb_read(struct sk_buff *skb, char *buff, size_t buff_sz);

//TODO this function call from stack (may be place it to other file)
void sock_rcv(struct sock *sk, struct sk_buff *skb,
		unsigned char *p_data, size_t size) {
	if ((sk == NULL) || (skb == NULL) || (p_data == NULL)) {
		return; /* error: invalid argument */
	}

	if (sk->shutdown_flag & (SHUT_RD + 1)) {
		skb_free(skb);
		return; /* error: socket is down */
	}

	skb->p_data = p_data;
	skb->p_data_end = p_data + size;

	skb_queue_push(&sk->rx_queue, skb);
	sk->rx_data_len += size;

	sock_notify(sk, POLLIN);
}

int sock_close(struct sock *sk) {
	if (sk == NULL) {
		return -EINVAL;
	}

	assert(sk->f_ops != NULL);
	if (sk->f_ops->close == NULL) {
		sock_release(sk);
		return 0;
	}

	return sk->f_ops->close(sk);
}

static unsigned long sock_calc_timeout(struct sock *sk) {
	unsigned long timeout = timeval_to_ms(&sk->opt.so_rcvtimeo);
	if (timeout == 0) {
		timeout = SCHED_TIMEOUT_INFINITE;
	}
	return timeout;
}

static struct sk_buff *sock_get_skb(struct sock *sk, unsigned long timeout, int *err_p) {
	struct sk_buff *skb;
	int err;

	sched_lock();
	{
		while (1) {
			skb = skb_queue_front(&sk->rx_queue);
			if (skb) {
				break;
			}

			if (!timeout) {
				err = 0;
				break;
			}

			err = sock_wait(sk, POLLIN | POLLERR, timeout);
			if (err) {
				break;
			}

		};
	}
	sched_unlock();

	if (err_p) {
		*err_p = err;
	}

	return skb;
}

int sock_dgram_recvmsg(struct sock *sk, struct msghdr *msg, int flags) {
	const unsigned long timeout = sock_calc_timeout(sk);
	struct sk_buff *skb;
	int err, nrecv;

	assert(sk != NULL);

	skb = sock_get_skb(sk, timeout, &err);

	if (!skb) {
		assert(err);
		return err;
	}

	nrecv = skb_iovec_buf(msg->msg_iov, msg->msg_iovlen, 
			skb->p_data, skb->p_data_end - skb->p_data);

	sk->rx_data_len -= skb->p_data_end - skb->p_data;

	assert(sk->p_ops != NULL);
	if (sk->p_ops->fillmsg && msg->msg_name) {
		sk->p_ops->fillmsg(sk, msg, skb);
	}

	skb_free(skb);

#if 0 //XXX
	return nrecv;
#else
	msg->msg_iov->iov_len = nrecv;
	return 0;
#endif
}

int sock_stream_recvmsg(struct sock *sk, struct msghdr *msg, int flags) {
	unsigned long timeout = sock_calc_timeout(sk);
	size_t buff_sz, total_len, len;
	struct sk_buff *skb;
	char *buff;

	assert(msg->msg_iovlen == 1);

	buff = msg->msg_iov->iov_base;
	buff_sz = msg->msg_iov->iov_len;

	total_len = 0;
	while (buff_sz != 0) {
		int err;

		skb = sock_get_skb(sk, timeout, &err);
		if (!skb) {
			if (err) {
				return err;
			}
			/* ToDo I think this check must be placed before this do-while loop
			 * and properly analyze either TCP connection was closed in usual way or forcibly.
			 * See "RETURN VALUE" http://pubs.opengroup.org/onlinepubs/009695399/functions/recvfrom.html
			 * --Alexander */
			if (0 != (err = sock_err(sk))) {
				return -err;
			}
			break;
		}

		len = skb_read(skb, buff, buff_sz);
		buff += len;
		buff_sz -= len;
		total_len += len;

		if (skb->p_data == skb->p_data_end) {
			skb_free(skb);
		}

		timeout = 0;
	}

	sk->rx_data_len -= total_len;

#if 0 //XXX
	return total_len;
#else
	msg->msg_iov->iov_len = total_len;
	return 0;
#endif
}

in_port_t sock_inet_get_src_port(const struct sock *sk) {
	assert(sk);
	assert((sk->opt.so_domain == AF_INET) || (sk->opt.so_domain == AF_INET6));

	if (sk->opt.so_domain == AF_INET) {
		return to_const_inet_sock(sk)->src_in.sin_port;
	}

	return to_const_inet6_sock(sk)->src_in6.sin6_port;
}

in_port_t sock_inet_get_dst_port(const struct sock *sk) {
	assert(sk != NULL);
	assert((sk->opt.so_domain == AF_INET)
			|| (sk->opt.so_domain == AF_INET6));

	if (sk->opt.so_domain == AF_INET) {
		return to_const_inet_sock(sk)->dst_in.sin_port;
	}

	return to_const_inet6_sock(sk)->dst_in6.sin6_port;
}
