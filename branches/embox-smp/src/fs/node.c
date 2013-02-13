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

node_t *node_alloc(const char *name, size_t name_len) {
	struct node_tuple *nt;

	struct node *node;
	struct nas *nas;

	if (!name_len) {
		name_len = strlen(name);
	}

	if (!*name || name_len > MAX_LENGTH_FILE_NAME) {
		/* TODO behave more clever here? -- Eldar */
		return NULL;
	}

	nt = pool_alloc(&node_pool);
	if (!nt) {
		return NULL;
	}

	node = &nt->node;
	nas = &nt->nas;

	node->nas = nas;
	nas->node = node;

	nas->fi = &nt->fi;

	tree_link_init(&node->tree_link);

	strncpy((char *) node->name, name, name_len);
	node->name[name_len] = '\0';

	return node;
}

void node_free(node_t *node) {
	pool_free(&node_pool, member_cast_out(node, struct node_tuple, node));
}
