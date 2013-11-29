/**
 * @file
 *
 * @date Oct 24, 2013
 * @author: Anton Bondarev
 */

#ifndef IDESC_EVENT_H_
#define IDESC_EVENT_H_

#include <kernel/sched/waitq.h>

/**
 * The same as struct wait_link link but have poll flags
 */
struct idesc_wait_link {
	int iwq_masks;
	struct wait_link link;
};

/**
 * @brief Prepare link to wait on idesc
 *
 * @param idesc Idesc to wait event on
 * @param wl Idesc_wait_link to prepare
 * @param mask Mask of events
 */
extern int idesc_wait_prepare(struct idesc *idesc, struct idesc_wait_link *wl,
		int mask);

/**
 * @brief Wait for events of specified mask occurred on idesc
 *
 * @param wl Prepared idesc_wait_link
 * @param timeout Timeout of waiting specified in ms (?). Can be SCHED_TIMEOUT_INFINITE.
 *
 * @return -EAGAIN if descriptor has O_NONBLOCK set
 * @return -ETIMEDOUT if timeout expired during waiting
 * @return -EINTR if was interrupted
 * @return Non-negative if event occured
 */
extern int idesc_wait(struct idesc *idesc, unsigned int timeout);


/**
 * @brief Clean idesc_wait_link
 *
 * @param idesc - index descriptor on which thread waited
 * @param wl wait link which was prepared by idesc_wait_prepare()
 */
extern void idesc_wait_cleanup(struct idesc *idesc, struct idesc_wait_link *wl);

/**
 * Wake all thread which wait this descriptor
 *
 * @param idesc on which something happened
 */
extern int idesc_notify(struct idesc * idesc, int mask);


#endif /* IDESC_EVENT_H_ */
