/**
 * @file 
 * @brief 
 *
 * @author  Felix Sulima
 * @author  Anton Kozlov
 * @date    06.03.2013
 */

#include <errno.h>
#include <drivers/console/mpx.h>
#include <drivers/keyboard.h>
#include <util/dlist.h>
#include <drivers/video/vesa_modes.h>
#include <drivers/video/fb.h> 
#include <embox/unit.h>

EMBOX_UNIT_INIT(vc_mpx_init);

struct vc *vcs[VC_MPX_N];

static struct vc *curvc;
static struct vc *postvc;
static struct fb_info *curfb;

static struct vc **vcs_find(struct vc **vcs, struct vc *vc) {
	int i;
	for (i = 0; i < VC_MPX_N; i++) {
		if (vcs[i] != vc) {
			continue;
		}

		return &vcs[i];

	}
	return NULL;
}

static void vc_init(struct vc *vc) {

}

static int mpx_visualize(struct vc *vc) {

	if (postvc) {
		return -EAGAIN;
	}

	postvc = vc;

	if (curvc) {
		curvc->callbacks->schedule_devisualization(curvc);
	} else {
		mpx_devisualized(curvc);
	}

	return 0;
	
}

int mpx_register_vc(struct vc *vc) {
	struct vc **pvc = vcs_find(vcs, NULL);
	const struct vc_callbacks *cbs;
	
	if (!pvc) {
		return -ENOMEM;
	}

	*pvc = vc;

	vc_init(vc);

	cbs = vc->callbacks;
	if (!(cbs && cbs->handle_input_event 
			&& cbs->visualized
			&& cbs->schedule_devisualization)) {
		return -EINVAL;
	}

	if (curvc == NULL) {
		mpx_visualize(vc);
	}

	return 0;
}

int mpx_deregister_vc(struct vc *vc) {
	struct vc **pvc;
	
	if (vc == curvc) {
		return -EBUSY;
	}

	if (!(pvc = vcs_find(vcs, vc))) {
		return -ENOENT;
	}

	*pvc = NULL;

	return 0;
}

int mpx_devisualized(struct vc *vc) {

	assert(curvc == vc);

	if (curvc != vc) {
		return -EINVAL;
	}

	postvc->fb = curfb;
	postvc->callbacks->visualized(postvc, curfb);

	curvc = postvc;
	postvc = NULL;

	return 0;
}

static int indev_event_cb(struct input_dev *indev) {
	struct input_event ev;
	const int f1 = 0x3b;

	input_dev_event(indev, &ev);

	if (ev.type == KEY_PRESSED && (ev.value & CTRL_PRESSED)) {
		int num = (ev.value & 0x7f) - f1;
		if (num >= 0 && num < VC_MPX_N && vcs[num] != NULL) {
			mpx_visualize(vcs[num]);
			return 0;
		}
	}

	if (curvc) {
		curvc->callbacks->handle_input_event(curvc, &ev);
	}

	return 0;
}

static int vc_mpx_init(void) {
	struct input_dev *indev;
	const struct fb_videomode *mode;
	struct video_resbpp resbpp = {
		.x = 1024,
		.y = 768,
		.bpp = 16,
	};
	int ret;

	if (!(indev = input_dev_lookup("keyboard"))) {
		return -ENOENT;
	}

	if (0 > input_dev_open(indev, indev_event_cb)) {
		return -EAGAIN;
	}

	if (NULL == (curfb = fb_lookup("fb0"))) {
		return -ENOENT;
	}

	mode = video_fbmode_by_resbpp(&resbpp);
	if (mode == NULL) {
		return -EINVAL;
	}

	ret = fb_try_mode(&curfb->var, curfb, mode, resbpp.bpp);
	if (ret != 0) {
		return ret;
	}

	ret = curfb->ops->fb_set_par(curfb);
	if (ret != 0) {
		return ret;
	}


	return 0;
}

