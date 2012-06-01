/**
 * @file
 * @brief
 *
 * @date 16.09.11
 * @author Anton Kozlov
 */
#include <embox/unit.h>
#include <kernel/task.h>
#include <mem/objalloc.h>

#include "index_desc.h"


OBJALLOC_DEF(idx_res_pool, struct idx_desc, CONFIG_TASKS_RES_QUANTITY);

void res_init(struct task_resources *res) {
	for (int i = 0; i < CONFIG_TASKS_RES_QUANTITY; i++) {
		task_res_idx_set(res, i, NULL);
	}
}
#if 0
struct idx_desc *task_idx_desc_alloc(int type, void *data) {
	struct idx_desc *desc = objalloc(&idx_res_pool);
	desc->link_count = 0; 

	desc->data = data;
	return desc;
}
#endif
struct idx_desc *task_idx_desc_alloc(const struct task_res_ops *res_ops, void *data) {
	struct idx_desc *desc = objalloc(&idx_res_pool);
	desc->link_count = 0; 

	desc->res_ops = res_ops;
	desc->data = data;
	return desc;
}

void task_idx_desc_free(struct idx_desc *desc) {
	objfree(&idx_res_pool, desc);
}

int task_res_idx_alloc(struct task_resources *res, const struct task_res_ops *res_ops, void *data) {
	if(NULL == data) return -1;
	for (int i = 0; i < CONFIG_TASKS_RES_QUANTITY; i++) {
		if (!task_res_idx_is_binded(res, i)) {
			task_res_idx_set(res, i, task_idx_desc_alloc(res_ops, data));
			return i;
		}
	}
	return -1; 
}	

void task_res_idx_free(struct task_resources *res, int idx) {
	struct idx_desc *cidx = task_res_idx_get(res, idx);
	if (0 == task_idx_desc_link_count_add(cidx, -1)) {
		task_idx_desc_free(cidx);
	}
	task_res_idx_unbind(res, idx);
}


