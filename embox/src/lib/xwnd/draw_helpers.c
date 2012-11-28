/**
 * @file
 * @brief XWnd drawing utilities
 *
 * @date Oct 10, 2012
 * @author Alexandr Chernakov
 */

#include <lib/xwnd/draw_helpers.h>
#include <drivers/vesa.h>


void xwnd_draw_pixel (const struct xwnd_window * wnd, unsigned x, unsigned y, unsigned c) {
	if (x < wnd->wd - 1 && y < wnd->ht - 1 && 
			wnd->x + x + 1>= 0 && wnd->x + x + 1< vesa_get_width() &&
			wnd->y + y + 1>= 0 && wnd->y + y + 1< vesa_get_height()) 
	{
		vesa_put_pixel(wnd->x + x + 1, wnd->y + y + 1, c);
	}
}

static void xwnd_draw_horiz_line (unsigned x, unsigned y, unsigned l, unsigned c) {
	int i;
	for (i = 0; i <= l; i++) {
		vesa_put_pixel(x + i, y, c);
	}
}

static void xwnd_draw_vert_line (unsigned x, unsigned y, unsigned l, unsigned c) {
	int i;
	for (i = 0; i <= l; i++) {
		vesa_put_pixel(x, y + i, c);
	}
}

void xwnd_draw_window (const struct xwnd_window * wnd) {
	xwnd_draw_vert_line  (wnd->x, wnd->y, wnd->ht, 2);
	xwnd_draw_horiz_line (wnd->x, wnd->y, wnd->wd, 2);
	xwnd_draw_vert_line  (wnd->x + wnd->wd, wnd->y, wnd->ht, 2);
	xwnd_draw_horiz_line (wnd->x, wnd->y + wnd->ht, wnd->wd, 2);
}

void xwnd_clear_window (const struct xwnd_window * wnd) {
	int x, y;
	for (y = wnd->y + 1; y < wnd->y + wnd->ht; y++) {
		for (x = wnd->x + 1; x < wnd->x + wnd->wd; x++) {
			vesa_put_pixel(x, y, 0);
		}
	}
}
