/**
 * @file
 *
 * @date Feb 4, 2013
 * @author: Anton Bondarev
 */
#include <errno.h>
#include <assert.h>

#include <drivers/iodev.h>
#include <drivers/video/vesa_modes.h>
#include <drivers/video/fb.h> 
#include <embox/unit.h>

#include <module/embox/arch/x86/boot/multiboot.h>

#define VESA_MODE_NUMBER OPTION_GET(NUMBER,vesa_mode)
#define FB_NAME OPTION_STRING_GET(fb_name)
#define FB_INIT OPTION_GET(NUMBER,fb_init)

#define MBOOTMOD embox__arch__x86__boot__multiboot

#define SET_X   OPTION_MODULE_GET(MBOOTMOD,NUMBER,video_width)
#define SET_Y   OPTION_MODULE_GET(MBOOTMOD,NUMBER,video_height)
#define SET_BPP OPTION_MODULE_GET(MBOOTMOD,NUMBER,video_depth)

EMBOX_UNIT_INIT(mode_init);

static int mode_init(void) {
	struct fb_info *fbinfo;
	const struct fb_videomode *mode;
	const struct video_resbpp resbpp = {
		.x = SET_X,
		.y = SET_Y,
		.bpp = SET_BPP,
	};
	int ret;

	fbinfo = fb_lookup(FB_NAME);
	if (fbinfo == NULL) {
		return -ENODEV;
	}

	mode = video_fbmode_by_resbpp(&resbpp);
	if (mode == NULL) {
		return -EINVAL;
	}

	ret = fb_try_mode(&fbinfo->var, fbinfo, mode, resbpp.bpp);
	if (ret != 0) {
		return -EIO;
	}

	ret = fbinfo->ops->fb_set_par(fbinfo);
	if (ret != 0) {
		return -EIO;
	}

	return 0;

}
#if 0
static int fb_init(void) {
	struct fb_info *info;
	const struct video_resbpp *resbpp;
	const struct fb_videomode *mode;
	int ret;

	info = fb_lookup(FB_NAME);
	if (info == NULL) {
		return -ENODEV;
	}

	assert(info->ops != NULL);
	assert(info->ops->fb_set_par != NULL);

	resbpp = video_resbpp_by_vesamode(VESA_MODE_NUMBER);
	mode = video_fbmode_by_resbpp(resbpp);
	if (mode == NULL) {
		return -EINVAL;
	}

	ret = fb_try_mode(&info->var, info, mode, resbpp->bpp);
	if (ret != 0) {
		return ret;
	}

	ret = info->ops->fb_set_par(info);
	if (ret != 0) {
		return ret;
	}

	return 0;
}

static int iodev_setup_video(void) {
	if (iodev_video_ops == NULL) {
		return -ENOSYS;
	}

	iodev_setup(iodev_video_ops);
	return 0;
}

static int graphic_init(void) {
	int ret;

	ret = FB_INIT ? fb_init() : 0;

	if (ret != 0) {
		return ret;
	}

	ret = iodev_setup_video();
	if (ret != 0) {
		return ret;
	}

	ret = iodev_init();
	if (ret != 0) {
		return ret;
	}

	return 0;
}
#endif
