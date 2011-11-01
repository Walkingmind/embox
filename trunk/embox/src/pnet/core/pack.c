/**
 * @file
 * @brief Network packet 
 *
 * @date 20.10.2011
 * @author Anton Kozlov
 */

#include <string.h>

#include <net/skbuff.h>
#include <pnet/core.h>

#include <mem/objalloc.h>

#include <embox/unit.h>

#define NET_PACKS_CNT 0x10

OBJALLOC_DEF(net_packs, struct net_packet, NET_PACKS_CNT);

net_packet_t pnet_pack_alloc_skb(net_node_t node, enum net_packet_dir dir, struct sk_buff *skb) {
	net_packet_t pack = objalloc(&net_packs);

	pack->node = node;
	pack->dir  = dir;

	pack->skbuf = skb;

	return pack;
}	

net_packet_t pnet_pack_alloc(net_node_t node, enum net_packet_dir dir, void *data, int len) {
	net_packet_t pack = objalloc(&net_packs);

	pack->node = node;
	pack->dir  = dir;

	pack->skbuf = alloc_skb(len, 0); 

	memcpy(pack->skbuf->data, data, len);

	return pack;
}

int pnet_pack_free(net_packet_t pack) {
	kfree_skb(pack->skbuf);

	objfree(&net_packs, pack);

	return 0;
}
