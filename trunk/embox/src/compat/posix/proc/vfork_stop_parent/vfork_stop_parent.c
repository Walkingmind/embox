/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    14.05.2014
 */

#include <mem/sysmalloc.h>
#include <hal/ptrace.h>
#include <hal/vfork.h>
#include <kernel/panic.h>
#include <kernel/sched.h>
#include <kernel/task.h>
#include <kernel/task/resource/task_vfork.h>

#define VFORK_CTX_STACK_LEN 0x1000
struct vfork_ctx {
	char stack[VFORK_CTX_STACK_LEN] __attribute__((aligned(4)));
};

static void vfork_parent_signal_handler(int sig, siginfo_t *siginfo, void *context) {
	struct task_vfork *task_vfork = task_resource_vfork(task_self());
	task_vfork->parent_holded = false;
}

static void *vfork_child_task(void *arg) {
	struct pt_regs *ptregs = arg;

	ptregs_retcode_jmp(ptregs, 0);

	panic("vfork_child_task returning");
}

static void vfork_wait_signal_store(struct sigaction *ochildsa,
	       	struct sigaction *ocontsa) {
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = vfork_parent_signal_handler;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGCHLD, &sa, ochildsa);
	sigaction(SIGCONT, &sa, ocontsa);
}

static void vfork_wait_signal_restore(const struct sigaction *ochildsa,
	       	const struct sigaction *ocontsa) {
	sigaction(SIGCHLD, ochildsa, NULL);
	sigaction(SIGCONT, ocontsa, NULL);
}

static void vfork_waiting(void) {
	struct sigaction ochildsa, ocontsa;
	struct task *child;
	struct task_vfork *task_vfork;
	struct context tmp;

	task_vfork = task_resource_vfork(task_self());
	child = task_table_get(task_vfork->child_pid);

	vfork_wait_signal_store(&ochildsa, &ocontsa);
	{
		task_vfork->parent_holded = true;
		task_start(child, vfork_child_task, &task_vfork->ptregs);
		while (SCHED_WAIT(!task_vfork->parent_holded));
	}
	vfork_wait_signal_restore(&ochildsa, &ocontsa);

	context_switch(&tmp, &task_vfork->ctx);
	
	panic("vfork_waiting returning");
}

int vfork_child_start(struct task *child) {
	struct vfork_ctx *vfctx;
	struct task_vfork *task_vfork;
	struct context chld_ctx;
	
	vfctx = sysmalloc(sizeof(*vfctx));
	if (!vfctx) {
		return -EAGAIN;
	}

	task_vfork = task_resource_vfork(task_self());
	task_vfork->child_pid = child->tsk_id;
	task_vfork->vfork_ctx = vfctx;

	context_init(&chld_ctx, true);
	context_set_entry(&chld_ctx, vfork_waiting);
	context_set_stack(&chld_ctx, vfctx->stack + sizeof(vfctx->stack));
	context_switch(&task_vfork->ctx, &chld_ctx);

	/* current stack is broken, can't reach any old data */
	task_vfork = task_resource_vfork(task_self());
	
	sysfree(task_vfork->vfork_ctx);
	
	ptregs_retcode_jmp(&task_vfork->ptregs, task_vfork->child_pid);

	panic("vfork_child_start returning");
	return -1;
}
