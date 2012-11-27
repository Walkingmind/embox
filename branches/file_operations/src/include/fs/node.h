/**
 * @file
 * @brief pool of nodes
 *
 * @date 06.10.10
 * @author Nikolay Korotky
 */

#ifndef FS_NODE_H_
#define FS_NODE_H_

#include <fs/fs_drv.h>
#include <util/tree.h>

#include <module/embox/fs/core.h>
#include <framework/mod/options.h>


#define MAX_LENGTH_FILE_NAME  OPTION_MODULE_GET(embox__fs__core,NUMBER,file_name_length)
#define MAX_LENGTH_PATH_NAME  OPTION_MODULE_GET(embox__fs__core,NUMBER,path_length)



#define NODE_TYPE_FILE       0x00
#define NODE_TYPE_DIRECTORY  0x10
#define NODE_TYPE_SPECIAL    0x20

typedef struct node {
	const char            name[MAX_LENGTH_FILE_NAME];
	int                   properties;  /* FILE, DIRECTORY, DEVICE, LINK ... */
	//void                 *node_info;   /* WTF? maybe introduce Node Attribute Structure(NAS)? (sikmir) */
	void                 *fi;
	struct tree_link      tree_link;
	void                 *nas;
	struct filesystem    *fs;
} node_t;

#if 1
typedef struct file_create_param {
	void  *node;
	void  *parents_node;
	char   path[MAX_LENGTH_PATH_NAME];
} file_create_param_t;

#endif

extern node_t *node_alloc(const char *name);
extern void node_free(node_t *node);


static inline int node_is_block_dev(struct node *node) {
	return 1;
}

static inline int node_is_directory(struct node *node) {
	return node->properties & NODE_TYPE_DIRECTORY;
}

#endif /* FS_NODE_H_ */
