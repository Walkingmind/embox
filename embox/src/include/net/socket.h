/**
 * @file
 *
 * @date 19.03.09
 * @author Anton Bondarev
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 */

#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <net/skbuff.h>
#include <stddef.h>
#include <types.h>

/* Supported address families. */
#define N_FAMILIES_SUPPORTED 4
enum supported_address_families{
	AF_UNSPEC =  0,
	AF_UNIX = 1,  /* Unix domain sockets */
	AF_INET = 2,  /* Internet IP Protocol */
	AF_PACKET = 17  /* Packet family */
};
/* socket types are somewhy defined in net.h */

#define AF_LOCAL AF_UNIX /* POSIX name for AF_UNIX */
/* this should be removed. the link is socket_repo.c and so on */
#define AF_MAX AF_PACKET /* valid only if AF_PACKET is last on list */

/* Protocol families, same as address families. */
#define PF_UNSPEC	AF_UNSPEC
#define PF_UNIX		AF_UNIX
#define PF_LOCAL	AF_LOCAL
#define PF_INET		AF_INET
#define PF_PACKET	AF_PACKET
//#define PF_MAX		AF_MAX

#define PNET_GRAPH   40

/* Maximum queue length specifiable by listen.  */
//#define SOMAXCONN 128

/* Flags we can use with send/ and recv.
   Added those for 1003.1g not all are supported yet
 */
#define MSG_OOB       0x0001
#define MSG_PEEK      0x0002
#define MSG_DONTROUTE 0x0004
#define MSG_TRYHARD   0x0004 /* Synonym for MSG_DONTROUTE for DECnet */
#define MSG_CTRUNC    0x0008
#define MSG_PROBE     0x0010 /* Do not send. Only probe path f.e. for MTU */
#define MSG_TRUNC     0x0020
#define MSG_DONTWAIT  0x0040 /* Nonblocking io */
#define MSG_EOR       0x0080 /* End of record */
#define MSG_WAITALL   0x0100 /* Wait for a full request */
#define MSG_FIN       0x0200
#define MSG_SYN       0x0400
#define MSG_CONFIRM   0x0800 /* Confirm path validity */
#define MSG_RST       0x1000
#define MSG_ERRQUEUE  0x2000 /* Fetch message from error queue */
#define MSG_NOSIGNAL  0x4000 /* Do not generate SIGPIPE */
#define MSG_MORE      0x8000 /* Sender will send more */

#define MSG_EOF       MSG_FIN

#if defined(CONFIG_COMPAT)
#define MSG_CMSG_COMPAT	0x80000000 /* This message needs 32 bit fixups */
#else
#define MSG_CMSG_COMPAT	0x00000000 /* We never have 32 bit fixups */
#endif


/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
#define SOL_IP      0
//#define SOL_ICMP    1   /* No-no-no! Due to Linux :-) we cannot use SOL_ICMP=1 */
//#define SOL_TCP     6
#define SOL_UDP     17
//#define SOL_IPV6    41
//#define SOL_ICMPV6  58
//#define SOL_SCTP    132
//#define SOL_UDPLITE 136 /* UDP-Lite (RFC 3828) */
#define SOL_RAW     255
//#define SOL_IPX     256
//#define SOL_AX25    257
//#define SOL_ATALK   258
//#define SOL_NETROM  259
//#define SOL_ROSE    260
//#define SOL_DECNET  261
//#define SOL_X25     262
//#define SOL_PACKET  263
//#define SOL_ATM     264 /* ATM layer (cell level) */
//#define SOL_AAL     265 /* ATM Adaption Layer (packet level) */
//#define SOL_IRDA    266
//#define SOL_NETBEUI 267
//#define SOL_LLC     268
//#define SOL_DCCP    269
//#define SOL_NETLINK 270
//#define SOL_TIPC    271

/* IPX options */
#define IPX_TYPE    1

struct iovec {
	void *iov_base;
	size_t iov_len;
};

struct msghdr {
	void *msg_name;       /* Socket name */
	int msg_namelen;      /* Length of name */
	struct iovec *msg_iov; /* Data blocks */
#if 0
	__kernel_size_t msg_iovlen;	/* Number of blocks		*/
#endif
	void *msg_control;    /* Per protocol magic (eg BSD file descriptor passing) */
#if 0
	__kernel_size_t	msg_controllen;	/* Length of cmsg list */
#endif
	unsigned int msg_flags;
};

typedef unsigned short sa_family_t;

/* abstract socket address structure(as i understand //ttimkk) */
typedef struct sockaddr {
	sa_family_t sa_family; /* Address family, AF_xxx */
	char sa_data[14];      /* 14 bytes of protocol address */
} sockaddr_t;

/**< Internet address. With underline it's in network representation */
struct in_addr {
	uint32_t    s_addr;
};

struct __in_addr {
	uint32_t    s_addr;
};

/* With underline it's in network representation */
typedef uint32_t in_addr_t;
typedef uint32_t __in_addr_t;

/* more specific address structure
	 (to recast on sockaddr_t in AF_INET sockets) */
typedef struct sockaddr_in {
	unsigned short   sin_family;   /* e.g. AF_INET */
	unsigned short   sin_port;     /* e.g. htons(3490) */
	struct in_addr   sin_addr;     /* see struct in_addr, above */
	char             sin_zero[8];  /* zero this if you want to */
} sockaddr_in_t;


/**
 * create an endpoint for communication.
 * @param protocol The protocol specifies a particular protocol to be used with the socket.
 * 	Normally only a single protocol exists to support a particular socket type within a
 * 	given protocol family, in which case protocol can be specified as 0.
 * @return On success, a file descriptor for the new socket is returned.
 * 	On error, result < 0.
 */
extern int socket(int domain, int type, int protocol);

/**
 * setup of connection
 * @param sockfd socket description, was created by socket()
 * @param daddr destination address
 * @param daddrlen size of daddr
 * @return error code
 */
extern int connect(int sockfd, const struct sockaddr *daddr, socklen_t daddrlen);

/**
 * bind a address to a socket.
 * @param sockfd socket description
 * @param addr local address
 * @param addrlen size of addr
 * @return 0 on success. On error, result < 0.
 */
extern int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * mark socket as accepting connections 
 * @param sockfd socket description
 * @param backlog limit of outstanding connections in sock queue 
 * @return 0 on success. On error, result < 0.
 */
extern int listen(int sockfd, int backlog); 

/**
 * peek first connection request from queue and return fd of socket associated to
 * connected stream
 * @param sockfd socket description
 * @param addr NULL or pointer of sockaddr struct where addres of connected socket
 * will be returened
 * @param addrlen length of addr struct
 * @return fd on success. On error, result < 0.
 */
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
 * send a message on a socket.
 * @param sockfd socket description
 * @param buf pointer on data
 * @param len length of buf
 * @param flags
 * @param daddr destination address
 * @param daddrlen size of daddr
 * @return the number of characters sent. On error, result < 0.
 */
extern ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
		const struct sockaddr *daddr, socklen_t daddrlen);

/**
 * receive a message from a socket.
 * @param sockfd socket description
 * @param buf buffer
 * @param len size of buffer
 * @param flags
 * @param daddr destination address
 * @param daddrlen size of daddr
 * @return the number of bytes received, or result < 0 if an error occurred.
 */
extern ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
		struct sockaddr *daddr, socklen_t *daddrlen);

#if 0
/**
 * check message in a socket
 * @param sockfd socket description
 * @return 1 if there isn't a message in socket, 0 otherwise or result < 0 if an error occurred.
 */
extern int empty_socket(int sockfd);
#endif

/**
 * close a socket descriptor
 * @param sockfd socket description
 * @return 0 on success. On error, result < 0.
 */
extern int socket_close(int sockfd);
extern int close(int sockfd);

//TODO not implement now
extern int socket_shutdown(int socket, int how);

//FIXME move below from here
extern struct socket * socket_alloc(void);
extern void socket_free(struct socket *sock);
extern int check_icmp_err(int sockfd);
#if 0 
extern size_t sendto_sock(struct socket *sock, const void *buf, size_t len, int flags,
		const struct sockaddr *daddr, socklen_t daddrlen);

extern ssize_t recvfrom_sock(struct socket *sock, void *buf, size_t len, int flags,
			struct sockaddr *daddr, socklen_t *daddrlen);
#endif
#endif /* NET_SOCKET_H_ */
