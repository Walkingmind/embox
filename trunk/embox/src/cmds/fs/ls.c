/**
 * @file
 * @brief List directory contents.
 *
 * @date 02.07.09
 * @author Anton Bondarev
 */


#include <getopt.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include <fs/vfs.h>
#include <fs/ramfs.h>
#include <sys/stat.h>
#include <util/tree.h>

#include <embox/cmd.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: ls [-hl] path\n");
}

/*
static void print_long_list(char *path, node_t *node, int recursive) {
	node_t *item;
	stat_t sb;
	char time_buff[26]; //ctime_r requires it least 26 byte buffer lentgh
	printf("%s\t%s\t%s\t\t\t%s\n", "mode", "size", "mtime", "name");
	tree_foreach_children(item, &node->tree_link, tree_link) {
		//stat((char *) item->name, &sb);
		ctime_r((time_t *) &(sb.st_mtime), time_buff);
		printf("%d\t%d\t%s\t%s\n",
			sb.st_mode,
			sb.st_size,
			time_buff,
			(char *) item->name);
	}
}
*/

static void print_folder(char *path, node_t *node, int recursive) {
	node_t *item;

	if(DIRECTORY_NODE_TYPE != (node->properties & DIRECTORY_NODE_TYPE)) {
		printf("%s\n",  path);
		return;
	}
	tree_foreach_children(item, (&node->tree_link), tree_link) {
		if (recursive) {
			if (0 == strcmp(path, "/")) {
				printf("%s\n",  (char *) item->name);
			} else {
				printf("%s/%s\n", path, (char *) item->name);
				strcat(path, (char *) item->name);
				print_folder(path, item, recursive);
			}
		} else {
			printf("%s\n", (char *) item->name);
		}
	}
}

typedef void (*print_func_t)(char *path, node_t *nod, int recursive);

static int exec(int argc, char **argv) {
	//int long_list = 0;
	int opt_cnt = 0;
	node_t *nod;
	char path[MAX_LENGTH_FILE_NAME];

	int recursive = 0;
	volatile print_func_t print_func = print_folder;

	int opt;
	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "Rlh"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		/*case 'l':
			//long_list = 1;
			print_func = print_long_list;
			opt_cnt++;
			break;*/
		case 'R':
			recursive = 1;
			print_func = print_folder;
			opt_cnt++;
			break;
		case '?':
			break;
		default:
			printf("ls: invalid option -- '%c'\n", optopt);
			return -1;
		}
	}

	if (optind < argc) {
		sprintf(path, "%s", argv[optind]);
	} else {
		sprintf(path, "/");
	}

	nod = vfs_find_node(path, NULL);
	if (NULL == nod) {
		printf("ls: cannot access %s: No such file or directory\n", path);
		return -1;
	}
	print_func(path, nod, recursive);

	return 0;
}
