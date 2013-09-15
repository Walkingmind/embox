/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    11.03.2013
 */

#ifndef CONSOLE_FBCON_H_
#define CONSOLE_FBCON_H_

#include <kernel/event.h>
#include <drivers/video/vesa_modes.h>
#include <drivers/console/mpx.h>
#include <drivers/video_term.h>
#include <kernel/task/io_sync.h>

#define FBCON_INPB 16

struct fbcon_displ_data {
	const struct font_desc *font;
	int fg_color;
	int bg_color;
	int cur_color;
};

struct fbcon {
	struct vc vc_this;

	struct vterm_video vterm_video;
	struct vterm vterm;

	struct fbcon_displ_data *fbcon_disdata;

	struct video_resbpp resbpp;
	struct io_sync ios;

};

extern volatile struct fbcon *vc_fbcon_cur;

extern int iodev_vc_init(struct tty *tty);

#endif /* CONSOLE_FBCON_H_ */

