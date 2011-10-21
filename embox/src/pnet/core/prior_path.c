/**
 * @file
 *
 * @brief
 *
 * @date 20.10.2011
 * @author Anton Bondarev
 */

#include <errno.h>
#include <pnet/core.h>
#include <pnet/prior_path.h>

//static struct pnet_path prior_table[0x10]; //TODO convert it to list or heap

int path_set_prior(net_node_t node, net_prior_t prior) { //now handles only prior increment
	net_node_t cur_node = node;
	while (cur_node != NULL) {
		if (cur_node->prior >= prior) {
			break;
		}
		cur_node->prior = prior;
		cur_node = cur_node->parent;
	}
	return 0;
}

static int __net_core_receive(net_packet_t pack) {
	net_node_t node = pack->node;
	net_id_t res = NET_HND_DFAULT;

	if (node->proto->rx_hnd != NULL) {
		res = node->proto->rx_hnd(pack);
	}
	
	if (res == NET_HND_DFAULT) {
		pack->node = pack->node->dfault;
	} else if (res > 0 ){
		pack->node = pack->node->children[res];
	}

	if (res != NET_HND_SUPPRESSED) {
		pnet_process(pack);
	}
	
	return 0;
}

static int __net_core_send(net_packet_t pack) {
	net_node_t node = pack->node;
	int res = NET_HND_DFAULT;

	if (node->proto->tx_hnd != NULL) {
		res = node->proto->tx_hnd(pack);
	}
	
	if (res == NET_HND_DFAULT) {
		pack->node = pack->node->parent;
		pnet_process(pack);
	}
	
	return ENOERR; 
}

int pnet_process(net_packet_t pack) {
	if (pack->dir == NET_PACKET_RX) {
		return __net_core_receive(pack);
	} 
	return __net_core_send(pack);
}

struct pnet_path *pnet_get_dev_prior(struct net_device *dev){
	return NULL;
}

int pnet_path_add(char prior, struct pnet_path *path) {

	return 0;

}
