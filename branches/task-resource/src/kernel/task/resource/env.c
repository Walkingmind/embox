/**
 * @file
 * @brief
 *
 * @author Ilia Vaprol
 * @date 30.03.13
 */

#include <assert.h>
#include <kernel/task.h>
#include <kernel/task/resource.h>
#include <kernel/task/resource/env.h>
#include <stddef.h>
#include <string.h>

#include "env.h"

TASK_RESOURCE_DESC(task_env_res);

static void task_env_init(const struct task *task, void *env_space) {
	struct task_env *env;

	assert(env_space == task_resource_env(task));

	env = env_space;
	assert(env != NULL);

	env->envs = NULL;
	env->next = 0;
}

static int task_env_inherit(const struct task *task,
		const struct task *parent) {
	struct task_env *task_env, *parent_env;
	size_t i;

	task_env = task_resource_env(task);
	assert(task_env != NULL);

	parent_env = task_resource_env(parent);
	assert(parent_env != NULL);

	task_env->envs = parent_env->envs != NULL ? &task_env->vals[0] : NULL;
	task_env->next = parent_env->next;
	for (i = 0; i < task_env->next; ++i) {
		task_env->vals[i] = &task_env->storage[i][0];
	}
	memcpy(&task_env->storage[0][0], &parent_env->storage[0][0],
			task_env->next * ARRAY_SIZE(task_env->storage[0]));

	return 0;
}

static size_t task_env_res_offset;

static const struct task_resource_desc task_env_res = {
	.init = task_env_init,
	.inherit = task_env_inherit,
	.resource_size = sizeof(struct task_env),
	.resource_offset = &task_env_res_offset
};

struct task_env * task_resource_env(const struct task *task) {
	assert(task != NULL);
	assert(task->resources != NULL);
	return task->resources + task_env_res_offset;
}
