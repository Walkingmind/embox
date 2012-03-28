/**
 * @file
 * @brief Definitions for the AF_INET socket handler.
 *
 * @date 17.03.09
 * @author Anton Bondarev
 */

#ifndef NET_SOCK_H_
#define NET_SOCK_H_

#include <net/netdevice.h>
#include <kernel/thread/sync/mutex.h>
#include <net/net.h>
#include <mem/misc/slab.h>

typedef struct {
	spinlock_t slock;
} socket_lock_t;

/**
 * Minimal network layer representation of sockets.
 * @param skc_family network address family
 * @param skc_state Connection state
 * @param skc_reuse %SO_REUSEADDR setting
 * @param skc_bound_dev_if bound device index if != 0
 */
struct sock_common {
	unsigned short skc_family;
	volatile unsigned char skc_state;
	unsigned char skc_reuse;
	int skc_bound_dev_if;
	struct proto *skc_prot;
};

enum socket_connection_state_t {UNCONNECTED, CLOSED, LISTENING, BOUND, CONNECTING, CONNECTED, ESTABLISHED, DISCONNECTING};

/**
 * Network layer representation of sockets.
 * @param __sk_common shared layout with inet_timewait_sock
 * @param sk_protocol which protocol this socket belongs in this network family
 * @param sk_type socket type
 * @param sk_rcvbuf size of receive buffer in bytes
 * @param sk_lock synchronizer
 * @param sk_sndbuf size of send buffer in bytes
 * @param sk_flags %SO_LINGER (l_onoff), %SO_BROADCAST, %SO_KEEPALIVE,
 *			%SO_OOBINLINE settings, %SO_TIMESTAMPING settings
 * @param sk_receive_queue incoming packets
 * @param sk_write_queue Packet sending queue
 * @param sk_socket Identd and reporting IO signals
 * @param sk_state_change: callback to indicate change in the state of the sock
 * @param sk_data_ready: callback to indicate there is data to be processed
 * @param sk_write_space: callback to indicate there is bf sending space available
 * @param sk_error_report: callback to indicate errors (e.g. %MSG_ERRQUEUE)
 * @param sk_backlog_rcv: callback to process the backlog
 * @param sk_destruct: called at sock freeing time, i.e. when all refcnt == 0
 * @param get_port TODO add description
 * @param arp_queue_info: arp_queue related parameter
 * @param sk_connection_state: state of the socket (i.e. UNCONNECTED, CONNECTED...). enumerated type
 * @param sock_is_ready: event for waking up socket when the packet is added to arp_queue
 */
typedef struct sock {
	struct sock_common __sk_common;
#define sk_family  __sk_common.skc_family
#define sk_prot    __sk_common.skc_prot
#define sk_state   __sk_common.skc_state
	unsigned char sk_protocol;
	unsigned short sk_type;
	int sk_rcvbuf;
	socket_lock_t sk_lock;
	struct {
		struct sk_buff *head;
		struct sk_buff *tail;
	} sk_backlog;
	int sk_sndbuf;
	unsigned long sk_flags;

	struct sk_buff_head *sk_receive_queue;
	struct sk_buff_head *sk_write_queue;

	struct socket *sk_socket;
	void *sk_user_data;

	void (* sk_state_change)(struct sock *sk);
	void (* sk_data_ready)(struct sock *sk, int bytes);
	void (* sk_write_space)(struct sock *sk);
	void (* sk_error_report)(struct sock *sk);
	int (* sk_backlog_rcv)(struct sock *sk, sk_buff_t *pack);
	void (* sk_destruct)(struct sock *sk);
	int (* get_port)(struct sock *sk, unsigned short num);
	int32_t sk_err;
	bool ready;
	enum socket_connection_state_t socket_connection_state;
	struct event sock_is_ready;
} sock_t;

static inline void sock_set_ready(struct sock *sk) {
	sk->ready = true;
}
static inline void sock_unset_ready(struct sock *sk){
	sk->ready = false;
}

/**
 *	Check if socket is wait for fate of pending packs resolution.
 *	@return
 *         - true if socket is ready for further actions
 *         - false in other case
 */
static inline bool sock_is_ready(struct sock *sk) {
	return sk->ready;
}

/** Sock flags */
enum sock_flags {
	SOCK_DEAD,
	SOCK_DONE,
	SOCK_DESTROY,
	SOCK_BROADCAST
};

/** Protocol specific functions */
typedef struct proto {
	void (*close)(sock_t *sk, long timeout);
	int (*connect)(sock_t *sk, sockaddr_t *addr, int addr_len);
	int (*disconnect)(sock_t *sk, int flags);
	int (*listen)(sock_t *sk, int backlog);
	int (*accept)(sock_t *sk, sock_t *newsk, sockaddr_t *addr, int *addr_len);
	int (*ioctl)(struct sock *sk, int cmd, unsigned long arg);
	int (*init)(sock_t *sk);
	void (*destroy)(struct sock *sk);
	int (*setsockopt)(struct sock *sk, int level, int optname, char *optval,
			int optlen);
	int (*getsockopt)(struct sock *sk, int level, int optname, char *optval,
			int *option);
	int (*sendmsg)(struct kiocb *iocb, sock_t *sk, struct msghdr *msg,
			size_t len);
	int (*recvmsg)(struct kiocb *iocb, sock_t *sk, struct msghdr *msg,
			size_t len, int noblock, int flags, int *addr_len);
	int (*bind)(sock_t *sk, sockaddr_t *uaddr, int addr_len);
	int (*backlog_rcv)(sock_t *sk, sk_buff_t *skb);
	void (*hash)(struct sock *sk);
	void (*unhash)(struct sock *sk);
	sock_t *(*sock_alloc)(void); /**< if not NULL, allocate proto socket casted to sock_t */
	void (*sock_free)(sock_t *); /**< must not be NULL if sock_alloc is not NULL */ 
	unsigned int obj_size;
	cache_t *cachep;             /**< associated cache in which socks will be stored */
	char name[32];
} proto_t;

/** Initializes structure sock's pull */
extern void sk_init(void);

/** Allocates structure sock with specific parameters
 * @family - Protocol family (PF_INIT for example)
 * @priority -not use now
 * @prot - pointer to the proto structure
 */
extern sock_t *sk_alloc(/*struct net *net,*/int family, gfp_t priority,
		proto_t *prot);

/**
 * Returns specified structure sock into pull,
 * assuming there are no more handle on it.
 */
extern void sk_free(sock_t *sk);

/** This function used by all transports to attempt to queue received packets*/
extern int sock_queue_rcv_skb(sock_t *sk, sk_buff_t *skb);

/**
 * Functions to fill in entries in struct proto_ops when a protocol
 * does not implement a particular function.
 */
extern int sock_no_listen(struct socket *, int);
extern int sock_no_accept(struct socket *, struct socket *, int);

extern int sock_common_recvmsg(struct kiocb *iocb, struct socket *sock,
			struct msghdr *msg, size_t size, int flags);

extern void sk_common_release(struct sock *sk);

/* Simple spinlock */
extern void sock_lock(struct sock *sk);
extern void sock_unlock(struct sock *sk);


/* extern void sk_set_connection_state(struct sock *sk, enum socket_connection_state_t state); */
/* extern enum socket_connection_state_t sk_get_connection_state(struct sock *sk); */
/* extern int sk_is_connected(struct sock *sk); */
/* extern int sk_is_bound(struct sock *sk); */
/* extern int sk_is_listening(struct sock *sk); */
static inline void sk_set_connection_state(struct sock *sk, enum socket_connection_state_t state){
	sk->socket_connection_state = state;
}

static inline enum socket_connection_state_t sk_get_connection_state(struct sock *sk){
	return sk->socket_connection_state;
}

static inline int sk_is_connected(struct sock *sk){
	return (sk->socket_connection_state == CONNECTED);
}

static inline int sk_is_bound(struct sock *sk){
	return (sk->socket_connection_state == BOUND);
}

static inline int sk_is_listening(struct sock *sk){
	return (sk->socket_connection_state == LISTENING);
}


enum sk_errno_t {SK_NOERR = 0, SK_ERR = 400, SK_NO_SUCH_METHOD = 401};

#endif /* NET_SOCK_H_ */
