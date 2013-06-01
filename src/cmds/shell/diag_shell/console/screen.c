/**
 * @file
 *
 * @date 28.02.09
 * @author Eldar Abusalimov
 */

#include "screen.h"
#include "cmdline.h"
#include <stddef.h>

SCREEN * screen_init(SCREEN *this, SCREEN_IO *io) {
	if (this == NULL || io == NULL) {
		return NULL;
	}

	if (terminal_init(this->terminal, io) == NULL) {
		return NULL;
	}

	this->running = false;
	return this;
}
