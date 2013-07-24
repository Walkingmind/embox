/**
 * @file
 * @brief
 *
 * @date 26.12.12
 * @author Anton Bulychev
 * @author Ilia Vaprol
 */

#ifndef KERNEL_CPU_H_
#define KERNEL_CPU_H_

#include <module/embox/kernel/cpu/cpu_api.h>

#ifndef __ASSEMBLER__

#include <sys/types.h>

struct thread;

/**
 * Common CPU functions
 */
extern void cpu_init(unsigned int cpu_id, struct thread *idle);
extern void cpu_bind(unsigned int cpu_id, struct thread *t);
extern struct thread * cpu_get_idle(unsigned int cpu_id);
extern clock_t cpu_get_started(unsigned int cpu_id);

/**
 * Get CPU statistic
 */
extern clock_t cpu_get_total_time(unsigned int cpu_id);
extern clock_t cpu_get_idle_time(unsigned int cpu_id);

#endif /* !__ASSEMBLER__ */

#endif /* !KERNEL_CPU_H_ */
