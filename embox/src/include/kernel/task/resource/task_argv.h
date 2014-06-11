/**
 * @file
 *
 * @date Jun 11, 2014
 * @author: Anton Bondarev
 */

#ifndef TASK_ARGV_H_
#define TASK_ARGV_H_

struct task_argv;
extern struct task_argv *task_resource_argv(const struct task *task);

extern int task_resource_argv_argc(const struct task *task);
extern char **task_resource_argv_argv(const struct task *task);
#endif /* TASK_ARGV_H_ */
