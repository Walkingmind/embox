/**
 * @file
 * @brief Implements udp socket function.
 *
 * @date 04.02.10
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <embox/net/sock.h>

#include <net/l3/ipv4/ip.h>
#include <net/l4/udp.h>
#include <net/lib/udp.h>
#include <net/sock.h>
#include <net/socket/inet_sock.h>
#include <embox/net/pack.h>

#include <util/list.h>

static const struct sock_proto_ops udp_sock_ops_struct;
const struct sock_proto_ops *const udp_sock_ops
		= &udp_sock_ops_struct;

EMBOX_NET_SOCK(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 1, 
		udp_sock_ops_struct);

static int udp_sendmsg(struct sock *sk, struct msghdr *msg, int flags) {
	int ret;
	size_t data_len, total_len, actual_len;
	struct sk_buff *skb;
	const struct sockaddr_in *to;
	const struct sockaddr *sockaddr;

	assert(sk);
	assert(sk->o_ops);
	assert(sk->o_ops->make_pack);
	assert(msg);
	assert(msg->msg_iov);
	assert(msg->msg_iov->iov_base);

	data_len = msg->msg_iov->iov_len;
	total_len = actual_len = UDP_HEADER_SIZE + data_len;
	skb = NULL;
	sockaddr = (const struct sockaddr *)msg->msg_name;

	ret = sk->o_ops->make_pack(sk, sockaddr, &actual_len, &skb);
	if (ret != 0) {
		return ret;
	}

	if (actual_len < total_len) {
		skb_free(skb);
		return -EMSGSIZE;
	}

	if (msg->msg_name != NULL) {
		to = (const struct sockaddr_in *)msg->msg_name;
	} else {
		to = (const struct sockaddr_in *)&to_inet_sock(sk)->dst_in;
	}

	assert(skb);
	assert(skb->h.uh);

	udp_build(skb->h.uh, sock_inet_get_src_port(sk), to->sin_port, total_len);

	memcpy(skb->h.uh + 1, msg->msg_iov->iov_base, data_len);

	udp4_set_check_field(skb->h.uh, skb->nh.iph);

	assert(sk->o_ops->snd_pack);
	return sk->o_ops->snd_pack(skb);
}

static LIST_DEF(udp_sock_list);

static int udp_fillmsg(struct sock *sk, struct msghdr *msg, 
		struct sk_buff *skb) {
	struct sockaddr_in *inaddr;

	inaddr = (struct sockaddr_in *)msg->msg_name;

	inaddr->sin_family = AF_INET;
	memcpy(&inaddr->sin_addr, &ip_hdr(skb)->saddr, sizeof(in_addr_t));
	inaddr->sin_port = udp_hdr(skb)->source;

	return 0;
}

static const struct sock_proto_ops udp_sock_ops_struct = {
	.sendmsg   = udp_sendmsg,
	.recvmsg   = sock_nonstream_recvmsg,
	.fillmsg   = udp_fillmsg,
	.sock_list = &udp_sock_list
};
