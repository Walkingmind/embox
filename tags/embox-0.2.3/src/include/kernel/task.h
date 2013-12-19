/**
 * @file
 * @brief
 *
 * @date 17.04.11
 * @author Anton Bondarev
 */

#ifndef TASK_H_
#define TASK_H_

#include <fs/file.h>
#include <lib/list.h>
#include <kernel/task_resources.h>

struct task {
	struct task *parent;

	struct list_head children;
	struct list_head link;

	struct list_head threads;

	struct task_resources resources;

	int errno;
};

static inline struct task_resources *task_get_resources(struct task *task) {
	return &task->resources;
}
extern int task_create(struct task **new, struct task *parent);

extern struct task *task_self(void);

extern struct task *task_default_get(void);

extern int task_file_open(FILE *file, struct task_resources *res);

extern int task_idx_alloc(int type);
extern int task_idx_release(int idx);

extern int task_idx_to_type(int idx);

extern int task_idx_save(int idx, void *desc);

extern void * task_idx_to_desc(int idx);

static inline int task_valid_fd(int fd) {
	return 0 <= fd && fd <= CONFIG_TASKS_FILE_QUANTITY;
}

#endif /* TASK_H_ */