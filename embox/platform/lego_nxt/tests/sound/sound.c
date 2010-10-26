/**
 * @file
 *
 * @date 09.10.2010
 * @author Anton Bondarev
 */

#include <types.h>
#include <embox/test.h>
#include <drivers/sound.h>
#include <kernel/irq.h>
#include <drivers/at91sam7s256.h>
#define   SOUNDVOLUMESTEPS      4

EMBOX_TEST(run_sound);

static const uint32_t patterns[SOUNDVOLUMESTEPS + 1][SAMPLETONENO] =
{
  {
    0xF0F0F0F0,0xF0F0F0F0, // Step 0 = silence
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0
  },
  {
    0xF0F0F0F0,0xF0F0F0F0, // Step 1 = 1/512
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F8,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0
  },
  {
    0xF0F0F0F0,0xF0F0F0F0, // Step 2 = 0,+3,+4,+3,0,-3,-4,-3
    0xF0F0F0F0,0xF0F8F8F8,
    0xF0F0F8F8,0xF8F8F0F0,
    0xF8F8F8F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0F0F0F0,
    0xF0F0F0F0,0xF0E0E0E0,
    0xF0F0E0E0,0xE0E0F0F0,
    0xE0E0E0F0,0xF0F0F0F0
  },
  {
    0xF0F0F0F0,0xF0F0F0F0, // Step 3 = 0,+10,+14,+10,0,-10,-14,-10
    0xF8F8F8F8,0xF8F8FCFC,
    0xF8F8FCFC,0xFCFCFCFC,
    0xFCFCF8F8,0xF8F8F8F8,
    0xF0F0F0F0,0xF0F0F0F0,
    0xE0E0E0E0,0xE0E0C0C0,
    0xE0E0C0C0,0xC0C0C0C0,
    0xC0C0E0E0,0xE0E0E0E0
  },
  {
    0xF0F0F0F0,0xF0F0F0F0, // Step 4 = 0,+22,+32,+22,0,-22,-32,-22
    0xFCFCFCFC,0xFCFCFDFD,
    0xFFFFFFFF,0xFFFFFFFF,
    0xFDFDFCFC,0xFCFCFCFC,
    0xF0F0F0F0,0xF0F0F0F0,
    0xC0C0C0C0,0xC0C08080,
    0x00000000,0x00000000,
    0x8080C0C0,0xC0C0C0C0
  }
};

extern void sound_next_sample(uint32_t, uint32_t, 
		    uint32_t *, uint32_t, uint32_t *);

enum FREQ_TONE  {
		TONE_C = 262,
		TONE_D = 294,
		TONE_E = 330,
		TONE_F = 349,
		TONE_G = 392,
		TONE_A = 440,
		TONE_H = 494
};
static uint32_t freq_tone[2][3] = {
	{TONE_C, TONE_E, TONE_G},
	{TONE_C, TONE_E, TONE_F}
};

#define DURETION 500

static uint32_t bank_num = 0;

void switch_bank(void) {
	bank_num ++;
}

irq_return_t sound_interrupt (int irq_num, void *dev_id) {
	static int i = 0;
	static uint32_t f = 0;
	static int time = 0;
	if (++i == 5) {
		if (time ++ == 10) {
			time = 0;
			if (3 == f ++) {
				f = 0;
			}
		}

		i = 0;
	}

	sound_next_sample(freq_tone[bank_num & 0x1][f], DURETION, (uint32_t *)patterns[i], DURETION, (uint32_t *)patterns[i+1]);
	return IRQ_HANDLED;
}

static int run_sound(void) {
	irq_attach((irq_nr_t) AT91C_ID_SSC, 
		(irq_handler_t) &sound_interrupt, 0, NULL, "at91 PIT"); 
	sound_next_sample(220, DURETION, (uint32_t *)patterns[0], DURETION, (uint32_t *)patterns[1]);
	return 0;
}
