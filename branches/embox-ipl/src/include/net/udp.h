/**
 * @file
 * @brief Definitions for the UDP module.
 *
 * @date 26.03.09
 * @author Nikolay Korotky
 */

#ifndef NET_UDP_H_
#define NET_UDP_H_

#include <net/inet_sock.h>

#include <framework/mod/options.h>
#include <module/embox/net/udp_sock.h>

#define MODOPS_AMOUNT_UDP_SOCK OPTION_MODULE_GET(embox__net__udp_sock, NUMBER, amount_udp_sock)

struct sock;

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
#if 0
extern int udp_sendmsg(struct kiocb *iocb, struct sock *sk,
			struct msghdr *msg, size_t len);
extern int udp_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len, int noblock, int flags);
/*extern void udp_err(sk_buff_t *, uint32_t);*/
extern int udp_disconnect(struct sock *sk, int flags);
#endif

extern void *get_udp_sockets(void);

extern struct udp_sock *udp_table[MODOPS_AMOUNT_UDP_SOCK];
extern const struct proto udp_prot;

#endif /* NET_UDP_H_ */
