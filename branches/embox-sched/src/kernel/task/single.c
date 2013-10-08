/**
 * @file
 * @brief
 *
 * @date 31.08.11
 * @author Anton Kozlov
 */

#include <errno.h>
#include <kernel/task.h>
#include "common.h"

int new_task(const char *name, void *(*run)(void *), void *arg) {
	return -EPERM;
}

struct task *task_self(void) {
	/* Since there is only one task, actually it means --
	 * that task is kernel's.
	 */
	return task_kernel_task();
}

void __attribute__((noreturn)) task_exit(void *res) {
	while(1);
}

int task_notify_switch(struct thread *prev, struct thread *next) {
	return 0;
}

struct task *task_table_get(int n) {
	if(n < 0) {
		return NULL;
	}
	return task_kernel_task();
}

int task_table_get_first(int since) {
	return 0;
}
