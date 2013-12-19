/**
 * @file
 * @brief The User Datagram Protocol (UDP).
 * @details RFC 768
 *
 * @date 26.03.09
 * @author Nikolay Korotky
 */

#include <string.h>
#include <net/inetdevice.h>
#include <net/udp.h>
#include <net/ip.h>
#include <net/icmp.h>
#include <net/socket.h>
#include <net/checksum.h>
#include <net/protocol.h>
#include <net/inet_common.h>
#include <embox/net/proto.h>

#include <embox/net/sock.h>

EMBOX_NET_PROTO(IPPROTO_UDP, udp_rcv, udp_err);

EMBOX_NET_SOCK(SOCK_DGRAM, IPPROTO_UDP, udp_prot, inet_dgram_ops, 0, NULL);

static udp_sock_t *udp_hash[CONFIG_MAX_KERNEL_SOCKETS];

static int rebuild_udp_header(sk_buff_t *skb, __be16 source,
					__be16 dest, size_t len) {
	udphdr_t *udph = skb->h.uh;
	udph->source = source;
	udph->dest = dest;
	udph->len = htons(len + UDP_HEADER_SIZE);
	udph->check = 0;
	//udph->check = ptclbsum((void *) udph, udph->len);
	return 0;
}

int udp_sendmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len) {
	struct inet_sock *inet = inet_sk(sk);
	sk_buff_t *skb = alloc_skb(ETH_HEADER_SIZE + IP_MIN_HEADER_SIZE +
				    /*inet->opt->optlen +*/ UDP_HEADER_SIZE +
				    msg->msg_iov->iov_len, 0);
	skb->nh.raw = (unsigned char *) skb->data + ETH_HEADER_SIZE;
	skb->h.raw = (unsigned char *) skb->nh.raw + IP_MIN_HEADER_SIZE; // + inet->opt->optlen;
	skb->sk = sk;
	memcpy((void*)((unsigned int)(skb->h.raw + UDP_HEADER_SIZE)),
				(void *) msg->msg_iov->iov_base, msg->msg_iov->iov_len);
	/* Fill UDP header */
	rebuild_udp_header(skb, inet->sport, inet->dport, len);
	return ip_send_packet(inet, skb);
}

int udp_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len, int noblock, int flags, int *addr_len) {
	struct sk_buff *skb;
	skb = skb_recv_datagram(sk, flags, 0, 0);
	if (skb && skb->len > 0) {
		if (len > (ntohs(skb->h.uh->len) - UDP_HEADER_SIZE)) {
			len = ntohs(skb->h.uh->len) - UDP_HEADER_SIZE;
		}
		memcpy((void *) msg->msg_iov->iov_base,
				(void *) (skb->h.raw + UDP_HEADER_SIZE), len);
		kfree_skb(skb);
	} else {
		len = 0;
	}
	msg->msg_iov->iov_len = len;
	return len;
}
#if 1
static void udp_lib_hash(struct sock *sk) {
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		if (udp_hash[i] == NULL) {
			udp_hash[i] = (udp_sock_t *) sk;
			break;
		}
	}
}

static void udp_lib_unhash(struct sock *sk) {
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		if (udp_hash[i] == (udp_sock_t *) sk) {
			udp_hash[i] = NULL;
			break;
		}
	}
}
#endif
static struct sock *udp_lookup(in_addr_t daddr, __be16 dport) {
	struct inet_sock *inet;
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		inet = inet_sk((struct sock*) udp_hash[i]);
		if (inet) {
			if ((inet->rcv_saddr == INADDR_ANY || inet->rcv_saddr == daddr) &&
					inet->sport == dport) {
				return (struct sock*) inet;
			}
		}
	}
	return NULL;
}

static int udp_queue_rcv_skb(struct sock *sk, struct sk_buff *skb) {
	sock_queue_rcv_skb(sk, skb);
	return 0;
}

static int udp_rcv(sk_buff_t *skb) {
	struct sock *sk;
	struct inet_sock *inet;
	sk_buff_t *skb_tmp;

	iphdr_t *iph = ip_hdr(skb);
	udphdr_t *uh = udp_hdr(skb);
	sk = udp_lookup(iph->daddr, uh->dest);
	if (sk) {
		inet = inet_sk(sk);
		udp_queue_rcv_skb(sk, skb);
		inet->dport = uh->source;
		inet->daddr = iph->saddr;
		if (inet->rcv_saddr == INADDR_ANY) {
			//TODO: temporary
			inet->saddr = skb->nh.iph->daddr;
		}
	} else {
		skb_tmp = skb_copy(skb, 0);
		icmp_send(skb_tmp, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
	}
	return 0;
}

void udp_err(sk_buff_t *skb, uint32_t info) {
	struct inet_sock *inet;
	struct sock *sk;
	size_t i;
	__be16 port;

	for (i = 0; i < CONFIG_MAX_KERNEL_SOCKETS; i++) {
		sk = (struct sock *) udp_hash[i];
		inet = inet_sk(sk);
		port = *(__be16*)(skb->h.raw + ICMP_HEADER_SIZE + IP_HEADER_SIZE(skb->nh.iph));
		if (sk && (inet->sport == port)
			   && (inet->daddr == skb->nh.iph->saddr)) {
			sk->sk_err = info;
		}
	}
}

void *get_udp_sockets() {
	return (void*) udp_hash;
}

int udp_disconnect(struct sock *sk, int flags) {
	return 0;
}

static void udp_lib_close(struct sock *sk, long timeout) {
	sk_common_release(sk);
}

struct proto udp_prot = {
	.name              = "UDP",
	.close             = udp_lib_close,
	.sendmsg           = udp_sendmsg,
	.recvmsg           = udp_recvmsg,
	.backlog_rcv       = udp_queue_rcv_skb,
	.hash              = udp_lib_hash,
	.unhash            = udp_lib_unhash,
	.obj_size = sizeof(struct udp_sock),
};