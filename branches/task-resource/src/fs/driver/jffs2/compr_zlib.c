/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: compr_zlib.c,v 1.31 2005/05/20 19:30:06 gleixner Exp $
 *
 */

#include <linux/zutil.h>
#undef local

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/zlib.h>
#include "nodelist.h"
#include "compr.h"

	/* Plan: call deflate() with avail_in == *sourcelen, 
	 * avail_out = *dstlen - 12 and flush == Z_FINISH.
	 * If it doesn't manage to finish,	call it again with
	 * avail_in == 0 and avail_out set to the remaining 12
	 * bytes for it to clean up.
	 * Q: Is 12 bytes sufficient?
	 */
#define STREAM_END_SPACE 12

static struct mutex deflate_sem = MUTEX_INIT(deflate_sem);
static struct mutex inflate_sem = MUTEX_INIT(inflate_sem);;

static z_stream inf_strm, def_strm;

#define alloc_workspaces() (0)
#define free_workspaces() do { } while(0)

static int jffs2_zlib_compress(unsigned char *data_in,
			       unsigned char *cpage_out,
			       uint32_t *sourcelen, uint32_t *dstlen,
			       void *model) {
	int ret;

	if (*dstlen <= STREAM_END_SPACE) {
		return -1;
	}

	mutex_lock(&deflate_sem);

	if (Z_OK != deflateInit(&def_strm, 3)) {
		printk(KERN_WARNING "deflateInit failed\n");
		mutex_unlock(&deflate_sem);
		return -1;
	}

	def_strm.next_in = data_in;
	def_strm.total_in = 0;
	
	def_strm.next_out = cpage_out;
	def_strm.total_out = 0;

	while (def_strm.total_out < *dstlen - STREAM_END_SPACE &&
			def_strm.total_in < *sourcelen) {
		def_strm.avail_out = *dstlen - (def_strm.total_out + STREAM_END_SPACE);
		def_strm.avail_in = min((unsigned)(*sourcelen-def_strm.total_in),
				def_strm.avail_out);
		D1(printk(KERN_DEBUG "calling deflate with avail_in %d, avail_out %d\n",
			  def_strm.avail_in, def_strm.avail_out));
		ret = deflate(&def_strm, Z_PARTIAL_FLUSH);
		D1(printk(KERN_DEBUG "deflate returned with avail_in %d, avail_out %d, total_in %ld, total_out %ld\n", 
			  def_strm.avail_in, def_strm.avail_out, def_strm.total_in, def_strm.total_out));
		if (ret != Z_OK) {
			D1(printk(KERN_DEBUG "deflate in loop returned %d\n", ret));
			deflateEnd(&def_strm);
			mutex_unlock(&deflate_sem);
			return -1;
		}
	}
	def_strm.avail_out += STREAM_END_SPACE;
	def_strm.avail_in = 0;
	ret = deflate(&def_strm, Z_FINISH);
	deflateEnd(&def_strm);

	if (ret != Z_STREAM_END) {
		D1(printk(KERN_DEBUG "final deflate returned %d\n", ret));
		ret = -1;
		goto out;
	}

	if (def_strm.total_out >= def_strm.total_in) {
		D1(printk(KERN_DEBUG "zlib compressed %ld bytes into %ld; failing\n",
			  def_strm.total_in, def_strm.total_out));
		ret = -1;
		goto out;
	}

	D1(printk(KERN_DEBUG "zlib compressed %ld bytes into %ld\n",
		  def_strm.total_in, def_strm.total_out));

	*dstlen = def_strm.total_out;
	*sourcelen = def_strm.total_in;
	ret = 0;
out:
	mutex_unlock(&deflate_sem);
	return ret;
}

static int jffs2_zlib_decompress(unsigned char *data_in,
				 unsigned char *cpage_out,
				 uint32_t srclen, uint32_t destlen,
				 void *model) {
	int ret;
	int wbits = MAX_WBITS;

	mutex_lock(&inflate_sem);

	inf_strm.next_in = data_in;
	inf_strm.avail_in = srclen;
	inf_strm.total_in = 0;
	
	inf_strm.next_out = cpage_out;
	inf_strm.avail_out = destlen;
	inf_strm.total_out = 0;

	/* If it's deflate, and it's got no preset dictionary, then
	 * we can tell zlib to skip the adler32 check.
	 */
	if (srclen > 2 && !(data_in[1] & PRESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFLATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) {

		D2(printk(KERN_DEBUG "inflate skipping adler32\n"));
		wbits = -((data_in[0] >> 4) + 8);
		inf_strm.next_in += 2;
		inf_strm.avail_in -= 2;
	} else {
		/* Let this remain D1 for now -- it should never happen */
		D1(printk(KERN_DEBUG "inflate not skipping adler32\n"));
	}


	if (Z_OK != zlib_inflateInit2(&inf_strm, wbits)) {
		printk(KERN_WARNING "inflateInit failed\n");
		mutex_unlock(&inflate_sem);
		return 1;
	}

	while((ret = zlib_inflate(&inf_strm, Z_FINISH)) == Z_OK) {
		;
	}
	if (ret != Z_STREAM_END) {
		printk(KERN_NOTICE "inflate returned %d\n", ret);
	}
	zlib_inflateEnd(&inf_strm);
	mutex_unlock(&inflate_sem);
    return 0;
}

static struct jffs2_compressor jffs2_zlib_comp = {
    .priority = JFFS2_ZLIB_PRIORITY,
    .name = "zlib",
    .compr = JFFS2_COMPR_ZLIB,
    .compress = &jffs2_zlib_compress,
    .decompress = &jffs2_zlib_decompress,
#ifdef JFFS2_ZLIB_DISABLED
    .disabled = 1,
#else
    .disabled = 0,
#endif
};

int __init jffs2_zlib_init(void) {
    int ret;

    ret = alloc_workspaces();
    if (ret) {
    	return ret;
    }

    ret = jffs2_register_compressor(&jffs2_zlib_comp);
    if (ret) {
    	free_workspaces();
    }

    return ret;
}

void jffs2_zlib_exit(void) {
    jffs2_unregister_compressor(&jffs2_zlib_comp);
    free_workspaces();
}
