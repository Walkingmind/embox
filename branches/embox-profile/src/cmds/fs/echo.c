/**
 * @file
 * @brief
 *
 * @date 25.04.2012
 * @author Andrey Gazukin
 */

#include <embox/cmd.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: echo \"STRING\" >> FILE\n");
}

static int exec(int argc, char **argv) {
	int opt;
	FILE *fd;
	const char *mode;

	getopt_init();
	while (-1 != (opt = getopt(argc - 1, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			break;
		}
	}

	if (argc > 3) {
		if (0 == strcmp((const char *) argv[argc - 2], ">>")) {
			mode = "a";
		} else if (0 == strcmp((const char *) argv[argc - 2], ">")) {
			mode = "w";
		}
		else {
			print_usage();
			return 0;
		}

		if (NULL == (fd = fopen((const char *) argv[argc - 1], mode))) {
			return -errno;
		}

		fwrite((const void *) argv[1], strlen((const char *) argv[1]), 1, fd);
		fwrite((const void *) "\n", 1, 1, fd);
		fclose(fd);
		return 0;
	}
	else if (argc == 2) {
		printf("%s \n",argv[argc - 1]);
	}
	else {
		print_usage();
	}
	return 0;
}
