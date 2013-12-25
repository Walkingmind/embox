/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    11.03.2013
 */

#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <drivers/input/keymap.h>
#include <drivers/keyboard.h>
#include <drivers/console/mpx.h>
#include <drivers/console/fbcon.h>
#include <drivers/video/fb.h>
#include <drivers/video/font.h>
#include <drivers/tty.h>
#include <fs/index_descriptor.h>
#include <kernel/sched/sched_lock.h>
#include <kernel/task.h>
#include <mem/objalloc.h>
#include <cmd/shell.h>
#include <embox/unit.h>

#include <fcntl.h>

EMBOX_UNIT_INIT(fbcon_init);

static void inpevent(struct vc *vc, struct input_event *ev);
static void visd(struct vc *vc, struct fb_info *fbinfo);
static void devisn(struct vc *vc);

static void fbcon_vterm_clear_rows(struct vterm_video *t, short row, unsigned short count);

const struct vc_callbacks thiscbs = {
	.handle_input_event = inpevent,
	.visualized = visd,
	.schedule_devisualization = devisn,
};

static struct fbcon fbcons[VC_MPX_N];

static struct fbcon_displ_data fbcon_displ_data = {
	.font = &font_vga_8x16,
	.fg_color = 0x0000,
	.bg_color = 0xFFFF,
	.cur_color = 0x00F0,
};

extern int vterm_input(struct vterm *vt, struct input_event *event);

static void inpevent(struct vc *vc, struct input_event *ev) {
	struct fbcon *fbcon = (struct fbcon *) vc;
	
	if (ev->devtype != INPUT_DEV_KBD) {
		return;
	}

	if (!(ev->type & KEY_PRESSED)) {
		return;
	}

	vterm_input(&fbcon->vterm, ev);
}

static void vterm_reinit(struct vterm_video *t, int x, int y);

static struct fbcon *fbcon_current;

static void visd(struct vc *vc, struct fb_info *fbinfo) {
	struct fbcon *fbcon = (struct fbcon *) vc;

	fbcon->resbpp.x = fbinfo->var.xres;
	fbcon->resbpp.y = fbinfo->var.yres;
	fbcon->resbpp.bpp = fbinfo->var.bits_per_pixel;

	vterm_reinit(&fbcon->vterm_video, fbcon->resbpp.x / fbcon_displ_data.font->width,
		       	fbcon->resbpp.y / fbcon_displ_data.font->height);

	fbcon_vterm_clear_rows(&fbcon->vterm_video, 0, fbcon->vterm_video.height);

	fbcon_current = fbcon;

}

static void devisn(struct vc *vc) {

	fbcon_current = NULL;

	mpx_devisualized(vc);
}

static inline struct fbcon *data2fbcon(struct idesc *idesc) {
	return member_cast_out(idesc, struct fbcon, idesc);
}

static int fbcon_idesc_read(struct idesc *idesc, void *buf, size_t nbyte) {
	struct fbcon *fbcon = data2fbcon(idesc);

	return tty_read(&fbcon->vterm.tty, buf, nbyte);
}

static int fbcon_idesc_write(struct idesc *idesc, const void *buf, size_t nbyte) {
	struct fbcon *fbcon = data2fbcon(idesc);
	char *cbuf = (char *) buf;

	while (nbyte--) {
		vterm_putc(&fbcon->vterm, *cbuf++);
	}

	return (int) cbuf - (int) buf;
}

static int fbcon_idesc_ioctl(struct idesc *idesc, int request, void *data) {
	struct fbcon *fbcon = data2fbcon(idesc);

	return tty_ioctl(&(fbcon->vterm.tty), request, data);
}

static int fbcon_idesc_fstat(struct idesc *idesc, void *buff) {
       struct stat *st = buff;

       st->st_mode = S_IFCHR;

       return 0;

}

static int fbcon_idesc_close(struct idesc *idesc) {
	return 0;
}

static const struct idesc_ops fbcon_idesc_ops = {
	.read  = fbcon_idesc_read,
	.write = fbcon_idesc_write,
	.close = fbcon_idesc_close,
	.ioctl = fbcon_idesc_ioctl,
	.fstat = fbcon_idesc_fstat,
};

static void *run(void *data) {
	int fd;
	const struct shell *sh;
	struct fbcon *fbcon = (struct fbcon *) data;

	sh = shell_lookup("tish");

	if (!sh) {
		return NULL;
	}

	close(0);
	close(1);
	close(2);

	idesc_init(&fbcon->idesc, &fbcon_idesc_ops, FS_MAY_READ | FS_MAY_WRITE);
	fd = index_descriptor_add(&fbcon->idesc);
	fbcon->vterm.tty.idesc = &fbcon->idesc;

	assert(fd == 0);

	dup2(fd, 1);
	/*dup2(fd, 2);*/

	shell_exec(sh, "login");

	return NULL;

}

static void fbcon_vterm_init(struct vterm_video *t) {
}

static int prev_x = -1, prev_y = -1;

static void fbcon_vterm_cursor(struct vterm_video *t, unsigned short x, unsigned short y) {
	struct fbcon *fbcon = member_cast_out(t, struct fbcon, vterm_video);
	struct fbcon_displ_data *data = fbcon->fbcon_disdata;
	struct fb_cursor cursor;
	struct fb_info *fb;

	assert(data != NULL);

	assert(data->font != NULL);

	cursor.enable = 1;
	cursor.rop = ROP_XOR;
	cursor.image.width = data->font->width;
	cursor.image.height = data->font->height;
	cursor.image.fg_color = data->cur_color;

	cursor.hot.x = prev_x;
	cursor.hot.y = prev_y;

	fb = fbcon->vc_this.fb;
	if (!fb) {
		return;
	}
	assert(fb->ops != NULL);
	assert(fb->ops->fb_cursor != NULL);

	if (prev_y >= 0) {
		fb->ops->fb_cursor(fb, &cursor);
	}

	prev_x = cursor.hot.x = x;
	prev_y = cursor.hot.y = y;

	fb->ops->fb_cursor(fb, &cursor);

}

static void fbcon_vterm_putc(struct vterm_video *t, char ch, unsigned short x, unsigned short y) {
	struct fbcon *fbcon = member_cast_out(t, struct fbcon, vterm_video);
	struct fb_image symbol;
	struct fbcon_displ_data *data = fbcon->fbcon_disdata;
	struct fb_info *fb;

	assert(data != NULL);

	assert(data->font != NULL);

	symbol.dx = x * data->font->width;
	symbol.dy = y * data->font->height;
	symbol.width = data->font->width;
	symbol.height = data->font->height;
	symbol.fg_color = data->fg_color;
	symbol.bg_color = data->bg_color;
	symbol.depth = 1;
	symbol.data = data->font->data + (unsigned char)ch * data->font->height * data->font->width / 8;

	fb = fbcon->vc_this.fb;
	if (!fb) {
		return;
	}

	if (prev_x == x && prev_y == y) {
		prev_x = prev_y = -1;
	}

	assert(fb->ops != NULL);
	assert(fb->ops->fb_imageblit != NULL);
	fb->ops->fb_imageblit(fb, &symbol);
}


static void fbcon_vterm_clear_rows(struct vterm_video *t, short row, unsigned short count){
	struct fbcon *fbcon = member_cast_out(t, struct fbcon, vterm_video);
	struct fb_fillrect rect;
	struct fbcon_displ_data *data = fbcon->fbcon_disdata;
	struct fb_info *fb;

	assert(data != NULL);

	assert(data->font != NULL);

	rect.dx = 0;
	rect.dy = row * data->font->height;
	rect.width = t->width * data->font->width;
	rect.height = count * data->font->height;
	rect.color = data->bg_color;
	rect.rop = ROP_COPY;

	fb = fbcon->vc_this.fb;
	if (!fb) {
		return;
	}
	assert(fb->ops != NULL);
	assert(fb->ops->fb_fillrect != NULL);
	fb->ops->fb_fillrect(fb, &rect);

	if (prev_y >= row && prev_y < row + count) {
		prev_y = prev_x = -1;
	}
}

static void fbcon_vterm_copy_rows(struct vterm_video *t,
		unsigned short to, unsigned short from, short nrows) {
	struct fbcon *fbcon = member_cast_out(t, struct fbcon, vterm_video);
	struct fb_copyarea area;
	struct fbcon_displ_data *data = fbcon->fbcon_disdata;
	struct fb_info *fb;

	assert(data != NULL);

	assert(data->font != NULL);

	area.dx = 0;
	area.dy = to * data->font->height;
	area.width = t->width * data->font->width;
	area.height = nrows * data->font->height;
	area.sx = 0;
	area.sy = from * data->font->height;

	fb = fbcon->vc_this.fb;
	if (!fb) {
		return;
	}

	assert(fb->ops != NULL);
	assert(fb->ops->fb_copyarea != NULL);
	fb->ops->fb_copyarea(fb, &area);

	if (prev_y >= from && prev_y < from + nrows) {
		prev_y -= from - to;
	}
}

static const struct vterm_video_ops fbcon_vterm_video_ops = {
		.init = &fbcon_vterm_init,
		.cursor = &fbcon_vterm_cursor,
		.putc = &fbcon_vterm_putc,
		.clear_rows = &fbcon_vterm_clear_rows,
		.copy_rows = &fbcon_vterm_copy_rows
};

extern int COLS __attribute__((weak)), LINES __attribute__((weak));

static void vterm_reinit(struct vterm_video *t, int x, int y) {
	int *pCOLS = &COLS, *pLINES = &LINES;

	t->width = x;
	t->height = y;

	if (pCOLS) {
		*pCOLS = x;
	}

	if (pLINES) {
		*pLINES = y;
	}
}

static int make_task(int i, char innewtask) {
	struct fbcon *fbcon = &fbcons[i];
	int ret;
	
	fbcon->vc_this.callbacks = &thiscbs;
	fbcon->fbcon_disdata = &fbcon_displ_data;

	vterm_video_init(&fbcon->vterm_video, &fbcon_vterm_video_ops,
			0, 0);

	vterm_init(&fbcon->vterm, &fbcon->vterm_video, NULL);

	if (0 > (ret = mpx_register_vc(&fbcon->vc_this))) {
		return ret;
	}

	if (innewtask) {
		return new_task("vc", run, &fbcons[i]);
	}

	run(fbcon);

	return 0;
}

#include <drivers/diag.h>

static void fbcon_diag_putc(const struct diag *diag, char ch) {

	if (!fbcon_current) {
		return;
	}

	
	vterm_putc(&fbcon_current->vterm, ch);
}

DIAG_OPS_DECLARE(
	.putc = fbcon_diag_putc,
);

static int fbcon_init(void) {

	make_task(0, true);
	make_task(1, true);

	return diag_setup(&DIAG_IMPL_NAME(__EMBUILD_MOD__));
}
