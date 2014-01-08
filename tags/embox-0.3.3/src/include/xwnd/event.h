/*
 * event.h
 *
 *  Created on: 15.10.2012
 *      Author: alexandr
 */

#ifndef XWND_EVENT_H_
#define XWND_EVENT_H_

#include <kernel/thread/event.h>

enum xwnd_event_type {XWND_EV_CREAT, XWND_EV_SIGNALLED, XWND_EV_QUIT,
	XWND_EV_KBD, XWND_EV_DRAW, XWND_EV_MAX /*to be continued*/};
struct xwnd_kbd_event {
	char key; /*Oh, forgive me, mom*/
};
struct xwnd_mouse_event {
	int x;
	int y;
	int state;
};
struct xwnd_quit_event {
	int exit_status;
};
struct xwnd_sys_event {
};
union xwnd_event_info {
	struct xwnd_sys_event sys;
	struct xwnd_kbd_event kbd;
	struct xwnd_mouse_event mouse;
	struct xwnd_quit_event quit;
};
struct xwnd_event {
	enum xwnd_event_type type;
	struct event krnl_event;
	union xwnd_event_info info;
};

extern int xwnd_app_send_event (int app_id, struct xwnd_event * event);
extern int xwnd_app_send_quit_event (int app_id, int exit_status);
extern int xwnd_app_send_kbd_event(int app_id, char key);
extern int xwnd_app_send_sys_event(int app_id, enum xwnd_event_type event_type);


#endif /* XWND_EVENT_H_ */