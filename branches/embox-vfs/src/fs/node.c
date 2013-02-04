/**
 * @file
 * @brief pool of nodes
 *
 * @date 06.10.10
 * @author Nikolay Korotky
 * @author Eldar Abusalimov
 */


#include <string.h>
#include <embox/unit.h>

#include <fs/node.h>

#include <mem/misc/pool.h>

#define MAX_NODE_QUANTITY OPTION_GET(NUMBER,fnode_quantity)

struct node_tuple {
	struct node node;
	struct nas nas;
	struct node_fi fi;
};

POOL_DEF(node_pool, struct node_tuple, MAX_NODE_QUANTITY);

EMBOX_UNIT_INIT(node_init);

static int node_init(void) {
	return 0;
}

node_t *node_alloc(const char *name) {
	struct node_tuple *nt;

	struct node *node;
	struct nas *nas;

	nt = pool_alloc(&node_pool);
	if(!nt) {
		return NULL;
	}

	node = &nt->node;
	nas = &nt->nas;

	node->nas = nas;
	nas->node = node;

	nas->fi = &nt->fi;

	tree_link_init(&node->tree_link);
	strcpy((char *) node->name, name);

	return node;
}

void node_free(node_t *node) {
	pool_free(&node_pool, member_cast_out(node, struct node_tuple, node));
}
