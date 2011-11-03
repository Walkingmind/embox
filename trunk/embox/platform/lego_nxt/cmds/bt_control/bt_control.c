/**
 * @file
 *
 * @brief
 *
 * @date 31.10.2011
 * @author Anton Bondarev
 */

#include <types.h>
#include <embox/cmd.h>

#include <net/socket.h>
#include <pnet/repo.h>
#include <pnet/types.h>
#include <pnet/graph.h>

EMBOX_CMD(bt_main);

static int control_handle(net_packet_t pack) {
	return 0;
}

static struct pnet_proto control_proto = {
	.rx_hnd = control_handle
};
static struct net_node pnet_control = {
	.proto = &control_proto
};

static int bt_main(int argc, char **argv) {
	struct pnet_graph *graph ;
	struct net_node *node, *src;

	graph = pnet_graph_create();

	src = pnet_get_module("lego_blue_core");
	
	pnet_graph_add_src(graph, src);

	node = pnet_get_module("lego_direct");

	pnet_graph_add_node(graph, node);

	pnet_node_link(src, node);

	pnet_node_link(node, (struct net_node *)&pnet_control);

	pnet_graph_start(graph);

	return 0;
}
