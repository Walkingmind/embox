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

EMBOX_CMD(restore_cmd);

static void usage(char *cmd) {
	printf("Usage: %s DIR BACKUP", cmd);
}

#define BUFLEN 160

static int restore_cmd(int argc, char *argv[]) {
	const struct shell *sh = shell_any();
	char buf[BUFLEN];

	if (argc != 3) {
		usage(argv[0]);
		return -EINVAL;
	}

	if (BUFLEN <= snprintf(buf, BUFLEN, "backup %s %s", argv[1], argv[2])) {
		return -ENOMEM;
	}

	return shell_exec(sh, buf);
}
