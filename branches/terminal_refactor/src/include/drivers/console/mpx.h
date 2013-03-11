/**
 * @file 
 * @brief 
 *
 * @author  Felix Sulima
 * @date    06.03.2013
 */

#ifndef CONSOLE_MPX_H_
#define CONSOLE_MPX_H_

#include <drivers/video/fb.h>
#include <drivers/input/input_dev.h>

#define VC_MPX_N 7

#define VC_FBUFLEN (1680 * 1024)

struct vc;

typedef void (*vc_devizcb_t)(struct vc *);

struct vc_callbacks {
	void (*handle_input_event)(struct vc *, struct input_event *);
	void (*visualized)(struct vc *, struct fb_info *);
	void (*schedule_devisualization)(struct vc *, vc_devizcb_t);
};

struct vc {
	const char *name;
	const struct vc_callbacks *callbacks;
	struct fb_info *fb; /**< current fb to draw, NULL is valid */
};


struct vc_fb {
	struct vc this;
};

extern int mpx_register_vc(struct vc *);
extern int mpx_deregister_vc(struct vc *);
extern int mpx_visualized(struct vc *vc);
extern int mpx_set_vmode(struct vc *, int mode);

#endif /* CONSOLE_MPX_H_ */
