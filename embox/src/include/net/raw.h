/**
 * @file
 * @brief Definitions for the RAW-IP module.
 *
 * @date 16.02.10
 * @author Nikolay Korotky
 */

#ifndef NET_RAW_H_
#define NET_RAW_H_

#include <net/inet_sock.h>

typedef struct raw_sock {
	/* inet_sock has to be the first member */
	struct inet_sock   inet;
#if 0
	struct icmp_filter filter;
#endif
} raw_sock_t;

static inline raw_sock_t *raw_sk(const struct sock *sk) {
	return (raw_sock_t *) sk;
}

extern const struct sock_ops *const raw_sock_ops;

extern int raw_rcv(struct sk_buff *);
extern void raw_err(sk_buff_t *skb, uint32_t info);

#endif /* NET_RAW_H_ */
