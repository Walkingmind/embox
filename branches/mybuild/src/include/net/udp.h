/**
 * @file
 * @brief Definitions for the UDP module.
 *
 * @date 26.03.09
 * @author Nikolay Korotky
 */

#ifndef UDP_H_
#define UDP_H_

#include <net/inet_sock.h>

struct sock;

extern struct proto udp_prot;

extern const struct proto_ops inet_dgram_ops;

typedef struct udphdr {
	__be16 source;
	__be16 dest;
	__be16 len;
	__be16 check;
} __attribute__((packed)) udphdr_t;

#define UDP_HEADER_SIZE	(sizeof(udphdr_t))

static inline udphdr_t *udp_hdr(const sk_buff_t *skb) {
	return (udphdr_t *) skb->h.raw;
}

typedef struct udp_sock {
	/* inet_sock has to be the first member */
	struct inet_sock inet;
	int              pending;
	unsigned int     corkflag;
	__be16           len;
} udp_sock_t;

static inline udp_sock_t *udp_sk(const struct sock *sk) {
	return (udp_sock_t *) sk;
}

/* net/ipv4/udp.c */

extern int udp_init(void);
extern void udp_err(sk_buff_t *skb, uint32_t info);
extern int udp_sendmsg(struct kiocb *iocb, struct sock *sk,
			struct msghdr *msg, size_t len);
extern int udp_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len, int noblock, int flags, int *addr_len);
/*extern void udp_err(sk_buff_t *, uint32_t);*/

extern int udp_disconnect(struct sock *sk, int flags);
extern void *get_udp_sockets(void);

#endif /* UDP_H_ */
