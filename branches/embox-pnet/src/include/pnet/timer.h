/**
 * @file
 *
 * @brief
 *
 * @date 28.04.2013
 * @author Alexander Kalmuk
 */

#ifndef PNET_TIMER_H_
#define PNET_TIMER_H_

#include <pnet/types.h>

extern void pnet_timer_hnd_stopped(struct pnet_pack *pack);

extern void pnet_timer_hnd_enter(struct pnet_pack *pack);

extern void pnet_timer_hnd_leave(struct pnet_pack *pack);

#endif /* PNET_TIMER_H_ */
