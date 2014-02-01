/**
 * @file
 *
 * @date Nov 7, 2013
 * @author: Anton Bondarev
 */

#include <net/sock.h>
#include <util/list.h>
#include <hal/ipl.h>


struct sock * sock_iter(const struct sock_proto_ops *p_ops) {
	if (p_ops == NULL) {
		return NULL; /* error: invalid argument */
	}

	return list_first_element(p_ops->sock_list, struct sock, lnk);
}

struct sock * sock_next(const struct sock *sk) {
	if (sk == NULL) {
		return NULL; /* error: invalid argument */
	}
	else if (list_alone_element(sk, lnk)) {
		return NULL; /* error: not hashed */
	}

	assert(sk->p_ops != NULL);

	return list_next_element(sk, sk->p_ops->sock_list,
			struct sock, lnk);
}

struct sock * sock_lookup(const struct sock *sk,
		const struct sock_proto_ops *p_ops,
		sock_lookup_tester_ft tester,
		const struct sk_buff *skb) {
	ipl_t ipl;
	struct sock *next_sk;

	if ((p_ops == NULL) || (tester == NULL)) {
		return NULL; /* error: invalid arguments */
	}

	next_sk = sk != NULL ? sock_next(sk) : sock_iter(p_ops);

	ipl = ipl_save();
	{
		while (next_sk != NULL) {
			if (tester(next_sk, skb)) {
				ipl_restore(ipl);
				return next_sk;
			}
			next_sk = sock_next(next_sk);
		}
	}
	ipl_restore(ipl);

	return NULL; /* error: no such entity */
}
