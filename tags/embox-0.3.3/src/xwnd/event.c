/*
 * event.c
 *
 *  Created on: 18.10.2012
 *      Author: alexandr
 */

#include <stdlib.h>
#include <xwnd/event.h>
#include <xwnd/app_registry.h>
#include <kernel/thread/sync/sem.h>

int xwnd_app_send_event (int app_id, struct xwnd_event * event) {
	return xwnd_app_put_message (app_id, event, sizeof(struct xwnd_event));
}

int xwnd_app_send_quit_event (int app_id, int exit_status) {
	struct xwnd_event ev;
	ev.type = XWND_EV_QUIT;
	ev.info.quit.exit_status = exit_status;
	return xwnd_app_send_event(app_id, &ev);
}

int xwnd_app_send_kbd_event(int app_id, char key) {
	struct xwnd_event ev;
	ev.type = XWND_EV_KBD;
	ev.info.kbd.key = key;
	return xwnd_app_send_event(app_id, &ev);
}

int xwnd_app_send_sys_event(int app_id, enum xwnd_event_type event_type) {
	struct xwnd_event ev;
	ev.type = event_type;
	return xwnd_app_send_event(app_id, &ev);
}