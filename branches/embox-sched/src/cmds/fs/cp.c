 /**
 * @file
 * @brief Mini cp implementation for Embox.
 *
 * @date 22.08.09
 * @author Roman Evstifeev
 */

#include <embox/cmd.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <mem/page.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: cp [-h] [source] [dest]\n");
}

static int exec(int argc, char **argv) {
	int opt, src_file, dst_file, ret;
	char buf[PAGE_SIZE()];
	int bytesread;
	const char *src_path,*dst_path;
	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			break;
		}
	}

	if (argc < 3) {
		print_usage();
		return -EINVAL;
	}

	dst_path = argv[argc - 1];
	src_path = argv[argc - 2];

	if (-1 == (src_file = open(src_path, O_RDONLY)))  {
		printf("can't open file %s\n",src_path);
		return -errno;
	}

	if (-1 == (dst_file = open(dst_path, O_WRONLY))) {
		if(0 > (dst_file = creat(dst_path, 0))) {
			ret = -errno;
			printf("can't open file %s\n",dst_path);
			close(src_file);
			return ret;
		}
	}

	lseek(dst_file, 0, SEEK_SET);

	// buf optimized for whole block write
	bytesread = 0;
	while ((bytesread = read(src_file, buf, PAGE_SIZE())) > 0) {
		if (write (dst_file, buf, bytesread)<=0) {
			printf ("WR ERR!\n");
			break;
		}
	}

	ret = 0;
	if (fsync(dst_file)) {
		ret = -errno;
	}

	close(src_file);
	close(dst_file);
	return ret;
}
