/**
 * @file
 * @brief
 *
 * @date 21.03.2013
 * @author Anton Bulychev
 */

#include <assert.h>
#include <kernel/task.h>
#include <kernel/task/resource.h>
#include <kernel/task/resource/waitpid.h>
#include <kernel/sched/waitq.h>
#include <stddef.h>

TASK_RESOURCE_DESC(task_waitpid_res);

static void task_waitpid_init(const struct task *task,
		void *waitpid_space) {
	struct waitq *waitq;

	assert(waitpid_space == task_resource_waitpid(task));

	waitq = waitpid_space;
	assert(waitq != NULL);

	waitq_init(waitq);
}

static void task_waitpid_deinit(const struct task *task) {
	struct waitq *waitq;

	waitq = task_resource_waitpid(task);
	assert(waitq != NULL);

	waitq_wakeup_all(waitq);
}

static size_t task_waitpid_res_offset;

static const struct task_resource_desc task_waitpid_res = {
	.init = task_waitpid_init,
	.deinit = task_waitpid_deinit,
	.resource_size = sizeof(struct waitq),
	.resource_offset = &task_waitpid_res_offset
};

struct waitq * task_resource_waitpid(const struct task *task) {
	assert(task != NULL);
	assert(task->resources != NULL);
	return task->resources + task_waitpid_res_offset;
}
