/**
 * @file
 * @brief Network node manager
 *
 * @date 19.10.2011
 * @author Anton Kozlov 
 */

#include <stddef.h>
#include <pnet/types.h>
#include <mem/objalloc.h>
#include <assert.h>

#include <util/list.h>

#ifndef CONFIG_PNET_NODES_QUANTITY
#define CONFIG_PNET_NODES_QUANTITY 0x10
#endif

OBJALLOC_DEF(net_nodes, struct net_node, CONFIG_PNET_NODES_QUANTITY);

net_node_t pnet_node_init(net_node_t node, pnet_proto_t proto) {
	assert(node);
	node->proto = proto;

	list_link_init(&node->gr_link);	

	node->rx_dfault = node->tx_dfault = NULL;
	node->graph = NULL;

	return node;
}

net_node_t pnet_node_alloc(net_addr_t addr, pnet_proto_t proto) {
	net_node_t node;
	if (NULL == proto || NULL == proto->actions.alloc) {
		node = (net_node_t) objalloc(&net_nodes);
	} else {
		node = proto->actions.alloc();
	}

	pnet_node_init(node, proto);

#if 0
	if (node->proto->init != NULL) {
		if (node->proto->init(node) != 0) {
			objfree(&net_nodes, node);
			return NULL;
		}
	}
#endif
	return node;
 
}

int pnet_node_free(net_node_t node) {
	assert(node);
	if ((NULL != node->proto) && (NULL != node->proto->actions.free)) {
		if (node->proto->actions.free(node) == 0) {
			return 0;
		}
	}
	objfree(&net_nodes, node);
	return 0;
}
