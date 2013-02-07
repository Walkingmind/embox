/**
 * @file
 * @brief
 *
 * @date 26.12.2012
 * @author Anton Bulychev
 */

#ifndef KERNEL_PERCPU_H_
#define KERNEL_PERCPU_H_

#include <types.h>

#include <kernel/cpu.h>

#ifdef SMP

extern char _percpu_vma, _percpu_len;

#define __PERCPU__     __attribute__((section(".percpu")))
#define __PERCPU_START ((char *) &_percpu_vma)
#define __PERCPU_LEN   ((size_t) &_percpu_len)

#define __PERCPU_VAR_PTR(name) \
		((typeof(&name)) (((char *) &name) + (cpu_get_id() * __PERCPU_LEN)))

#else

#define __PERCPU__

#define __PERCPU_VAR_PTR(name) \
		(&name)

#endif /* SMP */

#define percpu_get(name) \
		(__PERCPU_VAR_PTR(name))

#define percpu_set(name, val) \
		do { *(__PERCPU_VAR_PTR(name)) = val; } while (0)

#endif /* KERNEL_PERCPU_H_ */
