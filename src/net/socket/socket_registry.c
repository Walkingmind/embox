/**
 * @file
 * @brief Socket registry maintenance
 *
 * @date 23.03.12
 * @author Timur Abdukadyrov
 */

/* clean out unnecessary headers */
#include <errno.h>
#include <string.h>

#include <net/sock.h>
#include <util/debug_msg.h>
#include <mem/objalloc.h>
#include <util/dlist.h>
#include <net/socket_registry.h>

/* system socket registry */
POOL_DEF(socket_pool, socket_node_t, MAX_SYSTEM_CONNECTIONS);
DLIST_DEFINE(socket_registry);

static inline socket_node_t *get_sock_node_by_socket(struct socket *sock); 
static socket_node_t *get_sock_node_by_src_address(struct socket *sock,
    struct sockaddr *addr);
static socket_node_t *get_sock_node_by_dst_address(struct socket *sock,
    struct sockaddr *addr);


int sr_add_socket_to_registry(struct socket *sock){
	socket_node_t *newnode;

	/* allocate new node */
	newnode = (socket_node_t *)pool_alloc(&socket_pool);
	newnode->link.list_id = 0;  /* 0_o */
	if(newnode == NULL)
		return -ENOMEM;
	
	/* set source address data to NULL for now*/
	memset(&newnode->saddr, 0, sizeof(struct sockaddr));
	/* set destination address data to NULL for now*/
	memset(&newnode->daddr, 0, sizeof(struct sockaddr));

	/* set socket link */
	newnode->sock = sock;

	sock->socket_node = newnode;

	/* list_add_tail(&socket_registry_head, &newnode->link); */
	dlist_add_next(&newnode->link, &socket_registry);

	debug_printf("adding socket to pool",
							 "kernel_socket", "add_socket_to_pool");

	return ENOERR;
}

int sr_remove_socket_from_registry(struct socket *sock){
	socket_node_t *node;

	node = get_sock_node_by_socket(sock);
	if(node){
		debug_printf("removing socket entity...", "kernel_socket",
								 "remove_socket_from_pool");
		dlist_del(&node->link);
		pool_free(&socket_pool, node);
		return ENOERR;
	}
	return -1;
}

bool sr_is_saddr_free(struct socket *sock, struct sockaddr *addr){

	if(get_sock_node_by_src_address(sock, addr))
		return false;
	else
		return true;
}

bool sr_is_daddr_free(struct socket *sock, struct sockaddr *addr){

	if(get_sock_node_by_dst_address(sock, addr))
		return false;
	else
		return true;
}

bool sr_socket_exists(struct socket *sock){
	socket_node_t *node, *tmp;

	if(sock){  /* address validity */
		dlist_foreach_entry(node, tmp, &socket_registry, link){
			if(sock == node->sock)
				return true;
		}
	}
	return false;	
}

int sr_set_saddr(struct socket *sock, const struct sockaddr *addr){
	/* copy address data */
	memcpy(&sock->socket_node->saddr, addr, sizeof(struct sockaddr));

	debug_printf("bound address to socket",
							 "kernel_socket", "bind_address");

	return 0;
}

void sr_remove_saddr(struct socket *sock){
	socket_node_t *node;

	node = get_sock_node_by_socket(sock);
	if(node){
		debug_printf("found socket. trying to unbind...", 
								 "kernel_socket", "unbind_socket");
		memset(&node->saddr, 0, sizeof(struct sockaddr));
	}
}

static socket_node_t *get_sock_node_by_src_address(struct socket *sock,
																							 struct sockaddr *addr){
	socket_node_t *node, *tmp;

	if(addr){  /* address validity */
		dlist_foreach_entry(node, tmp, &socket_registry, link){
			if(sock->ops->compare_addresses(addr, &node->saddr) &&
				 (sock->type == node->sock->type))
				return node;
		}
	}
	return NULL;
}

static socket_node_t *get_sock_node_by_dst_address(struct socket *sock,
																							 struct sockaddr *addr){
	socket_node_t *node, *tmp;

	if(addr){  /* address validity */
		dlist_foreach_entry(node, tmp, &socket_registry, link){
			if(sock->ops->compare_addresses(addr, &node->daddr))
				return node;
		}
	}
	return NULL;
}

static inline socket_node_t *get_sock_node_by_socket(struct socket *sock){
	return sock ? sock->socket_node : NULL;
}
