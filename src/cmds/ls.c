/**
 * @file
 * @brief List directory contents.
 *
 * @date 02.07.09
 * @author Anton Bondarev
 */

#include <embox/cmd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <fs/file.h>
#include <fs/vfs.h>
#include <fs/ramfs.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: ls [-hl] path\n");
}

static void print_long_list(char *path, node_t *nod, int recursive) {
	struct list_head *p;
	node_t *item;
	stat_t sb;
	char time_buff[17];
	printf("%s\t%s\t%s\t\t\t%s\n", "mode", "size", "mtime", "name");

	list_for_each(p, &(nod->leaves)) {
		item = (node_t*) list_entry(p, node_t, neighbors);
		fstat((char *) item->name, &sb);
		ctime((time_t *) &(sb.st_mtime), time_buff);
		printf("%d\t%d\t%s\t%s\n",
			sb.st_mode,
			sb.st_size,
			time_buff,
			(char *) item->name);
	}
}

static void print_folder(char *path, node_t *nod, int recursive) {
	struct list_head *p;
	list_for_each(p, &(nod->leaves)) {
		if (recursive) {
			if (0 == strcmp(path, "/")) {
				printf("%s\n",  (char *) ((node_t*) list_entry(p, node_t, neighbors))->name);
			} else {
				printf("%s/%s\n", path, (char *)((node_t*) list_entry(p, node_t, neighbors))->name);
				strcat(path, (char *)((node_t*) list_entry(p, node_t, neighbors))->name);
				print_folder(path, (node_t*) list_entry(p, node_t, neighbors), recursive);
			}
		} else {
			printf("%s\n", (char *) ((node_t*) list_entry(p, node_t, neighbors))->name);
		}
	}
}

typedef void (*print_func_t)(char *path, node_t *nod, int recursive);

static int exec(int argc, char **argv) {
	//int long_list = 0;
	node_t *nod;
	char path[CONFIG_MAX_LENGTH_FILE_NAME];

	int recursive = 0;
	volatile print_func_t print_func = print_folder;

	int opt;
	getopt_init();
	while (-1 != (opt = getopt(argc - 1, argv, "Rlh"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		case 'l':
			/*long_list = 1;*/
			print_func = print_long_list;
			break;
		case 'R':
			recursive = 1;
			print_func = print_folder;
		default:
			printf("ls: invalid option -- '%c'\n", optopt);
			return -1;
		}
	}

	//TODO: Maybe we should support multiple file args
	if (argc > optind) {
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
