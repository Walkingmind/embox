/*
 * bmp.h
 *
 *  Created on: Oct 3, 2012
 *      Author: user
 */

#ifndef BMP_H_
#define BMP_H_

#define XWND_BMP_MAGIC 0x00
#define XWND_BMP_PX_OFFSET 0x0A
#define XWND_BMP_WIDTH 0x12
#define XWND_BMP_HEIGHT 0x16
#define XWND_BMP_BPP 0x1C
#define XWND_BMP_BUF_SIZE 0x40

enum xwnd_bmp_err {XWND_BMP_OK, XWND_BMP_FAIL, XWND_BMP_FAIL_FILE, XWND_BMP_FAIL_MEM, XWND_BMP_FAIL_SIGN};

struct xwnd_bmp_image {
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	enum xwnd_bmp_err err;
	char * pxls;
};

extern struct xwnd_bmp_image xwnd_bmp_load (const char * file);
extern void xwnd_bmp_unload (struct xwnd_bmp_image * img);
extern void xwnd_bmp_draw (struct xwnd_bmp_image * img);

#endif /* BMP_H_ */
