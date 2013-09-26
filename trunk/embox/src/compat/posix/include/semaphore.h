/**
 * @file
 *
 * @brief
 *
 * @date 26.09.2013
 * @author Vita Loginova
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <kernel/thread/sync/semaphore.h>

typedef struct sem sem_t

extern int    sem_close(sem_t *);
extern int    sem_destroy(sem_t *);
extern int    sem_getvalue(sem_t *restrict, int *restrict);
extern int    sem_init(sem_t *, int, unsigned);
extern sem_t *sem_open(const char *, int, ...);
extern int    sem_post(sem_t *);
extern int    sem_timedwait(sem_t *restrict, const struct timespec *restrict);
extern int    sem_trywait(sem_t *);
extern int    sem_unlink(const char *);
extern int    sem_wait(sem_t *);


#endif /* SEMAPHORE_H_ */
