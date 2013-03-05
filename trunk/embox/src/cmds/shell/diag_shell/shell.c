/**
 * @file
 *
 * @date 02.02.09
 * @author Alexey Fomin
 */

#include <embox/unit.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <util/array.h>
#include <cmd/cmdline.h>
#include <framework/cmd/api.h>
#include <cmd/shell.h>

#include "console/console.h"

// XXX just for now -- Eldar
EMBOX_UNIT(shell_start, shell_stop);

static void exec_callback(CONSOLE_CALLBACK *cb, CONSOLE *console, char *cmdline) {
	const struct cmd *cmd;
	int code;
	/* In the worst case cmdline looks like "x x x x x x". */
	char *argv[(CMDLINE_MAX_LENGTH + 1) / 2];
	int argc = 0;

	if (0 == (argc = cmdline_tokenize(cmdline, argv))) {
		/* Only spaces were entered */
		return;
	}

	if (NULL == (cmd = cmd_lookup(argv[0]))) {
		printf("%s: Command not found\n", argv[0]);
		return;
	}

	if (0 != (code = cmd_exec(cmd, argc, argv))) {
		printf("%s: Command returned with code %d: %s\n",
				cmd_name(cmd), code, strerror(-code));
	}
}

/**
 * Guesses command using its beginning
 *
 * -- Eldar
 */
static void guess_callback(CONSOLE_CALLBACK *cb, CONSOLE *console,
		const char* line, const int max_proposals, int *proposals_len,
		const char *proposals[], int *offset, int *common) {
	const struct cmd *cmd = NULL;
	int cursor = strlen(line);
	int start = cursor, i;
	char ch;

	while (start > 0 && isalpha(line[start - 1])) {
		start--;
	}
	line += start;

	*offset = cursor - start;
	*proposals_len = 0;

	cmd_foreach(cmd) {
		if (0 == strncmp(cmd_name(cmd), line, *offset)) {
			proposals[(*proposals_len)++] = cmd_name(cmd);
		}
	}

	*common = 0;
	if (*proposals_len == 0) {
		return;
	}
	while (1) {
		if ((ch = proposals[0][*offset + *common]) == '\0') {
			return;
		}
		for (i = 1; i < *proposals_len; ++i) {
			if (ch != proposals[i][*offset + *common]) {
				return;
			}
		}
		(*common)++;
	}
}

static CONSOLE console[1];


static int shell_start(void) {
	static CONSOLE_CALLBACK callback[1];

	callback->exec = exec_callback;
	callback->guess = guess_callback;
	if (console_init(console, callback) == NULL) {
		printf("Failed to create a console");
		return -1;
	}

	return 0;
}

static void diag_shell_run(void) {
	static const char* prompt = OPTION_STRING_GET(prompt);

	printf("\n%s", OPTION_STRING_GET(welcome_msg));
	console_start(console, prompt);
}

static int shell_stop(void) {
	console_stop(console);
	return 0;
}

SHELL_DEF({
	.name = "diag_shell",
	.exec = NULL,
	.run  = diag_shell_run,
	});
