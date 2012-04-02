/**
 * @file
 * @brief Console command prompt.
 *
 * @details Supports typing proposals and custom welcome messages.
 *
 * Implementation of MVC with passive model.
 * This entity is controller, cmdline is model, and screen is view.
 *
 * @author: Eldar Abusalimov
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "cmdline.h"
#include "screen.h"

#include <embox/unit.h> /* For getting options -- Anton K */

struct _CONSOLE;

typedef struct _CONSOLE_CALLBACK {
	void (*exec)(struct _CONSOLE_CALLBACK *, struct _CONSOLE *console,
			char *line);
	void (*guess)(struct _CONSOLE_CALLBACK *, struct _CONSOLE *console,
			const char* line, const int max_proposals, int *proposals_len,
			const char *proposals[], int *offset, int *common);
	void *user_data;
} CONSOLE_CALLBACK;

typedef struct _CONSOLE {
	CONSOLE_CALLBACK *callback;
	CMDLINE model[1];
	SCREEN view[1];
	char prompt[OPTION_GET(NUMBER, prompt_len) + 1];
} CONSOLE;

CONSOLE * console_init(CONSOLE *, CONSOLE_CALLBACK *callback);

void console_start(CONSOLE *, const char *prompt);

void console_stop(CONSOLE *);

#endif /* CONSOLE_H_ */
