/**
 * @file
 *
 * @brief
 *
 * @date 06.12.2011
 * @author Anton Bondarev
 */

#include <errno.h>
#include <string.h>

#include <util/dlist.h>

#include <kernel/task.h>
#include <util/binalign.h>
#include <stdint.h>


#include "common.h"


ARRAY_SPREAD_DEF(const struct task_resource_desc *, task_resource_desc_array);
ARRAY_SPREAD_DEF(const task_notifing_resource_hnd, task_notifing_resource);

static size_t resource_sum_size = sizeof(struct task);

void resource_sum_size_calc(void) {
	const struct task_resource_desc *res_desc;

	task_resource_foreach(res_desc) {
		if(res_desc->resource_init) {
			res_desc->resource_init(res_desc, resource_sum_size);
		}

		resource_sum_size += res_desc->resource_size;
	}
}

size_t task_resource_sum_size(void) {
	return resource_sum_size;
}

size_t task_size(void) {
	return resource_sum_size;
}


struct task *task_init(void *task_n_res_space, size_t size) {
	struct task *task;
	void *res_ptr;
	const struct task_resource_desc *res_desc;
	size_t task_off, task_sz;

	task = (struct task *)binalign_bound((uintptr_t)task_n_res_space, 4);
	task_off = (void *)task - task_n_res_space;
	task_sz = task_size();
	res_ptr = (void *)task + sizeof(struct task);

	if (size < task_off + task_sz) {
		return NULL;
	}

	memset(task_n_res_space, 0, task_sz);

	dlist_head_init(&task->task_link);

	dlist_init(&task->children_tasks);

	task->parent = NULL;

	task->priority = TASK_PRIORITY_DEFAULT;

	task_resource_foreach(res_desc) {
		res_desc->init(task, res_ptr);
		res_ptr += res_desc->resource_size;
	}

	task_thread_key_init(task);

	/* FIXME: This should be only in SMP */
	task->affinity = TASK_AFFINITY_DEFAULT;

	return task;

}
