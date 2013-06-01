/**
 * @file
 * @brief
 *
 * @date 05.02.13
 * @author Ilia Vaprol
 */

#include <drivers/diag.h>
#include <asm/io.h>
#include <drivers/video/vga.h>
#include <drivers/iodev.h>
#include <drivers/iodev_diag.h>
#include <drivers/video_term.h>
#include <util/member.h>
#include <string.h>

/* The video memory address. */
#define VIDEO          0xB8000

static void diag_vterm_init(struct vterm_video *t) {
	/**
	 * mode 3h (80x25 text mode)
	 * 0x67 => 01100111
	 * +---+---+---+--+--+----+---+
	 * |7  |6  |5 4|3 |2 |1   |0  |
	 * |1  |1  |1 0|0 |1 |1   |0  |
	 * |VSP|HSP|   |CS|CS|ERAM|IOS|
	 * 7,6 - 480 lines
	 * 3,2 - 28,322 MHZ Clock
	 * 1 - Enable Ram
	 * 0 - Map 0x3d4 to 0x3b4
	 */
	out16(0x67, VGA_MISC_WRITE);
}

static void diag_vterm_cursor(struct vterm_video *t, unsigned short x, unsigned short y) {
	unsigned int pos;

	pos = x + y * t->width;
	out16((pos & 0xff00) | 0x0e, VGA_CRTC_INDEX);
	out16((pos << 8) | 0x0f, VGA_CRTC_INDEX);
}

static void diag_vterm_putc(struct vterm_video *t, char ch, unsigned short x, unsigned short y) {
	struct diag_vterm_data *data = &member_cast_out(t, struct vga_vterm_video, video)->data;

	data->video[x + y * t->width] = (vchar_t) {.c = ch, .a = data->attr};
}


static void diag_vterm_clear_rows(struct vterm_video *t, short row, unsigned short count){
	struct diag_vterm_data *data = &member_cast_out(t, struct vga_vterm_video, video)->data;

	for (int i = row * t->width; i < (row + count) * t->width; ++i){
		data->video[i] = (vchar_t) {.c = ' ', .a = data->attr};
	}
}

static void diag_vterm_copy_rows(struct vterm_video *t,
		unsigned short to, unsigned short from, short nrows) {
	struct diag_vterm_data *data = &member_cast_out(t, struct vga_vterm_video, video)->data;

	memmove(&data->video[to * t->width],
			&data->video[from * t->width],
			sizeof(data->video[0]) * nrows * t->width);
}

static const struct vterm_video_ops diag_tty_ops = {
		.init = &diag_vterm_init,
		.cursor = &diag_vterm_cursor,
		.putc = &diag_vterm_putc,
		.clear_rows = &diag_vterm_clear_rows,
		.copy_rows = &diag_vterm_copy_rows
};

static int iodev_diag_init(void) {
	return 0;
}

static const struct iodev_ops iodev_diag_ops_struct = {
	.init = &iodev_diag_init,
	.getc = NULL,//&diag_getc,
	.putc = &diag_putc,
	.kbhit = NULL //&diag_kbhit,
};

const struct iodev_ops *const iodev_diag_ops = &iodev_diag_ops_struct;
struct vga_vterm_video diag_vga = {
		.video = {
				.ops = &diag_tty_ops,
				.width = 80,
				.height = 24
		},
		.data = { .attr = 0x7, .video = (vchar_t *) VIDEO }
};
