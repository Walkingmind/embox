/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    29.03.2013
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <cmd/shell.h>
#include <embox/cmd.h>
#include <string.h>

EMBOX_CMD(backup_exec);

static void usage(char *cmd) {
	printf("Usage: %s DIR BACKUP [-f]\n", cmd);
}

#define BUFLEN 160
#define MIN_ARGS_OF_RESTORE 3

static int backup_exec(int argc, char *argv[]) {
	DIR *dir;
	struct dirent *dent;
	char *src = argv[1];
	char *dst = argv[2];
	stat_t sb;
	const struct shell *sh = shell_any();
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

	if (-1 == stat(src, &sb)) {
		printf("Cannot stat %s\n", src);
		return -EINVAL;
	}

	if (!(sb.st_mode & S_IFDIR)) {
		return -ENOTDIR;
	}

	if (NULL == (dir = opendir(src))) {
		return -errno;
	}

	if (-1 == stat(dst, &sb)) {
		if (0 > mkdir(dst, 0755)) {
			return -errno;
		}
	}

	while (NULL != (dent = readdir(dir))) {
		char buf[BUFLEN];
		int res;

		if (BUFLEN <= snprintf(buf, BUFLEN, "cp %s/%s %s/%s", src, 
					dent->d_name, dst, dent->d_name)) {
			return -ENOMEM;
		}

		if (0 > (res = shell_exec(sh, buf))) {
			return res;
		}
	}

	return 0;
}
