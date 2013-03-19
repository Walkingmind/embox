/**
 * @file
 * @brief Runs start script
 *
 * @date 04.10.11
 * @author Alexander Kalmuk
 */

#include <errno.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <util/array.h>
#include <embox/unit.h>

#include <framework/cmd/api.h>

#include <cmd/shell.h>


#include <kernel/task.h>
#include <kernel/task/idx.h>

#include <kernel/printk.h>

#define BUF_INP_SIZE OPTION_GET(NUMBER,input_buffer)

EMBOX_UNIT_INIT(run_script);

static const char *script_commands[] = {
	#include <start_script.inc>
};

static void setup_tty(const char *dev_name) {
	int fd;
	char full_name[MAX_LENGTH_PATH_NAME];

	putenv("TERM=emterm");

	if (strlen(dev_name) == 0) {
		return;
	}

	strncpy(full_name, "/dev/", sizeof(full_name));
	strcat(full_name, dev_name);

	if (-1 == (fd = open(full_name, O_RDWR))) {
		return;
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
}

static int run_script(void) {
	const char *command;
	const struct shell *shell;

	printk("\nStarting shell [%s] at device [%s]\n",
		OPTION_STRING_GET(shell_name), OPTION_STRING_GET(tty_dev));
	setup_tty(OPTION_STRING_GET(tty_dev));

	shell = shell_lookup(OPTION_STRING_GET(shell_name));
	if (NULL == shell) {
		char env[20];
		shell = shell_any();

		if (NULL == shell) {
			return -ENOENT;
		}
		sprintf(env, "shell=%s", shell->name);
		putenv(env);
	}

	printk("loading start script:\n");
	array_foreach(command, script_commands, ARRAY_SIZE(script_commands)) {
		printk("> %s \n", command);

		shell_exec(shell, command);
	}

	shell_run(shell);

	return 0;
}
