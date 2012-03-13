/**
 * @file
 * @brief Network socket 
 *
 * @date 19.10.2011
 * @author Anton Kozlov
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pnet/core.h>
#include <pnet/socket.h>
#include <embox/unit.h>
#include <mem/objalloc.h>

EMBOX_UNIT_INIT(net_socket_init);

#define NET_SOCKET_CNT 0x10

OBJALLOC_DEF(sockets, struct net_socket, NET_SOCKET_CNT);

static int rx_hnd(net_packet_t pack) {
	printf("%d: %s\n", pack->skbuf->len, (char *) pack->skbuf->data);
	return NET_HND_SUPPRESSED;
}

static int tx_hnd(net_packet_t pack) {

	return NET_HND_DFAULT;
}	


static struct pnet_proto socket_proto;

static int net_socket_init(void) {
	pnet_proto_init(&socket_proto, 0, rx_hnd, tx_hnd);
	return 0;
}

net_socket_t pnet_socket_open(net_id_t id, net_node_t parent) {
	net_socket_t sock = (net_socket_t) objalloc(&sockets);

	pnet_node_attach(&sock->node, id, parent);

	sock->node.proto = &socket_proto;

	return sock;
}

int pnet_socket_send(net_socket_t node, void *data, int len) {
	net_packet_t pack = pnet_pack_alloc((net_node_t) node, PNET_PACK_DIRECTION_TX, data, len);

	return pnet_process(pack);
}

#if 0
int pnet_core_receive(net_node_t node, void *data, int len) {
	net_packet_t pack = pnet_pack_alloc(node, PNET_PACK_DIRECTION_RX, data, len);

	return pnet_process(pack);
}
#endif
