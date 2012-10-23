/*
 * test_app.c
 *
 *  Created on: 18.10.2012
 *      Author: alexandr
 */

#include <xwnd/xwnd.h>
#include <xwnd/test_app.h>
#include <drivers/vesa.h>

static struct xwnd_bmp_image * img;
static struct xwnd_application * xapp;

static void on_creat (struct xwnd_event * ev) {
	img = xwnd_bmp_load("test2.bmp");
}

static void on_draw (struct xwnd_event * ev) {
	xwnd_bmp_draw(img);
}

static void on_quit (struct xwnd_event * ev) {
	xwnd_bmp_unload(img);
	vesa_clear_screen();
}

static void on_key (struct xwnd_event * ev) {
	xwnd_draw_window(xapp->wnd);
}

void * test_app_main (void * args) {
	xapp = (struct xwnd_application *) args;
	xwnd_app_set_event_handle(xapp, XWND_EV_CREAT, on_creat);
	xwnd_app_set_event_handle(xapp, XWND_EV_DRAW, on_draw);
	xwnd_app_set_event_handle(xapp, XWND_EV_QUIT, on_quit);
	xwnd_app_set_event_handle(xapp, XWND_EV_KBD, on_key);
	xwnd_app_main_loop(xapp);
	return NULL;
}
