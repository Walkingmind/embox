/**
 * @file
 * @brief
 *
 * @date 14.03.13
 * @author Ilia Vaprol
 */

#include <embox/cmd.h>
#include <stdio.h>
#include <kernel/task.h>
#include <kernel/task/task_table.h>
#include <kernel/task/u_area.h>

EMBOX_CMD(exec);

static int exec(int argc, char **argv) {
	int tid;
	struct task *task;

	printf("PID USER  PR COMMAND\n");
	for (tid = 0; (tid = task_table_get_first(tid)) >= 0; ++tid) {
		task = task_table_get(tid);
		printf("%-3d %-4d % 3d %s\n", tid, task->u_area->reuid,
				task_get_priority(task), task->task_name);
	}

	return 0;
}
