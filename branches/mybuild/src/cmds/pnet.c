 /**
 * @file
 * @brief Util for pnet configuration
 *
 * @date 14.03.2012
 * @author Alexander Kalmuk
 */

#include <errno.h>
#include <err.h>
#include <embox/cmd.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <net/util.h>
#include <net/in.h>

#include <pnet/netfilter/match_lin.h>
#include <pnet/core.h>
#include <pnet/node.h>
#include <pnet/repo.h>
#include <pnet/graph.h>

EMBOX_CMD(exec);

extern struct list_head graphs_list;
extern struct pnet_module __pnet_mod_repo[];

#define MAX_WORD_LENGTH 100
#define MAX_TOKEN_COUNT 10
#define RULE_OPTION_QUANTITY 3

typedef int (*_rule_setter) (struct pnet_graph *gr, match_rule_t rule, char *rule_str);

static void print_graph(struct pnet_graph *gr);
static void print_list_of_graph_nodes(struct pnet_graph *gr);
static void print_graph_names(void);
static void print_rules(net_node_matcher_t node);

static int add_node(char **argv);
static int link_node(char **argv);
static int unlink_node(char **argv);

static int rule_set_mac(struct pnet_graph *gr, match_rule_t rule, char *rule_str);
static int rule_set_ip(struct pnet_graph *gr, match_rule_t rule, char *rule_str);
static int rule_set_next_node(struct pnet_graph *gr, match_rule_t rule, char *rule_str);
static match_rule_t rule_get_by_id(net_node_t node, char id);

static int delete_brokens(char *str);

struct rule {
	char *option;
	_rule_setter setter;
};

static struct rule rule_setters[RULE_OPTION_QUANTITY] = {
		{.option = "--mac",   .setter = rule_set_mac},
		{.option = "--ip",    .setter = rule_set_ip},
		{.option = "--node",  .setter = rule_set_next_node}
};

static void print_usage(void) {
	printf("Usage: pnet [options] [keys] graph [nodes | rules]\n");
}

//TODO move from here
static int delete_brokens(char *str) {
	int len;
	char *cur;
	int overlooking_words_cnt;

	overlooking_words_cnt = 0;
	len = MAX_WORD_LENGTH;
	cur = str;
	cur++;

	while (*cur != '\'' && len) {
		if (*cur == '\0') {
			*cur = ' ';
			overlooking_words_cnt++;
		}
		cur++; len--;
	}

	*cur = '\0';

	return overlooking_words_cnt;
}

static void shift(char **argv, int begin, int shift) {
	for(int i = begin + shift; i < MAX_TOKEN_COUNT; i++) {
		argv[i - shift] = argv[i];
	}
}

static void rebuild_argv(char **argv) {
	int len = MAX_TOKEN_COUNT;
	int i = 0;

	while (NULL != argv[i] && len) {
		if (argv[i][0] == '\'') {
			argv[i]++;
			shift(argv, i + 1, delete_brokens(argv[i]));
		}
		i++;
	}
}

//FIXME now this function return only first graph in list if exist
static struct pnet_graph *get_graph_by_name(char *name) {
	struct pnet_graph *gr;

	list_for_each_entry(gr, &graphs_list, lnk) {
		if (0 == strcmp(gr->name, name))
			return gr;
	}

	return NULL;
}

static net_node_t get_node_from_graph_by_name(struct pnet_graph *gr, char *name) {
	net_node_t node;

	list_for_each_entry(node, &gr->nodes, gr_link) {
		if (!strcmp(node->proto->name, name))
			return node;
	}

	return NULL;
}

static void print_graph_names(void) {
	struct pnet_graph *gr;

	printf("%s", "Running graphs: ");
	list_for_each_entry(gr, &graphs_list, lnk) {
		if (PNET_GRAPH_STARTED == gr->state)
			printf("%s, ", gr->name);
	}
	printf("\n%s", "Stopped graphs: ");
	list_for_each_entry(gr, &graphs_list, lnk) {
		if (PNET_GRAPH_STOPPED == gr->state)
			printf("%s, ", gr->name);
	}
}

static void print_list_of_graph_nodes(struct pnet_graph *gr) {
	net_node_t node = NULL;

	if (list_empty(&gr->nodes)) {
		printf("list of nodes is empty \n");
		return;
	}
	printf("nodes of %s: ", gr->name);
	list_for_each_entry(node, &gr->nodes, gr_link) {
		printf("%s, ", node->proto->name);
	}
}

static void print_graph(struct pnet_graph *gr) {
	net_node_t node, root;

	if (list_empty(&gr->nodes)) {
		printf("list of nodes is empty \n");
		return;
	}
	root = member_cast_out((&gr->nodes)->next, struct net_node , gr_link);
	node = root->rx_dfault;

	printf("%s \n", root->proto->name);
	while (NULL != node) {
		printf("%s\n", node->proto->name);
		node = node->rx_dfault;
	}
}

static void print_rules(net_node_matcher_t node) {
	struct list_head *h;
	match_rule_t rule;

	list_for_each (h, &node->match_rx_rules) {
		rule = member_cast_out(h, struct match_rule, lnk);
		printf("%d \n", rule->id);
	}
}

static int add_node(char **argv) {
	struct pnet_graph *gr;
	net_node_t node;
	int graph_state;

	if (NULL == argv[3] || NULL == (gr = get_graph_by_name(argv[3]))) {
		printf("%s: no such graph\n", argv[3]);
		return -ENOENT;
	}

	if (PNET_GRAPH_STOPPED != (graph_state = gr->state)) {
		pnet_graph_stop(gr);
	}

	if (NULL == argv[4] || NULL == (node = pnet_get_module(argv[4]))) {
		printf("%s: no such node\n", argv[4]);
		return -ENOENT;
	}

	gr->state = graph_state;

	return pnet_graph_add_node(gr, node);
}

/**
 *	@param argv[2] - graph name
 *	@param argv[3] - name of source node
 *	@param argv[4] - name of node will be linked to argv[3]
 */
static int link_node(char **argv) {
	net_node_t src, node;
	struct pnet_graph *gr;
	int graph_state;
	int res;

	if (NULL == argv[2] || NULL == (gr = get_graph_by_name(argv[2]))) {
		printf("%s: no such graph\n", argv[2]);
		return -ENOENT;
	}

	if (PNET_GRAPH_STOPPED != (graph_state = gr->state)) {
		pnet_graph_stop(gr);
	}

	if (NULL == argv[3] || NULL == (src = get_node_from_graph_by_name(gr, argv[3]))) {
		printf("%s: no such node in graph %s\n", argv[3], argv[2]);
		return -ENOENT;
	}

	if (NULL == argv[4] || NULL == (node = get_node_from_graph_by_name(gr, argv[4]))) {
		printf("%s: no such node in graph %s\n", argv[4], argv[2]);
		return -ENOENT;
	}

	res = pnet_node_link(src, node);
	gr->state = graph_state;

	return res;
}

static int unlink_node(char **argv) {
	struct pnet_graph *gr;
	net_node_t node;
	int graph_state;

	if (NULL == argv[3] || NULL == (gr = get_graph_by_name(argv[3]))) {
		printf("%s: no such graph\n", argv[3]);
		return -ENOENT;
	}

	if (PNET_GRAPH_STOPPED != (graph_state = gr->state)) {
		pnet_graph_stop(gr);
	}

	if (NULL == argv[4] || NULL == (node = get_node_from_graph_by_name(gr, argv[4]))) {
		printf("%s: no such node in graph %s\n", argv[4], argv[3]);
		return -ENOENT;
	}
	/* if node->graph == NULL it means that node is not in any graph */
	node->graph = NULL;
	node->rx_dfault = NULL;

	/* delete node from graph */
	list_del(&node->gr_link);

	gr->state = graph_state;

	return ENOERR;
}

static int rule_alloc(struct pnet_graph *gr, net_node_matcher_t node){
	match_rule_t rule;

	if (NULL == (rule = pnet_rule_alloc())) {
		return -ENOMEM;
	}

	pnet_add_new_rx_rule(rule, node);

	return ENOERR;
}

static int rule_set_mac(struct pnet_graph *gr, match_rule_t rule, char *rule_elem) {
	if (NULL == macaddr_scan((unsigned char *) rule_elem, rule->skbuf->mac.ethh->h_source)) {
		return -ENOENT;
	}
	return ENOERR;
}

static int rule_set_ip(struct pnet_graph *gr, match_rule_t rule, char *rule_elem) {
	if (NULL == ipaddr_scan((unsigned char *) rule_elem, (unsigned char *) &rule->skbuf->nh.iph->saddr)) {
		return -ENOENT;
	}
	return ENOERR;
}

static int rule_set_next_node (struct pnet_graph *gr, match_rule_t rule, char *rule_elem) {
	net_node_t node;

	if (NULL == (node = get_node_from_graph_by_name(gr, rule_elem)))
		return -ENOENT;

	pnet_rule_set_next_node(rule, node);
	return ENOERR;
}

static match_rule_t rule_get_by_id(net_node_t node, char id) {
	struct list_head *h;
	match_rule_t rule;
	net_node_matcher_t matcher;
	int n;

	sscanf(&id, "%d", &n);

	matcher = (net_node_matcher_t) node;
	list_for_each (h, &matcher->match_rx_rules) {
		rule = member_cast_out(h, struct match_rule, lnk);
		if (rule->id == n)
			return rule;
	}

	return NULL;
}

static _rule_setter get_setter_by_option(char *option) {
	for(int i = 0; i < RULE_OPTION_QUANTITY; i++) {
		if (!strcmp(rule_setters[i].option, option))
			return rule_setters[i].setter;
	}

	return NULL;
}

static int exec(int argc, char **argv) {
	int opt, res;
	struct pnet_graph *gr;
	const struct pnet_module *mod;
	match_rule_t rule;
	net_node_t node;
	_rule_setter setter;

	getopt_init();

	while (-1 != (opt = getopt(argc, argv, "hgnt:d:p:r:s:a:l:"))) {
		rebuild_argv(argv);

		switch(opt) {
		case 'h':
			print_usage();
			break;
		case 'g':
			print_graph_names();
			break;
		case 'p':
			if (!strcmp("--nodes", argv[2])) {
				if (NULL != (gr = get_graph_by_name(argv[3]))) {
					print_list_of_graph_nodes(gr);
				}
				else {
					printf("%s: no such graph\n", argv[3]);
					return 0;
				}
			} else if (!strcmp("--rules", argv[2])) {
				if (NULL == (gr = get_graph_by_name(argv[3]))) {
					printf("%s: no such graph\n", argv[3]);
					return 0;
				}

				if (NULL == (node = get_node_from_graph_by_name(gr, argv[4]))) {
					printf("%s: no such node in graph %s\n", argv[4], argv[3]);
					return 0;
				}

				print_rules((net_node_matcher_t) node);
			} else if (NULL != (gr = get_graph_by_name(argv[2]))) {
				print_graph(gr);
			} else {
				printf("%s: no such graph\n", argv[2]);
				return 0;
			}
			break;
		case 'n' :
			printf("nodes: ");
			array_foreach_ptr(mod, __pnet_mod_repo, ARRAY_SPREAD_SIZE(__pnet_mod_repo)) {
				if (mod->node)
					printf("%s, ", mod->node->proto->name);
			}
			printf("\nprotocols: ");
			array_foreach_ptr(mod, __pnet_mod_repo, ARRAY_SPREAD_SIZE(__pnet_mod_repo)) {
				if (!mod->node)
					printf("%s, ", mod->proto->name);
			}
			break;
		case 'r':
			if (NULL != (gr = get_graph_by_name(argv[2]))) {
				pnet_graph_start(gr);
				printf("%s run \n", gr->name);
			} else {
				printf("%s: no such graph\n", argv[2]);
				return 0;
			}
			break;
		case 's':
			if (NULL != (gr = get_graph_by_name(argv[2]))) {
				pnet_graph_stop(gr);
				printf("%s stopped \n", gr->name);
			} else {
				printf("%s: no such graph\n", argv[2]);
				return 0;
			}
			break;
		case 'a' :
			if (!strcmp("--node", argv[2])) {
				if ((res = add_node(argv)) < 0) {
					if (res == -EBUSY) {
						gr = get_graph_by_name(argv[3]);
						node = pnet_get_module(argv[4]);
						printf("node '%s' in use already in graph '%s' \n", argv[4], node->graph->name);
						return 0;
					}
					return -1;
				}
			} else if (!strcmp("--graph", argv[2])) {
				if (NULL == pnet_graph_create(argv[3])) {
					printf("%s: graph was not created\n", argv[3]);
					return -1;
				}
			} else if (!strcmp("--rule", argv[2])) {
				if (NULL == (gr = get_graph_by_name(argv[3]))) {
					printf("%s: no such graph\n", argv[3]);
					return 0;
				}
				if (NULL == (node = get_node_from_graph_by_name(gr, argv[4]))) {
					printf("%s: no such node in graph %s\n", argv[4], argv[3]);
					return 0;
				}

				if (rule_alloc(gr, (net_node_matcher_t) node) < 0) {
					printf("rule was not created\n");
					return -1;
				}
			} else {
				printf("%s: no such option \n", argv[2]);
			}
			break;
		case 't':
			if (NULL == (gr = get_graph_by_name(argv[2]))) {
				printf("%s: no such graph\n", argv[2]);
				return 0;
			}

			if (NULL == (node = get_node_from_graph_by_name(gr, argv[3]))) {
				printf("%s: no such node in graph %s\n", argv[3], argv[2]);
				return 0;
			}

			if (NULL == (rule = rule_get_by_id(node, *argv[4]))) {
				printf("%s: no such rule in node %s\n", argv[4], argv[3]);
				return 0;
			}

			if (NULL != (setter = get_setter_by_option(argv[5]))) {
				if (setter(gr, rule, argv[6]) < 0) {
					printf("%s: incorrect value\n", argv[6]);
					return 0;
				}
			} else {
				printf("%s: no such option \n", argv[5]);
			}
			break;
		case 'l':
			if (link_node(argv) < 0)
				return -1;
			break;
		case 'd' :
			if (!strcmp("--node", argv[2])) {
				if (unlink_node(argv) < 0)
					return -1;
			}
			break;
		default:
			return 0;
		}
	}

	return 0;
}
