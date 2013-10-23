/**
 * @file
 * @brief Current thread signal handling.
 *
 * @date 14.10.2013
 * @author Eldar Abusalimov
 */

#include <signal.h>

#include <kernel/task.h>
#include <kernel/thread.h>
#include <kernel/thread/signal.h>


void thread_signal_handle(void) {
	struct thread *thread = thread_self();
	struct task   *task   = thread->task;

	struct signal_data *sig_data = &thread->signal_data;
	struct sigaction *sig_table = task->sig_table;

	sighandler_t handler;
	int sig;

	while ((sig = sigrt_dequeue(&sig_data->sigrt_data)) ||
		(sig = sigstd_dequeue(&sig_data->sigstd_data))) {

		// TODO locks?
		handler = sig_table[sig].sa_handler;
		assert(handler && "there must be at least a fallback handler");

		handler(sig);
	}
}
