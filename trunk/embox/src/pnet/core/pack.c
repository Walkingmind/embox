/**
 * @file
 * @brief Network packet 
 *
 * @date 20.10.2011
 * @author Anton Kozlov
 */

#include <pnet/core.h>

#include <mem/objalloc.h>

#include <embox/unit.h>

#define NET_PACKS_CNT 0x10

OBJALLOC_DEF(net_packs, struct net_packet, NET_PACKS_CNT);

net_packet_t pnet_pack_alloc(net_node_t node, enum net_packet_dir dir, void *data, int len) {
	net_packet_t pack = objalloc(&net_packs);

	pack->node = node;
	pack->data = data;
	pack->len  = len;
	pack->dir  = dir;

	return pack;
}

int pnet_pack_free(net_packet_t pack) {
	objfree(&net_packs, pack);
	return 0;
}
