/**
 * @file
 *
 * @date 09.10.2010
 * @author Anton Bondarev
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <types.h>

#define   DURATION_MIN          10        // [mS]
#define   FREQUENCY_MIN         220       // [Hz]
#define   FREQUENCY_MAX         14080     // [Hz]
#define   SAMPLEWORD            uint32_t
#define   SAMPLETONENO          16
#define   SAMPLEWORDBITS        (sizeof(SAMPLEWORD) * 8)
#define   SAMPLEWORDS           8

/* next samplebuffer, called when needed by framework */
typedef SAMPLEWORD *(*sound_handler_t)(void); 

/* start playing sound with initial buffers
 * @param ms = 0: continuous playing, stops only at explicit stop 
 * @param ms != 0: playing specified time */
void sound_start_play(uint32_t freq, useconds_t ms, 
	SAMPLEWORD *buff, SAMPLEWORD *next_buff, sound_handler_t sound_hnd);

/* stop playing anything */
void sound_stop_play(void);

#endif /* SOUND_H_ */
