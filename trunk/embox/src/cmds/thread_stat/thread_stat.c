/**
 * @file
 * @brief Prints threads statistic for EMBOX
 *
 * @date 2 Dec 2010
 * @author Gleb Efimov
 * @author Alina Kramar
 * @author Roman Oderov
 */

#include <shell_command.h>
#include <kernel/thread.h>
#include <lib/list.h>
#include <stdio.h>

#define COMMAND_NAME     "thread_stat"
#define COMMAND_DESC_MSG "print threads statistic for EMBOX"
#define HELP_MSG         "Usage: thread_stat [-h] "
static const char *man_page =
#include "thread_stat_help.inc"
;

DECLARE_SHELL_COMMAND(COMMAND_NAME, exec, COMMAND_DESC_MSG, HELP_MSG, man_page);

struct stats_context {
	int run, wait, stop, zombie;
};

static void print_statistic(struct stats_context *ctx, struct thread *thread) {
	switch (thread->state) {
	case THREAD_STATE_RUN:
		ctx->run++;
		break;
	case THREAD_STATE_WAIT:
		ctx->wait++;
		break;
	case THREAD_STATE_ZOMBIE:
		ctx->zombie++;
		break;
	default:
		break;
	}

	TRACE("\tTHREAD id : %d; priority : %d; \n", thread->id, thread->priority);
}

static int exec(int argc, char **argv) {
	struct thread *thread;
	int next_opt;

	getopt_init();

	while ((next_opt = getopt(argc, argv, "h")) != -1) {
		switch (next_opt) {
		case '?':
		case -1:
		case 'h':
			show_help();
			/* FALLTHROUGH */
		default:
			return 0;
		};
	}

	struct stats_context ctx = { 0 };

	thread_foreach(thread) {
		if (thread->exist) {
			print_statistic(&ctx, thread);
		} else {
			ctx.stop++;
		}
	}

	TRACE("THREAD_STATE_RUN  %d\n", ctx.run);
	TRACE("THREAD_STATE_WAIT  %d\n", ctx.wait);
	TRACE("THREAD_STATE_STOP  %d\n", ctx.stop);
	TRACE("THREAD_STATE_ZOMBIE  %d\n", ctx.zombie);

	return 0;
}
