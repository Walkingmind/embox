/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    18.02.2013
 */

#include <security/security.h>

int security_node_permissions(struct node *node, int flags) {
	return 0;
}

int security_node_create(struct node *dir, mode_t mode) {
	return 0;
}

int security_node_delete(struct node *dir, struct node *node) {
	return 0;
}

int security_mount(struct node *dev) {
	return 0;
}

