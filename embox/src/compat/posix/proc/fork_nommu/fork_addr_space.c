/**
 * @file 
 * @brief 
 *
 * @author  Denis Deryugin
 * @date    30.07.2014
 */

#include "fork_copy_addr_space.h"
#include <kernel/task/resource.h>
#include <kernel/task/resource/task_fork.h>
#include <mem/sysmalloc.h>
#include <sys/types.h>

void fork_addr_space_prepare_switch(void) {
	struct addr_space *adrspc;

	adrspc = fork_addr_space_get(task_self());
	if (!adrspc) {
		return;
	}

	fork_addr_space_store(adrspc);
}

static int fork_addr_space_is_shared(struct addr_space *adrspc) {
	return adrspc->parent_addr_space || adrspc->child_count;
}

void fork_addr_space_finish_switch(void *safe_point) {
	struct addr_space *adrspc;
	
	adrspc = fork_addr_space_get(task_self());
	if (!adrspc) {
		return;
	}

	fork_addr_space_restore(adrspc, safe_point);

	if (!fork_addr_space_is_shared(adrspc)) {
		fork_addr_space_delete(task_self());
	}
}

struct addr_space *fork_addr_space_create(struct addr_space *parent) { 
	struct addr_space *adrspc;

	adrspc = sysmalloc(sizeof(*adrspc));
	memset(adrspc, 0, sizeof(*adrspc));

	adrspc->parent_thread = thread_self();
	if (parent) {
		adrspc->parent_addr_space = parent;
		parent->child_count++;
	}

	return adrspc;
}

void fork_addr_space_store(struct addr_space *adrspc) { 
	struct task *tk = task_self();

	fork_user_stack_store(&adrspc->stack_space, adrspc->parent_thread);
	fork_heap_store(&adrspc->heap_space, tk);
	fork_static_store(&adrspc->static_space, tk);
}

void fork_addr_space_restore(struct addr_space *adrspc, void *stack_safe_point) { 
	struct task *tk = task_self();

	fork_user_stack_restore(&adrspc->stack_space, adrspc->parent_thread, stack_safe_point);
	fork_heap_restore(&adrspc->heap_space, tk);
	fork_static_restore(&adrspc->static_space, tk);
}

static void fork_addr_space_child_del(struct addr_space *child) {
	struct addr_space *parent;

	assert(child->child_count == 0, "%s: deleting address space with childs is NIY", __func__);
	
	parent = child->parent_addr_space;
	if (!parent) {
		return;
	}

	/* removing child from parent */
	parent->child_count--;

	/* reassigning child's childs to parent */
	parent->child_count += child->child_count;
}

static void fork_addr_space_init(const struct task *task, void *space) {
	struct addr_space **adrspc_p = space;

	*adrspc_p = NULL;
}

static void fork_addr_space_deinit(const struct task *task) {
	assert(task == task_self());
	fork_addr_space_delete(task_self());
}

TASK_RESOURCE_DECLARE(static, 
		fork_addr_space, 
		struct addr_space *, 
	.init = fork_addr_space_init,
	.deinit = fork_addr_space_deinit,
);

struct addr_space *fork_addr_space_get(const struct task *task) {
	return *((struct addr_space **) task_resource(task, &fork_addr_space));
}

void fork_addr_space_set(struct task *tk, struct addr_space *adrspc) {
	struct addr_space **adrspc_p;
	adrspc_p = task_resource(tk, &fork_addr_space);
	*adrspc_p = adrspc; 
}

void fork_addr_space_delete(struct task *task) {
	struct addr_space *adrspc;
	adrspc = fork_addr_space_get(task);

	if (!adrspc)
		return;

	fork_user_stack_cleanup(&adrspc->stack_space);
	fork_heap_cleanup(&adrspc->heap_space);
	fork_static_cleanup(&adrspc->static_space);

	fork_addr_space_child_del(adrspc);
	sysfree(adrspc);
	
	fork_addr_space_set(task, NULL);
}
