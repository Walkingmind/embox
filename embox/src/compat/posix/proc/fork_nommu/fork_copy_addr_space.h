/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    04.06.2014
 */

#ifndef FORK_COPY_ADDR_SPACE_H_
#define FORK_COPY_ADDR_SPACE_H_

#include <hal/stack.h>
#include <sys/types.h>
#include <util/dlist.h>
#include <kernel/task.h>

struct stack_space {
	void *user_stack;
	size_t user_stack_sz;
}; 

struct heap_space {
	void *heap;
	size_t heap_sz;

	struct dlist_head store_space;
};

struct static_space {
	void *bss_store;
	void *data_store;
};

struct addr_space { 
	struct addr_space *parent_addr_space;
	unsigned int child_count;

	struct pt_regs *pt_entry;

	struct thread *parent_thread;

	struct stack_space stack_space;
	struct heap_space heap_space;
	struct static_space static_space;
};

extern void fork_addr_space_prepare_switch(void); 
extern void fork_addr_space_finish_switch(void *safe_point);

#define __ADDR_SPACE_PREPARE_SWITCH() \
	fork_addr_space_prepare_switch()

#define __ADDR_SPACE_FINISH_SWITCH() \
	fork_addr_space_finish_switch(stack_ptr())

/* Stack */
struct thread;
extern void fork_user_stack_store(struct stack_space *stspc, struct thread *thread);
extern void fork_user_stack_restore(struct stack_space *stspc, struct thread *th, void *stack_safe_point);
extern void fork_user_stack_cleanup(struct stack_space *stspc);

/* Heap */
extern void fork_heap_store(struct heap_space *hpspc, struct task *tk);
extern void fork_heap_restore(struct heap_space *hpspc, struct task *tk);
extern void fork_heap_cleanup(struct heap_space *hpspc);

/* Static */
extern void fork_static_store(struct static_space *sspc, struct task *tk);
extern void fork_static_restore(struct static_space *sspc, struct task *tk);
extern void fork_static_cleanup(struct static_space *sspc);

#endif /* FORK_COPY_ADDR_SPACE_H_ */
