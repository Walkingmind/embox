 /**
 * @file
 * @brief
 *
 * @date 14.03.2012
 * @author Alexander Kalmuk
 */

#include <errno.h>
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

static void print_graph(struct pnet_graph *gr);
static void print_graph_node_list(struct pnet_graph *gr);
static void print_graph_names(void);

static int add_node(char *str);
static int link_node(char *str);

static int form_rule(match_rule_t rule, const char *rule_elem, struct pnet_graph *gr, int num);

static char *next_word(char *str);

static void print_usage(void) {
	printf("Usage: pnet [-h] [-p [--nodes] graph] [-g] [-n] [-r graph] [-s graph]");
	printf("[-l graph node1 node2] [(-a | -d) --node graph node] [(-a | -d)");
	printf("--rule graph [-node next_node] [-ip ip] [-proto proto]] [-m [--enable | --disable] rule \n");
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

	list_foreach(node, &gr->nodes, gr_link) {
		if(!strcmp(node->proto->name, name))
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

static void print_graph_node_list(struct pnet_graph *gr) {
	net_node_t node = NULL;

	printf("nodes of %s: ", gr->name);
	list_foreach(node, &gr->nodes, gr_link) {
		printf("%s, ", node->proto->name);
	}
}

static void print_graph(struct pnet_graph *gr) {
	net_node_t node, root;
	net_node_matcher_t matcher;
	match_rule_t rule;
	struct list_head *h;

	root = list_first_element(&gr->nodes, struct net_node, gr_link);
	node = root->rx_dfault;

	printf("%s\n", root->proto->name);
	while (NULL != node) {
		/* FIXME matcher must have special type to differ from other nodes in graph */
		if (strcmp(node->proto->name, "matcher")) {
			printf("%s\n ", node->proto->name);
		} else {
			/* if node is matcher it contain links with some other nodes */
			matcher = (net_node_matcher_t) node;
			printf("%s->", matcher->node.proto->name);

			list_for_each (h, &matcher->match_rx_rules) {
				rule = member_cast_out(h, struct match_rule, lnk);
				printf("%s, ", rule->next_node->proto->name);
			}
			printf("\n");
		}
		node = node->rx_dfault;
	}
}

static char *next_word(char *str) {
	int len = MAX_WORD_LENGTH;

	while (*str != '\0' && len)
		str++; len--;

	while (*str == '\0' && len)
		str++; len--;

	if(*str != '\'') {
		return str;
	} else {
		char *cur;
		*str++ = '\0';
		cur = str;

		while (*cur != '\'' && len) {
			if (*cur == '\0')
				*cur = ' ';
			cur++; len--;
		}

		*cur = '\0';
	}

	return str;
}

static int add_node(char *str) {
	char *name;
	struct pnet_graph *gr;
	net_node_t node;

	if(NULL == (name = str) || NULL == (gr = get_graph_by_name(name)))
		return -ENOENT;

	if(NULL == (name = next_word(name)) || NULL == (node = pnet_get_module(name)))
		return -ENOENT;

	return pnet_graph_add_node(gr, node);
}

static int link_node(char *str) {
	char *name;
	net_node_t src, node;
	struct pnet_graph *gr;

	if(NULL == (name = str) || NULL == (gr = get_graph_by_name(name)))
		return -ENOENT;

	if(NULL == (name = next_word(name)) || NULL == (src = get_node_from_graph_by_name(gr, name)))
		return -ENOENT;

	if(NULL == (name = next_word(name)) || NULL == (node = get_node_from_graph_by_name(gr, name)))
		return -ENOENT;

	return pnet_node_link(src, node);
}

static int form_rule(match_rule_t rule, const char *rule_elem, struct pnet_graph *gr, int num) {
	if ('*' == rule_elem[0]) {
		return 0;
	}

	switch (num) {
	case 1:
		macaddr_scan((unsigned char *) rule_elem,
				rule->skbuf->mac.ethh->h_source);
		break;
	case 2:
		if (strcmp("IP", rule_elem) == 0) {
			pnet_rule_set_pack_type(rule, ETH_P_IP);
		} else if (strcmp("ARP", rule_elem) == 0) {
			pnet_rule_set_pack_type(rule, ETH_P_ARP);
		}
		break;
	case 3:
		ipaddr_scan((unsigned char *) rule_elem,
				(unsigned char *) &rule->skbuf->nh.iph->saddr);
		break;
	case 4:
		if (strcmp("icmp", rule_elem) == 0) {
			pnet_rule_set_proto(rule, 0x1);
		} else if (strcmp("udp", rule_elem) == 0) {
			pnet_rule_set_proto(rule, 0x11);
		}
		break;
	case 5:
		pnet_rule_set_src_udp_port(rule, *(uint16_t*) rule_elem);
		break;
	case 6:
		rule->next_node = get_node_from_graph_by_name(gr, (char *) rule_elem);
		break;
	}

	return 0;
}

static int exec(int argc, char **argv) {
	int opt;
	char *name;
	struct pnet_graph *gr;
	const struct pnet_module *mod;
	match_rule_t rule;

	getopt_init();

	while (-1 != (opt = getopt(argc, argv, "hgnp:r:s:a:l:"))) {
		name = optarg;
		name--;
		switch(opt) {
		case 'h':
			print_usage();
			break;
		case 'g':
			print_graph_names();
			break;
		case 'p':
			name = next_word(name);
			if (!strcmp("--nodes", name)) {
				name = next_word(name);
				if (NULL != (gr = get_graph_by_name(name)))
					print_graph_node_list(gr);
				else
					printf("%s: no such graph", name);
			} else if (NULL != (gr = get_graph_by_name(name))){
				print_graph(gr);
			} else {
				printf("%s: no such graph", name);
			}
			break;
		case 'n' :
			printf("nodes: ");
			array_foreach_ptr(mod, __pnet_mod_repo, ARRAY_SPREAD_SIZE(__pnet_mod_repo)) {
				printf("%s, ", mod->node->proto->name);
			}
			break;
		case 'r':
			name = next_word(name);
			if (NULL != (gr = get_graph_by_name(name))) {
				pnet_graph_start(gr);
				printf("%s run \n", gr->name);
			} else {
				printf("%s: no such graph \n", name);
			}
			break;
		case 's':
			name = next_word(name);
			if (NULL != (gr = get_graph_by_name(name))) {
				pnet_graph_stop(gr);
				printf("%s stopped \n", gr->name);
			} else {
				printf("%s: no such graph \n", name);
			}
			break;
		case 'a' :
			name = next_word(name);
			if (!strcmp("--node", name)) {
				name = next_word(name);
				if (add_node(name) < 0)
					printf("%s", "error\n");
			} else if (!strcmp("--graph", name)) {
				name = next_word(name);
				pnet_graph_create(name);
			} else if (!strcmp("--rule", name)){
				rule = pnet_rule_alloc();
				name = next_word(name);
				gr = get_graph_by_name(name);

				name = next_word(name);
				if(!strcmp(name, "--proto")) {
					name = next_word(name);
					form_rule(rule,name, gr, 4);
				}
			} else {
				print_usage();
			}
			break;
		case 'l':
			name = next_word(name);
			if(link_node(name) < 0)
				printf("%s", "error");
			break;
		default:
			return 0;
		}
	}

	return 0;
}
