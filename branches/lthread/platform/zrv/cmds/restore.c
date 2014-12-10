/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    29.03.2013
 */

#include <stdio.h>
#include <cmd/shell.h>
#include <embox/cmd.h>
#include <unistd.h>
#include <string.h>


EMBOX_CMD(restore_cmd);

static void usage(char *cmd) {
	printf("Usage: %s BACKUP DIR [-f]\n", cmd);
}

#define BUFLEN 160
#define MIN_ARGS_OF_RESTORE 3

static int restore_cmd(int argc, char *argv[]) {
	const struct shell *sh = shell_any();
	char buf[BUFLEN];
	char *src = argv[1];
	char *dst = argv[2];
	int opt;
	int min_argc = MIN_ARGS_OF_RESTORE;

	getopt_init();

	while (-1 != (opt = getopt(argc, argv, "hf"))) {

		switch (opt) {
		case '?':
		case 'h': /* show help */
			usage(argv[0]);
			return ENOERR;
		case 'f': /* force overwrite */
			min_argc = 4;

			if (argc != min_argc) {
				usage(argv[0]);
				return -EINVAL;
			}

			if(0 != strncmp(dst, "/", 1) ||
			   0 != strncmp(src, "/", 1)) {
				return -EINVAL;
			}

			if (-1 == remove(dst)) {
				return -errno;
			}
			break;

			if (-1 == mkdir(dst, 0)) {
				return -errno;
			}
			break;
		default:
			break;
		}
	}

	if (argc != min_argc) {
			usage(argv[0]);
			return -EINVAL;
		}

	if(0 != strncmp(dst, "/", 1) ||
	   0 != strncmp(src, "/", 1)) {
		return -EINVAL;
	}

	if (BUFLEN <= snprintf(buf, BUFLEN, "backup %s %s", src, dst)) {
		return -ENOMEM;
	}

	return shell_exec(sh, buf);

}
