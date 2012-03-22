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
#include <net/port.h>
#include <net/tcp.h>

EMBOX_NET_PACK(ETH_P_IP, ip_rcv, inet_init);

/* TODO: to meet POSIX inet_proto_find should decide whether type-protocol
   combination is valid and return appropriate errno. see kernel_socket_create*/
static struct inet_protosw *inet_proto_find(short int *type, int *protocol) {
	struct inet_protosw *p_netsock = NULL;
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

		if(*type == p_netsock->type){  /* type is ok */
			type_present = true;
			if(*protocol){
				if(*protocol == p_netsock->protocol)
					return p_netsock;  /* protocol and type matched */
				else
					continue;  /* type matched but no such protocol. try next */
			}else
				if(p_netsock->deflt)
					return p_netsock;  /* only type is specified. */
		}
	}

	if(type_present)
		*protocol = -1; /* to notify about type-protocol absence */
	else
		*type = -1; /* to notify about type absence  */
	return NULL;
}

/* AF_INET socket create */
static int inet_create(struct socket *sock, int protocol) {
	int err;
	short int type = sock->type;
	struct sock *sk;
	struct inet_sock *inet;
	struct inet_protosw *p_netsock = NULL;

	if (NULL == (p_netsock = inet_proto_find(&type, &protocol))) {
		if(type < 0)
			return -EPROTOTYPE;
		else
			return -EPROTONOSUPPORT;
	}

	sk = sk_alloc(PF_INET, 0, (struct proto *) p_netsock->prot);
	if (sk == NULL) {
		return -ENOMEM;
	}

	sock->sk = sk;
	sock->ops = p_netsock->ops;
	sk->sk_type = sock->type;
	sk->sk_protocol = protocol;

	inet = inet_sk(sk);
	inet->id = 0;
	inet->uc_ttl = -1; /* TODO socket setup more options  */
	inet->mc_ttl = 1;

	if (sk->sk_prot->init != NULL) {
		if(0 != (err = sk->sk_prot->init(sk))) {
			sk_common_release(sk);
			return err;
		}
	}

	return ENOERR;
}

int inet_release(struct socket *sock) {
	struct sock *sk;
	struct inet_sock *inet;

	sk = sock->sk;
	if (sk == NULL) {
		return -EINVAL;
	}

	sock_lock(sk);
	inet = inet_sk(sk);
	socket_port_unlock(inet->sport, inet->sport_type);
	sock_unlock(sock->sk);

	if (sk->sk_prot->close != NULL) {
		/* altering close() interface to return NULL 
			 is probably not appropriate) */
		sk->sk_prot->close(sock->sk, 0);
		sock->sk = NULL;
	}

	if(sock->sk)
		sk_common_release(sock->sk);
	sock->sk = NULL;

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

	sock_lock(sk);
	if (sk->sk_prot->bind != NULL) {
		res = sk->sk_prot->bind(sk, addr, addr_len);
		if (res < 0) {
			return res;
		}
	}

	inet = inet_sk(sk);
	addr_in = (struct sockaddr_in *)addr;

	socket_set_port_type(sock);
	if (socket_port_is_busy(addr_in->sin_port, inet->sport_type)) {
		return -EBUSY;
	}
	socket_port_lock(addr_in->sin_port, inet->sport_type);
	inet->rcv_saddr = inet->saddr = addr_in->sin_addr.s_addr;
	inet->sport = addr_in->sin_port;
	inet->daddr = 0;
	inet->dport = 0;
	sock_unlock(sock->sk);

	return ENOERR;
}

int inet_dgram_connect(struct socket *sock, struct sockaddr * addr,
			int addr_len, int flags) {
	struct sock *sk;
	struct inet_sock *inet;
	sk = sock->sk;

	if(!sk->sk_prot->connect)
		return SK_NO_SUCH_METHOD;

	inet = inet_sk(sock->sk);
	inet->sport = socket_get_free_port(inet->sport_type);
	socket_set_port_type(sock);
//	socket_port_lock(inet->sport, inet->sport_type); it was locked in socket_get_free_port

	return sk->sk_prot->connect(sk, addr, addr_len);
}

int inet_sendmsg(struct kiocb *iocb, struct socket *sock,
			struct msghdr *msg, size_t size) {
	struct sock *sk;
	sk = sock->sk;

	if(!sk->sk_prot->sendmsg)
		return SK_NO_SUCH_METHOD;

	return sk->sk_prot->sendmsg(iocb, sk, msg, size);
}

//FIXME add more states handling
int inet_stream_connect(struct socket *sock, struct sockaddr * addr,
			int addr_len, int flags) {
	int err;

	if(!sock->sk->sk_prot->connect)
		return SK_NO_SUCH_METHOD;

	sock_lock(sock->sk);
	switch (sock->state) {
	default:
		err = -EINVAL;
		goto release;
	case SS_CONNECTED:
		err = -EISCONN;
		goto release;
	case SS_CONNECTING:
		err = -EALREADY;
		goto release;
	case SS_UNCONNECTED:
		err = -EISCONN;
		if (sock->sk->sk_state != TCP_CLOSE)
			goto release;
		err = sock->sk->sk_prot->connect(sock->sk, addr, addr_len);
		if (err < 0)
			goto release;
		break;
	}
	sock_unlock(sock->sk);

release:
	inet_release(sock);
	return err;
}

int inet_listen(struct socket *sock, int backlog) {
	struct sock *sk = sock->sk;

	if(!sk->sk_prot->listen)
		return SK_NO_SUCH_METHOD;

	return sk->sk_prot->listen(sk, backlog);
}

static int inet_accept(socket_t *sock, socket_t *newsock, sockaddr_t *addr, int *addr_len) {
	struct sock *sk = sock->sk;
	struct sock *newsk = newsock->sk;

	if(!sk->sk_prot->accept)
		return SK_NO_SUCH_METHOD;

	return sk->sk_prot->accept(sk, newsk, addr, addr_len);
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
