/**
 * @file
 * @brief Socket registry maintenance header
 *
 * @date 23.03.12
 * @author Timur Abdukadyrov
 */

#ifndef SOCKET_REGISTRY_H_
#define SOCKET_REGISTRY_H_

/* TODO: add descriptions */

/* inner functions for address binding maintance */
extern int sr_add_socket_to_registry(struct socket *sock);
extern int sr_remove_socket_from_registry(struct socket *sock);
extern int sr_set_saddr(struct socket *sock, const struct sockaddr *addr);
extern void sr_remove_saddr(struct socket *sock);


extern bool sr_is_saddr_free(struct socket *sock, struct sockaddr *addr);
extern bool sr_is_daddr_free(struct socket *sock, struct sockaddr *addr);

#endif
