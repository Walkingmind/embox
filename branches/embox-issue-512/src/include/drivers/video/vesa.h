/**
 * @file
 * @brief This file provides low-level video-mode routines for XWnd.
 *
 * @date 14.09.12
 * @author Alexandr Chernakov
 */

#ifndef DRIVERS_VIDEO_VESA_H_
#define DRIVERS_VIDEO_VESA_H_

enum vesa_video_mode {
	VESA_MODE_TEXT_40x25x16_M = 0x0,
	VESA_MODE_TEXT_40x25x16 = 0x1,
	VESA_MODE_TEXT_80x25x16_M = 0x2,
	VESA_MODE_TEXT_80x25x16 = 0x3,
	VESA_MODE_CGA_320x200x4 = 0x4,
	VESA_MODE_CGA_320x200x4_M = 0x5,
	VESA_MODE_CGA_640x200x2 = 0x6,
	VESA_MODE_MDA_80x25 = 0x7,
	/* ... */
	VESA_MODE_EGA_320x200x16 = 0xD,
	VESA_MODE_EGA_640x200x16 = 0xE,
	VESA_MODE_VGA_640x350 = 0xF,
	VESA_MODE_VGA_640x350x4 = 0x10,
	VESA_MODE_VGA_640x480x1 = 0x11,
	VESA_MODE_VGA_640x480x16 = 0x12,
	VESA_MODE_VGA_320x200x256 = 0x13,
	/* ... */
	VESA_MODE_SVGA_640x480x256 = 0x101,
	VESA_MODE_SVGA_800x600x16 = 0x102,
	VESA_MODE_SVGA_800x600x256 = 0x103,
	VESA_MODE_SVGA_1024x768x16 = 0x104,
	VESA_MODE_SVGA_1024x768x256 = 0x105,
	VESA_MODE_SVGA_1280x1024x16 = 0x106,
	VESA_MODE_SVGA_1280x1024x256 = 0x107,
	VESA_MODE_SVGA_TEXT_80x60 = 0x108,
	VESA_MODE_SVGA_TEXT_132x25 = 0x109,
	VESA_MODE_SVGA_TEXT_132x43 = 0x10A,
	VESA_MODE_SVGA_TEXT_132x50 = 0x10B,
	VESA_MODE_SVGA_TEXT_132x60 = 0x10C,
	VESA_MODE_SVGA_320x200x32K = 0x10D, /* (1:5:5:5) */
	VESA_MODE_SVGA_320x200x64K = 0x10E, /*  (5:6:5) */
	VESA_MODE_SVGA_320x200x16M = 0x10F, /* (8:8:8) */
	VESA_MODE_SVGA_640x480x32K = 0x110,
	VESA_MODE_SVGA_640x480x64K = 0x111,
	VESA_MODE_SVGA_640x480x16M = 0x112,
	VESA_MODE_SVGA_800x600x32K = 0x113,
	VESA_MODE_SVGA_800x600x64K = 0x114,
	VESA_MODE_SVGA_800x600x16M = 0x115,
	VESA_MODE_SVGA_1024x768x32K = 0x116,
	VESA_MODE_SVGA_1024x768x64K = 0x117,
	VESA_MODE_SVGA_1024x768x16M = 0x118,
	VESA_MODE_SVGA_1280x1024x32K = 0x119,
	VESA_MODE_SVGA_1280x1024x64K = 0x11A,
	VESA_MODE_SVGA_1280x1024x16M = 0x11B,
	VESA_MODE_SVGA_1600x1200x256 = 0x11C
};

struct vesa_mode_desc {
	int xres; /* horizontal resolution */
	int yres; /* vertical resolution */
	int bpp;  /* number of color bits per pixel */
};

struct dislay;
extern struct display *vga_setup_mode(struct display *display, enum vesa_video_mode mode);

extern const struct vesa_mode_desc * vesa_mode_get_desc(enum vesa_video_mode mode);

#endif /* DRIVERS_VIDEO_VESA_H_ */
