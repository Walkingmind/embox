/**
 * @file
 *
 * @brief
 *
 * @date 01.11.2011
 * @author Anton Bondarev
 */

#ifndef PNET_GRAPH_H_
#define PNET_GRAPH_H_

#include <pnet/types.h>
#include <mem/objalloc.h>
#include <util/list.h>

enum pnet_graph_state {
	PNET_GRAPH_STOPPED,
	PNET_GRAPH_STARTED
};

struct pnet_graph {
	int id;
	enum pnet_graph_state state;
	struct list nodes;
};

extern struct pnet_graph *pnet_get_graph(int sock);

extern struct pnet_graph *pnet_graph_create(void);

extern int pnet_graph_start(struct pnet_graph *graph);
extern int pnet_graph_stop(struct pnet_graph *graph);

extern int pnet_graph_add_src(struct pnet_graph *graph, struct net_node *src);

extern int pnet_graph_add_node(struct pnet_graph *graph, struct net_node *node);

extern int pnet_node_link(struct net_node *src, struct net_node *node);

static inline int pnet_graph_run_valid(struct pnet_graph *graph) {
	return !((graph != NULL) && (graph->state == PNET_GRAPH_STARTED));
}


#endif /* PNET_GRAPH_H_ */