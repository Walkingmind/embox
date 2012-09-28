#include <embox/cmd.h>
#include <stdio.h>
#include <vesa.h>
#include <asm/io.h>

#define	VGA_MISC_WRITE		0x3C2
#define	VGA_MISC_READ		0x3CC

EMBOX_CMD(main);

int main (int argc, char ** argv) {
	dump_state();
	set_text_mode(argc > 1);
	demo_graphics();
	font512();
	return 0;
}
