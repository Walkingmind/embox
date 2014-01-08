/**
 * @file
 * @brief
 *
 * @date 09.11.12
 * @author Anton Bulychev
 */

#include <kernel/task.h>
#include <mem/mmap.h>

#include "../kernel/task/common.h"

static void task_mmap_init(struct task *task, void *mmap) {
	task->mmap = mmap;
	mmap_init(task->mmap);
}

static int task_mmap_inherit(struct task *task, struct task *parent_task) {
	return mmap_inherit(task->mmap, parent_task->mmap);
}

static void task_mmap_deinit(struct task *task) {
	mmap_free(task->mmap);
}

static const struct task_resource_desc mmap_resource = {
	.init = task_mmap_init,
	.inherit = task_mmap_inherit,
	.deinit = task_mmap_deinit,
	.resource_size = sizeof(struct emmap),
};

TASK_RESOURCE_DESC(&mmap_resource);