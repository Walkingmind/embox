#ifndef INCLUDE_NETPACKET_PACKET_H_
#define INCLUDE_NETPACKET_PACKET_H_

#ifndef PD_STUB
#define PD_STUB(x) ((void) 1)
#endif

#include <sys/socket.h>

#define SO_ATTACH_FILTER (SO_POSIX_MAX + 0)

#define PACKET_OUTGOING (PD_STUB("PACKET_OUTGOING"), 0)
#define PACKET_HOST 	(PD_STUB("PACKET_HOST"), 0)

#define SIOCGSTAMP 	(PD_STUB("SIOCGSTAMP"), 0)

struct sockaddr_ll {
	unsigned short sll_family;   /* Always AF_PACKET */
	unsigned short sll_protocol; /* Physical layer protocol */
	int            sll_ifindex;  /* Interface number */
	unsigned short sll_hatype;   /* ARP hardware type */
	unsigned char  sll_pkttype;  /* Packet type */
	unsigned char  sll_halen;    /* Length of address */
	unsigned char  sll_addr[8];  /* Physical layer address */
};

struct sock_filter {	/* Filter block */
	__u16	code;   /* Actual filter code */
	__u8	jt;	/* Jump true */
	__u8	jf;	/* Jump false */
	__u32	k;      /* Generic multiuse field */
};

struct sock_fprog {
	unsigned short len;
	struct sock_filter *filter;
};

#endif /* INCLUDE_NETPACKET_PACKET_H_ */
