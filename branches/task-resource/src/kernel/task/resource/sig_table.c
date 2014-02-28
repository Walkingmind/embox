/**
 * @file
 * @brief
 *
 * @date    22.10.2012
 * @author  Anton Kozlov
 * @author  Alexander Kalmuk
 * 			- split signals into standard signals and real-time signals
 * @author  Eldar Abusalimov
 */

#include <assert.h>
#include <kernel/task.h>
#include <kernel/task/resource.h>
#include <kernel/task/resource/sig_table.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

TASK_RESOURCE_DEF(task_sig_table_desc, struct sigaction [_SIG_TOTAL]);

static void task_sig_handler_terminate(int sig) {
	task_exit(NULL);
}

static void task_sig_table_init(const struct task *task,
		void *sig_table_space) {
	struct sigaction *sig_table;
	int sig;

	assert(sig_table_space == task_resource_sig_table(task));

	sig_table = sig_table_space;
	assert(sig_table != NULL);

	for (sig = 0; sig < _SIG_TOTAL; ++sig) {
		sig_table[sig].sa_flags = 0;
		memset(&sig_table[sig].sa_mask, 0,
				sizeof sig_table[sig].sa_mask);;
		sig_table[sig].sa_handler = task_sig_handler_terminate;
	}
}

static size_t task_sig_table_offset;

static const struct task_resource_desc task_sig_table_desc = {
	.init = task_sig_table_init,
	.resource_size = sizeof(struct sigaction) * _SIG_TOTAL,
	.resource_offset = &task_sig_table_offset
};

struct sigaction * task_resource_sig_table(const struct task *task) {
	assert(task != NULL);
	return (void *)task->resources + task_sig_table_offset;
}
