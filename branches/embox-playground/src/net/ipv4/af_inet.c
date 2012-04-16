/**
 * @file
 * @brief PF_INET protocol family socket handler.
 *
 * @date 01.12.09
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 */

#include <errno.h>
#include <embox/net/pack.h>
#include <framework/net/sock/api.h>
#include <stddef.h>
#include <linux/aio.h>
#include <net/protocol.h>
#include <net/in.h>
#include <net/sock.h>
#include <net/socket.h>
#include <net/inet_sock.h>
#include <net/tcp.h>
#include <net/inetdevice.h>

EMBOX_NET_PACK(ETH_P_IP, ip_rcv, inet_init);

static struct inet_protosw * inet_proto_find(short int *type, int *protocol) {
	struct inet_protosw *p_netsock;
	const struct net_sock *net_sock_ptr;
	int net_proto_family;

 /* to determine whether family-type combination is valid */
	bool type_present = false;

	net_sock_foreach(net_sock_ptr) {
		p_netsock = net_sock_ptr->netsock;
		net_proto_family = net_sock_ptr->net_proto_family;
		if (net_proto_family != AF_UNSPEC && net_proto_family != AF_INET) {
			continue;
		}
		if (*type == p_netsock->type){  /* type is ok */
			type_present = true;
			if (*protocol) {
				if(*protocol == p_netsock->protocol) {
					return p_netsock;  /* protocol and type matched */
				}
				else {
					continue;  /* type matched but no such protocol. try next */
				}
			}
			else if (p_netsock->deflt) {
					return p_netsock;  /* only type is specified. */
			}
		}
	}

	if (type_present) {
		*protocol = -1; /* to notify about type-protocol absence */
	}
	else {
		*type = -1; /* to notify about type absence  */
	}
	return NULL;
}

/* AF_INET socket create */
struct sock * inet_create_sock(gfp_t priority, struct proto *prot,
		int protocol, int type) {
	struct sock *sk;

	sk = sk_alloc(PF_INET, 0, prot);
	if(sk != NULL){
		sk->sk_type = type;
		sk->sk_protocol = protocol;	
	}
	return sk;
}

static int inet_create(struct socket *sock, int protocol) {
	int err;
	short int type = sock->type;
	struct sock *sk;
	struct inet_sock *inet;
	struct inet_protosw *p_netsock;

	p_netsock = inet_proto_find(&type, &protocol);
	if (p_netsock == NULL) {
		if (type < 0) {
			return -EPROTOTYPE;
		}
		else {
			return -EPROTONOSUPPORT;
		}
	}

	sk = inet_create_sock(0, (struct proto *)p_netsock->prot, protocol, type);
	if (sk == NULL) {
		return -ENOMEM;
	}

	sock->sk = sk;
	sock->ops = p_netsock->ops;

	inet = inet_sk(sk);
	inet->id = 0;
	inet->uc_ttl = -1; /* TODO socket setup more options  */
	inet->mc_ttl = 1;
	/* setup port */
	/* socket_set_port_type(sock); */
	/* inet->sport = htons(socket_get_free_port(inet->sport_type)); /\* inet->sport at network bytes order  */

	if (sk->sk_prot->init != NULL) {
		err = sk->sk_prot->init(sk);
		if (err < 0) {
			sk_common_release(sk);
			return err;
		}
	}

	return ENOERR;
}

int inet_release(struct socket *sock) {
	struct sock *sk;
	/* struct inet_sock *inet; */

	sk = sock->sk;
	if (sk == NULL) {
		return -EINVAL;
	}

	sock_lock(sk);

	/* inet = inet_sk(sk); */
	/* socket_port_unlock(ntohs(inet->sport), inet->sport_type); */

	if (sk->sk_prot->close != NULL) {
		/* altering close() interface to return NULL 
			 is probably not appropriate) */
		sk->sk_prot->close(sock->sk, 0);
	}
	else {
		sk_common_release(sock->sk);
	}
	sock->sk = NULL;
	sock_unlock(sk);

	return ENOERR;
}


/**
 * predicate to compare two internet address structures
 **/
bool inet_address_compare(struct sockaddr *addr1, struct sockaddr *addr2){
        sockaddr_in_t *addr_in1, *addr_in2;
        addr_in1 = (sockaddr_in_t *)addr1;
        addr_in2 = (sockaddr_in_t *)addr2;

        if((addr_in1->sin_family == addr_in2->sin_family) &&
                 (addr_in1->sin_addr.s_addr == addr_in2->sin_addr.s_addr) &&
                 (addr_in1->sin_port == addr_in2->sin_port))
                return true;
        else
                return false;
}

int inet_bind(struct socket *sock, struct sockaddr *addr, int addr_len) {
	int res;
	struct sock *sk;
	struct sockaddr_in *addr_in;
	struct inet_sock *inet;

	sk = sock->sk;

	addr_in = (struct sockaddr_in *)addr;
	/* check if there is such an ip thought our local inet devices */
		/* check broadcast and multicast, is that correct? */
		/* svv: It depends. Some sockets might work with broadcast/multicast
		 * packets, some doesn't. IMHO, there is no reason for tcp to use
		 * not unicast addresses
		 */
	if (!ip_is_local(addr_in->sin_addr.s_addr, true, true)) {
		return -EADDRNOTAVAIL;
	}

	res = ENOERR;
	sock_lock(sk);
	if (sk->sk_prot->bind != NULL) {
		res = sk->sk_prot->bind(sk, addr, addr_len);
		if (res < 0) {
			goto unlock;
		}
	}

	inet = inet_sk(sk);
	/* if (socket_port_is_busy(ntohs(addr_in->sin_port), inet->sport_type)) { */
	/* 	res = -EBUSY; */
	/* 	goto unlock; */
	/* } */
	/* else { */
	/* 	socket_port_unlock(ntohs(inet->sport), inet->sport_type); */
	/* } */
	/* socket_port_lock(ntohs(addr_in->sin_port), inet->sport_type); // reserve new port */
	inet->rcv_saddr = addr_in->sin_addr.s_addr;
	inet->sport = addr_in->sin_port;
	inet->daddr = 0;
	inet->dport = 0;

unlock:
	sock_unlock(sock->sk);
	return res;
}

int inet_dgram_connect(struct socket *sock, struct sockaddr * addr,
			int addr_len, int flags) {
	struct sock *sk;

	sk = sock->sk;
	if (sk->sk_prot->connect != NULL) {
		return sk->sk_prot->connect(sk, addr, addr_len);
	}
	return ENOERR;	
}

int inet_sendmsg(struct kiocb *iocb, struct socket *sock,
			struct msghdr *msg, size_t size) {
	struct sock *sk;

	sk = sock->sk;
	if (sk->sk_prot->sendmsg == NULL) {
		return SK_NO_SUCH_METHOD;
	}

	return sk->sk_prot->sendmsg(iocb, sk, msg, size);
}

//FIXME add more states handling
int inet_stream_connect(struct socket *sock, struct sockaddr * addr,
			int addr_len, int flags) {
	int err;

	if (sock->sk->sk_prot->connect == NULL) {
		return SK_NO_SUCH_METHOD;
	}

	sock_lock(sock->sk);
	switch (sock->state) {
	default:
		err = -EINVAL;
		break;
	case SS_CONNECTED:
		err = -EISCONN;
		break;
	case SS_CONNECTING:
		err = -EALREADY;
		break;
	case SS_UNCONNECTED:
		err = sock->sk->sk_prot->connect(sock->sk, addr, addr_len);
		break;
	}
	sock_unlock(sock->sk);

//release:
//	inet_release(sock);
	return err;
}

int inet_listen(struct socket *sock, int backlog) {
	struct sock *sk;

	sk = sock->sk;
	if (sk->sk_prot->listen == NULL) {
		return SK_NO_SUCH_METHOD;
	}

	return sk->sk_prot->listen(sk, backlog);
}

static int inet_accept(socket_t *sock, socket_t *newsock, sockaddr_t *addr, int *addr_len) {
	struct sock *sk;

	sk = sock->sk;
	if (sk->sk_prot->accept == NULL) {
		return SK_NO_SUCH_METHOD;
	}

	return sk->sk_prot->accept(sk, newsock->sk, addr, addr_len);
}

/* uses for create socket */
struct net_proto_family inet_family_ops = {
	.family = PF_INET,
	.create = inet_create,
};

const struct proto_ops inet_dgram_ops = {
	.family            = PF_INET,
	.release           = inet_release,
	.bind              = inet_bind,
	.connect           = inet_dgram_connect,
	.sendmsg           = inet_sendmsg,
	.recvmsg           = sock_common_recvmsg,
	.compare_addresses = inet_address_compare,
};

const struct proto_ops inet_stream_ops = {
	.family            = PF_INET,
	.release           = inet_release,
	.bind              = inet_bind,
	.connect           = inet_stream_connect,
	.accept            = inet_accept,
	.listen            = inet_listen,
	.sendmsg           = inet_sendmsg,
	.recvmsg           = sock_common_recvmsg,
	.compare_addresses = inet_address_compare,
};

static int inet_init(void) {
	return sock_register(&inet_family_ops);
}
