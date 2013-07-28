/**
 * @file
 *
 * @date 09.10.10
 * @author Anton Bondarev
 * @author Darya Dzendzik
 */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <kernel/time/ktime.h>
#include <kernel/irq.h>
#include <drivers/sound.h>
#include <drivers/at91sam7s256.h>
#include <hal/reg.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(sound_init);

static sound_handler_t current_handler = NULL;

static irq_return_t sound_interrupt(unsigned int irq_num, void *dev_id) {
	sampleword_t *next_buff;
	if (current_handler == NULL) { /*inefficient */
		return IRQ_HANDLED;
	}
	next_buff = (*current_handler)();
	REG_STORE(AT91C_SSC_TNPR, (uint32_t) next_buff);
	REG_STORE(AT91C_SSC_TNCR, SAMPLETONENO);

	return IRQ_HANDLED;
}

void sound_stop_play(void) {
	REG_STORE(AT91C_SSC_PTCR, AT91C_PDC_TXTDIS);
}

static int sound_init(void) {
	int res = 0;
	res = irq_attach(AT91C_ID_SSC, sound_interrupt, 0, NULL,
			"Sound Buffer Transfer End");
	// TODO error handling?

	/* Enable MCK clock   */
	REG_STORE(AT91C_PMC_PCER, (1L << AT91C_ID_SSC));
	/* Disable TD on PA17  */ //???
	//REG_STORE(AT91C_PIOA_PER, AT91C_PA17_TD);
	REG_STORE(AT91C_PIOA_PDR, AT91C_PA17_TD);

	REG_STORE(AT91C_SSC_CR, AT91C_SSC_SWRST);
	REG_STORE(AT91C_SSC_TCMR, AT91C_SSC_CKS_DIV +
		AT91C_SSC_CKO_CONTINOUS + AT91C_SSC_START_CONTINOUS);

	REG_STORE(AT91C_SSC_TFMR, (SAMPLEWORDBITS - 1) +
		((SAMPLEWORDS & 0xF) << 8) + AT91C_SSC_MSBF);
	/* TX enable */
	REG_STORE(AT91C_SSC_CR, AT91C_SSC_TXEN);
	REG_STORE(AT91C_SSC_IER, AT91C_SSC_ENDTX);
	sound_stop_play();
	return res;
}

void sound_start_play(uint32_t freq, useconds_t ms,
	sample_t buff, sample_t next_buff, sound_handler_t sound_hnd) {

	current_handler = sound_hnd;

	if (freq) {
		if (freq < FREQUENCY_MIN) {
			freq = FREQUENCY_MIN;
		}
		if (freq > FREQUENCY_MAX) {
			freq = FREQUENCY_MAX;
		}
	} else {
		freq = 1000;
	}

	REG_STORE(AT91C_SSC_CMR, ((CONFIG_SYS_CLOCK / (2L * 512L)) / freq) + 1L);

	REG_STORE(AT91C_SSC_TNPR, (uint32_t) next_buff);
	REG_STORE(AT91C_SSC_TNCR, SAMPLETONENO);

	REG_STORE(AT91C_SSC_TPR, (uint32_t) buff);
	REG_STORE(AT91C_SSC_TCR, SAMPLETONENO);

	REG_STORE(AT91C_SSC_PTCR, AT91C_PDC_TXTEN);

	if (ms != 0) {
		ksleep(ms);
		sound_stop_play();
	}
}
