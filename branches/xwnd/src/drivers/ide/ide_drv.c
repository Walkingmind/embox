/*
 * @file
 * @brief 
 *
 * @date 24.08.2012
 * @author Andrey Gazukin
 */


/*
 * hd.c
 *
 * IDE driver
 *
 * Copyright (C) 2002 Michael Ringgaard. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <asm/io.h>
#include <embox/unit.h>
#include <kernel/irq.h>
#include <kernel/time/clock_source.h>
#include <types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <net/in.h>
#include <fs/fat.h>
#include <drivers/ide.h>
#include <embox/block_dev.h>

int ideprobe = 0;
static hdc_t hdctab[HD_CONTROLLERS];
static hd_t  hdtab[HD_DRIVES];
static slot_t ide;

static long tmr_cmd_start_time;

static int create_partitions(hd_t *hd);

static void hd_fixstring(unsigned char *s, int len) {
	unsigned char *p = s;
	unsigned char *end = s + len;

	/* Convert from big-endian to host byte order */
	for (p = end ; p != s;) {
		 unsigned short *pp = (unsigned short *) (p -= 2);
		*pp = ((*pp & 0x00FF) << 8) | ((*pp & 0xFF00) >> 8);
	}

	/* Strip leading blanks */
	while (s != end && *s == ' ') {
		++s;
	}

	/* Compress internal blanks and strip trailing blanks */
	while (s != end && *s) {
		if (*s++ != ' ' || (s != end && *s && *s != ' ')) {
			*p++ = *(s - 1);
		}
	}

	/* Wipe out trailing garbage */
	while (p != end) {
		*p++ = '\0';
	}
}

static void hd_error(char *func, unsigned char error) {
	/*
	kprintf(KERN_ERR "%s: ", func);
	if (error & HDCE_BBK)   kprintf("bad block  ");
	if (error & HDCE_UNC)   kprintf("uncorrectable data  ");
	if (error & HDCE_MC)    kprintf("media change  ");
	if (error & HDCE_IDNF)  kprintf("id not found  ");
	if (error & HDCE_MCR)   kprintf("media change requested  ");
	if (error & HDCE_ABRT)  kprintf("abort  ");
	if (error & HDCE_TK0NF) kprintf("track 0 not found  ");
	if (error & HDCE_AMNF)  kprintf("address mark not found  ");
	printf("\n");
	*/
	return;
}

static long system_read_timer(void) {
	struct timespec ts;

	ktime_get_timespec (&ts);
	return (long) ts.tv_sec;
}

static void tmr_set_timeout(void) {
	/* get the command start time */
	tmr_cmd_start_time = system_read_timer();
}

static int tmr_chk_timeout(long timeout) {
	long curTime;

	/* get current time */
	curTime = system_read_timer();

	/* timed out yet ? */
	if (curTime >= (tmr_cmd_start_time + timeout)) {
	  return 1;      /* yes */
	}
	/* no timeout yet */
	return 0;
}


static int hd_wait(hdc_t *hdc, unsigned char mask, unsigned int timeout) {
	unsigned char status, error;

	tmr_set_timeout();
	while (1) {
		status = inb(hdc->iobase + HDC_ALT_STATUS);
		if (status & HDCS_ERR) {
			error = inb(hdc->iobase + HDC_ERR);
			hd_error("hdwait", error);

			return error;
		}

		if (!(status & HDCS_BSY) && ((status & mask) == mask)) {
			return 0;
		}
		if (tmr_chk_timeout(timeout)) {
			return -ETIMEDOUT;
		}
		if((HDCS_DRQ == mask) && (0 == status)) {
			return -EIO;
		}
	}
	return -ETIMEDOUT;
}

static void hd_select_drive(hd_t *hd) {
	outb(hd->drvsel, hd->hdc->iobase + HDC_DRVHD);
}

static void hd_setup_transfer(hd_t *hd, blkno_t blkno, int nsects) {
	unsigned int track;
	unsigned int head;
	unsigned int sector;

	if (hd->lba) {
		track = (blkno >> 8) & 0xFFFF;
		head = ((blkno >> 24) & 0xF) | HD_LBA;
		sector = blkno & 0xFF;
	}
	else {
		track = blkno / (hd->heads * hd->sectors);
		head = (blkno / hd->sectors) % hd->heads;
		sector = blkno % hd->sectors + 1;
	}

	outb(0, hd->hdc->iobase + HDC_FEATURE);
	outb(nsects, hd->hdc->iobase + HDC_SECTORCNT);
	outb((unsigned char) sector, hd->hdc->iobase + HDC_SECTOR);
	outb((unsigned char) track, hd->hdc->iobase + HDC_TRACKLSB);
	outb((unsigned char) (track >> 8), hd->hdc->iobase + HDC_TRACKMSB);
	outb((((unsigned char) head & 0xFF) | (unsigned char) hd->drvsel),
		 hd->hdc->iobase + HDC_DRVHD);
}

static void pio_read_buffer(hd_t *hd, char *buffer, int size) {
	hdc_t *hdc = hd->hdc;

	if (hd->use32bits) {
		insl(hdc->iobase + HDC_DATA, buffer, size / 4);
	}
	else {
		insw(hdc->iobase + HDC_DATA, buffer, size / 2);
	}
}

static void pio_write_buffer(hd_t *hd, char *buffer, int size) {
	hdc_t *hdc = hd->hdc;

	if (hd->use32bits) {
		outsl(hdc->iobase + HDC_DATA, buffer, size / 4);
	}
	else {
		outsw(hdc->iobase + HDC_DATA, buffer, size / 2);
	}
}

static void setup_dma(hdc_t *hdc, char *buffer, int count, int cmd) {
	int i;
	int len;
	char *next;

	i = 0;
	next = (char *) ((unsigned long) buffer & ~(PAGESIZE - 1)) + PAGESIZE;
	while (1) {
		/*
		if (i == MAX_PRDS) {
		     panic("hd dma transfer too large");
		}
		*/

		/* hdc->prds[i].addr = virt2phys(buffer);*/
		hdc->prds[i].addr = (unsigned long) buffer;
		len = next - buffer;
		if (count > len) {
			hdc->prds[i].len = len;
			count -= len;
			buffer = next;
			next += PAGESIZE;
			i++;
		}
		else {
			hdc->prds[i].len = count | 0x80000000;
			break;
		}
	}

	/* Setup PRD table */
	outl(hdc->prds_phys, hdc->bmregbase + BM_PRD_ADDR);

	/* Specify read/write */
	outb(cmd | BM_CR_STOP, hdc->bmregbase + BM_COMMAND_REG);

	/* Clear INTR & ERROR flags */
	outb(inb(hdc->bmregbase + BM_STATUS_REG) | BM_SR_INT | BM_SR_ERR,
		 hdc->bmregbase + BM_STATUS_REG);
}

static void start_dma(hdc_t *hdc) {
	/* Start DMA operation */
	outb(inb(hdc->bmregbase + BM_COMMAND_REG) | BM_CR_START,
		 hdc->bmregbase + BM_COMMAND_REG);
}

static int stop_dma(hdc_t *hdc) {
	int dmastat;

	/* Stop DMA channel and check DMA status */
	outb(inb(hdc->bmregbase + BM_COMMAND_REG) & ~BM_CR_START,
	   hdc->bmregbase + BM_COMMAND_REG);

	/* Get DMA status */
	dmastat = inb(hdc->bmregbase + BM_STATUS_REG);

	/* Clear INTR && ERROR flags */
	outb(dmastat | BM_SR_INT | BM_SR_ERR, hdc->bmregbase + BM_STATUS_REG);

	/* Check for DMA errors */
	if (dmastat & BM_SR_ERR) {
		/*kprintf(KERN_ERR "hd: dma error %02X\n", dmastat); */
		return -EIO;
	}

	return 0;
}

static int hd_identify(hd_t *hd) {

	/* Ignore interrupt for identify command */
	hd->hdc->dir = HD_XFER_IGNORE;
	/* reset_event(&hd->hdc->ready); */

	/* Issue read drive parameters command */
	outb(0, hd->hdc->iobase + HDC_FEATURE);
	outb(hd->drvsel, hd->hdc->iobase + HDC_DRVHD);
	outb(hd->iftype == HDIF_ATAPI ? HDCMD_PIDENTIFY : HDCMD_IDENTIFY,
			hd->hdc->iobase + HDC_COMMAND);

	/* Wait for data ready */
	/*
	if (wait_for_object(&hd->hdc->ready, HDTIMEOUT_CMD) < 0) {
		return -ETIMEDOUT;
	}
	*/

	/*
	* Some controllers issues the interrupt before data is ready to be read
	* Make sure data is ready by waiting for DRQ to be set
	*/
	if (hd_wait(hd->hdc, HDCS_DRQ, HDTIMEOUT_DRQ) < 0) {
		return -EIO;
	}

	/* Read parameter data */
	insw(hd->hdc->iobase + HDC_DATA,
			(char *) &(hd->param), SECTOR_SIZE / 2);

	/* Fill in drive parameters */
	hd->cyls = hd->param.cylinders;
	hd->heads = hd->param.heads;
	hd->sectors = hd->param.sectors;
	hd->use32bits = 0;/*hd->param.usedmovsd != 0; */
	hd->sectbufs = hd->param.buffersize;
	hd->multsect = hd->param.nsecperint;
	if (hd->multsect == 0) {
		hd->multsect = 1;
	}

	hd_fixstring((unsigned char *)hd->param.model, sizeof(hd->param.model));
	hd_fixstring((unsigned char *)hd->param.rev, sizeof(hd->param.rev));
	hd_fixstring((unsigned char *)hd->param.serial, sizeof(hd->param.serial));

	if (hd->iftype == HDIF_ATA) {
		hd->media = IDE_DISK;
	}
	else {
		hd->media = (hd->param.config >> 8) & 0x1f;
	}

	/* Determine LBA or CHS mode */
	if ((hd->param.caps & 0x0200) == 0) {
		hd->lba = 0;
		hd->blks = hd->cyls * hd->heads * hd->sectors;
		if (hd->cyls == 0 && hd->heads == 0 && hd->sectors == 0) {
			return -EIO;
		}
		if (hd->cyls == 0xFFFF && hd->heads == 0xFFFF
			&& hd->sectors == 0xFFFF) {
			return -EIO;
		}
	}
	else {
		hd->lba = 1;
		hd->blks = (hd->param.totalsec1 << 16) | hd->param.totalsec0;
		if (hd->media == IDE_DISK && (hd->blks == 0 ||
			hd->blks == 0xFFFFFFFF)) {
			return -EIO;
		}
	}
	/* size in Mb */
	hd->size = hd->blks / (1024 * 1024 / SECTOR_SIZE);

	return 0;
}

static int hd_cmd(hd_t *hd, unsigned int cmd,
				  unsigned int feat, unsigned int nsects) {
	/* Ignore interrupt for command */
	hd->hdc->dir = HD_XFER_IGNORE;
	/*  reset_event(&hd->hdc->ready);*/

	/* Issue command */
	outb(feat, hd->hdc->iobase + HDC_FEATURE);
	outb(nsects, hd->hdc->iobase + HDC_SECTORCNT);
	outb(hd->drvsel, hd->hdc->iobase + HDC_DRVHD);
	outb(cmd, hd->hdc->iobase + HDC_COMMAND);

	/* Wait for data ready */
	/*
	 if (wait_for_object(&hd->hdc->ready, HDTIMEOUT_CMD) < 0) {
	 	 return -ETIMEDOUT;
	 }
	 */

	/* Check status */
	if (hd->hdc->result < 0) {
		return -EIO;
	}

	return 0;
}

static int atapi_packet_read(hd_t *hd, unsigned char *pkt,
		                     int pktlen, char *buffer, size_t bufsize) {
	hdc_t *hdc;
	int result;
	char *bufp;
	int bufleft;
	unsigned short bytes;

	/*kprintf("atapi_read_packet(0x%x) %d bytes, buflen=%d\n", pkt[0], pktlen, bufsize); */
	hdc = hd->hdc;
	/*
	if (wait_for_object(&hdc->lock, HDTIMEOUT_BUSY) < 0) {
		return -EBUSY;
	}
	*/

	bufp = (char *) buffer;
	bufleft = bufsize;
	hdc->dir = HD_XFER_IGNORE;
	hdc->active = hd;
	hdc->result = 0;
	/* reset_event(&hdc->ready); */

	/* Setup registers */
	outb(0, hdc->iobase + HDC_FEATURE);
	outb(0, hdc->iobase + HDC_SECTORCNT);
	outb(0, hdc->iobase + HDC_SECTOR);
	outb((unsigned char) (bufsize & 0xFF), hdc->iobase + HDC_TRACKLSB);
	outb((unsigned char) (bufsize >> 8), hdc->iobase + HDC_TRACKMSB);
	outb((unsigned char) hd->drvsel, hdc->iobase + HDC_DRVHD);

	/* Send packet command */
	outb(HDCMD_PACKET, hdc->iobase + HDC_COMMAND);

	/* Wait for drive ready to receive packet */
	result = hd_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
	if (result != 0) {
		/* kprintf(KERN_WARNING "atapi_packet_read: busy waiting for packet ready (0x%02x)\n", result); */

		hdc->dir = HD_XFER_IDLE;
		hdc->active = NULL;
		/* release_mutex(&hdc->lock);*/

		return -EIO;
	}

	/* Command packet transfer */
	hdc->result = 0;
	pio_write_buffer(hd, (char *) pkt, pktlen);

	/* Data transfer */
	while (!hdc->result) {
		/* Wait until data ready */
		usleep(300);
		/*kprintf("wait for data\n"); */
		/*
		if (wait_for_object(&hdc->ready, HDTIMEOUT_XFER) < 0) {
			//kprintf(KERN_WARNING "hd_read: timeout waiting for interrupt\n");
			hdc->result = -EIO;
			break;
		}
		reset_event(&hdc->ready);
		*/
		/* Check for errors */
		if (hdc->status & HDCS_ERR) {
			/*unsigned char error;

			error = inb(hdc->iobase + HDC_ERR);

			kprintf(KERN_ERR "hd: atapi packet read error (status=0x%02x,error=0x%02x)\n", hdc->status, error); */
			hdc->result = -EIO;

			break;
		}
		/*
		 * Exit the read data loop if the device indicates this is
		 * the end of the command
		 */
		/* kprintf("stat 0x%02x\n", hdc->status); */
		if ((hdc->status & (HDCS_BSY | HDCS_DRQ)) == 0) {
			break;
		}

		/* Get the byte count */
		bytes = (inb(hdc->iobase + HDC_TRACKMSB) << 8) | inb(hdc->iobase + HDC_TRACKLSB);
		/*kprintf("%d bytes\n", bytes); */
		if (bytes == 0) {
			break;
		}
		if (bytes > bufleft) {
			/*kprintf(KERN_ERR "%s: buffer overrun\n", device(hd->devno)->name); */
			hdc->result = -ENOBUFS;
			break;
		}
		/* Read the bytes */
		pio_read_buffer(hd, bufp, bytes);
		bufp += bytes;
		bufleft -= bytes;
	}

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;
	if(0 < hdc->result) {
		result = hdc->result = 0;
	}
	/* release_mutex(&hdc->lock);*/
	return result == 0 ? bufsize - bufleft : result;
}

static int atapi_read_capacity(hd_t *hd) {
	unsigned char pkt[12];
	unsigned long buf[2];
	unsigned long blks;
	//unsigned long blksize;
	int rc;

	memset(pkt, 0, 12);
	pkt[0] = ATAPI_CMD_READCAPICITY;

	rc = atapi_packet_read(hd, pkt, 12, (char *)buf, sizeof buf);
	if (rc < 0) {
		return rc;
	}
	if (rc != sizeof buf) {
		return -ENOBUFS;
	}

	blks = ntohl(buf[0]);
	/*blksize = ntohl(buf[1]);

	if (blksize != CDSECTORSIZE) {
		kprintf("%s: unexpected block size (%d)\n", device(hd->devno)->name, blksize);
	}
	*/
	return blks;
}

static int atapi_request_sense(hd_t *hd) {
	unsigned char pkt[12];
	unsigned char buf[18];
	int rc;

	memset(pkt, 0, 12);
	pkt[0] = ATAPI_CMD_REQUESTSENSE;
	pkt[4] = sizeof buf;

	rc = atapi_packet_read(hd, pkt, 12, (char *)buf, sizeof buf);
	if (rc < 0) {
		return rc;
	}

	return 0;
}

static int hd_ioctl(block_dev_t *dev, int cmd, void *args, size_t size) {
	block_dev_geometry_t *geom;
	hd_t *hd = (hd_t *) dev->privdata;

	switch (cmd) {
	case IOCTL_GETDEVSIZE:
		return hd->blks;

	case IOCTL_GETBLKSIZE:
		return SECTOR_SIZE;

	case IOCTL_GETGEOMETRY:
		if (!args || size != sizeof(block_dev_geometry_t)) {
			return -EINVAL;
		}
		geom = (block_dev_geometry_t *) args;
		geom->cyls = hd->cyls;
		geom->heads = hd->heads;
		geom->spt = hd->sectors;
		geom->sectorsize = SECTOR_SIZE;
		geom->sectors = hd->blks;
		return 0;

	case IOCTL_REVALIDATE:
		return create_partitions(hd);
	}

	return -ENOSYS;
}

static int hd_read_pio(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno) {
	hd_t *hd;
	hdc_t *hdc;
	int sectsleft;
	int nsects;
	int result;
	char *bufp;

	/*kprintf("hdread: block %d\n", blkno); */

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;
	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;
	/*
	if (wait_for_object(&hdc->lock, HDTIMEOUT_BUSY) < 0) {
		return -EBUSY;
	}
	*/

	while (sectsleft > 0) {
		/* Select drive */
		hd_select_drive(hd);

		/* Wait for controller ready */
		result = hd_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
			/*kprintf(KERN_ERR "hd_read: no drdy (0x%02x)\n", result); */
			hdc->result = -EIO;
			break;
		}

		/* Calculate maximum number of sectors we can transfer */
		/*kprintf("%d sects left\n", sectsleft); */
		if (sectsleft > 256) {
			nsects = 256;
		}
		else {
			nsects = sectsleft;
		}

		/* Prepare transfer */
		/*kprintf("read %d sects\n", nsects); */
		hdc->bufp = bufp;
		hdc->nsects = nsects;
		hdc->result = 0;
		hdc->dir = HD_XFER_READ;
		hdc->active = hd;
		/*    reset_event(&hdc->ready); */

		hd_setup_transfer(hd, blkno, nsects);
		outb(hd->multsect > 1 ? HDCMD_MULTREAD : HDCMD_READ,
				hdc->iobase + HDC_COMMAND);

	/* Wait until data read */
	/*
	if (wait_for_object(&hdc->ready, HDTIMEOUT_XFER) < 0) {
		//kprintf(KERN_WARNING "hd_read: timeout waiting for interrupt\n");
		hdc->result = -EIO;
		break;
	}
	*/

		while(!hdc->result) {
			usleep(300);
		}
		if (hdc->result < 0) {
			break;
		}

		/* Advance to next */
		sectsleft -= nsects;
		bufp += nsects * SECTOR_SIZE;
	}
	/*kprintf("finito\n"); */

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;
	if(0 < hdc->result) {
		result = hdc->result = 0;
	}

	return result == 0 ? count : result;
}

static int hd_write_pio(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno) {
	hd_t *hd;
	hdc_t *hdc;
	int sectsleft;
	int nsects;
	int n;
	int result;
	char *bufp;

	/*kprintf("hdwrite: block %d\n", blkno); */

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;
	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;
	/*
	if(wait_for_object(&hdc->lock, HDTIMEOUT_BUSY) < 0) {
	return -EBUSY;
	}
	*/

	while (sectsleft > 0) {
		/*kprintf("%d sects left\n", sectsleft); */
		/* Select drive */
		hd_select_drive(hd);

		/* Wait for controller ready */
		result = hd_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
			/*kprintf(KERN_ERR "hd_write: no drdy (0x%02x)\n", result); */
			hdc->result = -EIO;
			break;
		}
		/* Calculate maximum number of sectors we can transfer */
		if (sectsleft > 256) {
			nsects = 256;
		}
		else {
			nsects = sectsleft;
		}
		/*kprintf("write %d sects\n", nsects); */

		/* Prepare transfer */
		hdc->bufp = bufp;
		hdc->nsects = nsects;
		hdc->result = 0;
		hdc->dir = HD_XFER_WRITE;
		hdc->active = hd;
		/* reset_event(&hdc->ready); */

		hd_setup_transfer(hd, blkno, nsects);
		outb(hd->multsect > 1 ? HDCMD_MULTWRITE : HDCMD_WRITE,
				hdc->iobase + HDC_COMMAND);

		/* Wait for data ready */
		if (!(inb(hdc->iobase + HDC_ALT_STATUS) & HDCS_DRQ)) {
			result = hd_wait(hdc, HDCS_DRQ, HDTIMEOUT_DRQ);
			if (result != 0) {
				/* kprintf("hd_write: no drq (0x%02x)\n", result);*/
				hdc->result = -EIO;
				break;
			}
		}

		/* Write first sector(s) */
		n = hd->multsect;
		if (n > nsects) {
			n = nsects;
		}
		while (n-- > 0) {
			pio_write_buffer(hd, hdc->bufp, SECTOR_SIZE);
			hdc->bufp += SECTOR_SIZE;
		}
		/*kprintf("wait\n"); */

		/* Wait until data written */
		/*
		if (wait_for_object(&hdc->ready, HDTIMEOUT_XFER) < 0) {
			//kprintf(KERN_ERR "hd_write: timeout waiting for interrupt\n");
			hdc->result = -EIO;
			break;
		}
		*/
		while(!hdc->result) {
			usleep(300);
		}
		if (hdc->result < 0) {
			break;
		}
		/*kprintf("ready\n"); */

		/* Advance to next */
		sectsleft -= nsects;
		bufp += nsects * SECTOR_SIZE;
	}

	/*kprintf("finito\n"); */

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;
	result = hdc->result;

	return result == 0 ? count : result;
}

static int hd_read_udma(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno) {
	hd_t *hd;
	hdc_t *hdc;
	int sectsleft;
	int nsects;
	int result;
	char *bufp;
	unsigned char error;

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;

	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;
	/*
	if (wait_for_object(&hdc->lock, HDTIMEOUT_BUSY) < 0) {
		return -EBUSY;
	}
	*/

	while (sectsleft > 0) {
		/* Select drive */
		hd_select_drive(hd);

		/* Wait for controller ready */
		result = hd_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
			/*kprintf(KERN_ERR "hd_read: no drdy (0x%02x)\n", result); */
			result = -EIO;
			break;
		}

		/* Calculate maximum number of sectors we can transfer */
		if (sectsleft > 256) {
			nsects = 256;
		}
		else {
			nsects = sectsleft;
		}

		if (nsects > MAX_DMA_XFER_SIZE / SECTOR_SIZE) {
			nsects = MAX_DMA_XFER_SIZE / SECTOR_SIZE;
		}

		/* Prepare transfer */
		result = 0;
		hdc->dir = HD_XFER_DMA;
		hdc->active = hd;
		/* reset_event(&hdc->ready); */

		hd_setup_transfer(hd, blkno, nsects);

		/* Setup DMA */
		setup_dma(hdc, bufp, nsects * SECTOR_SIZE, BM_CR_WRITE);

		/* Start read */
		outb(HDCMD_READDMA, hdc->iobase + HDC_COMMAND);
		start_dma(hdc);

		/* Wait for interrupt */
		/*
		if (wait_for_object(&hdc->ready, HDTIMEOUT_XFER) < 0) {
			//kprintf(KERN_WARNING "hd: timeout waiting for read to complete\n");
			stop_dma(hdc);
			result = -EIO;
			break;
		}
		*/

		/* Stop DMA channel and check DMA status */
		result = stop_dma(hdc);
		if (result < 0) {
			break;
		}

		/* Check controller status */
		if (hdc->status & HDCS_ERR) {
			error = inb(hdc->iobase + HDC_ERR);
			hd_error("hdread", error);

			/*kprintf(KERN_ERR "hd: read error (0x%02x)\n", hdc->status); */
			result = -EIO;
			break;
		}

		/* Advance to next */
		sectsleft -= nsects;
		bufp += nsects * SECTOR_SIZE;
	}

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;

	return result == 0 ? count : result;
}

static int hd_write_udma(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno) {
	hd_t *hd;
	hdc_t *hdc;
	int sectsleft;
	int nsects;
	int result;
	char *bufp;
	unsigned char error;

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;

	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;
	/*
	if (wait_for_object(&hdc->lock, HDTIMEOUT_BUSY) < 0)
	{
		return -EBUSY;
	}
	*/
	/*kprintf("hdwrite block %d size %d buffer %p\n", blkno, count, buffer); */

	while (sectsleft > 0) {
		/* Select drive */
		hd_select_drive(hd);

		/* Wait for controller ready */
		result = hd_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
			/*kprintf(KERN_ERR "hd_write: no drdy (0x%02x)\n", result); */
			result = -EIO;
			break;
		}

		/* Calculate maximum number of sectors we can transfer */
		if (sectsleft > 256) {
			nsects = 256;
		}
		else {
			nsects = sectsleft;
		}
		if (nsects > MAX_DMA_XFER_SIZE / SECTOR_SIZE) {
			nsects = MAX_DMA_XFER_SIZE / SECTOR_SIZE;
		}

		/* Prepare transfer */
		result = 0;
		hdc->dir = HD_XFER_DMA;
		hdc->active = hd;
		/* reset_event(&hdc->ready); */

		hd_setup_transfer(hd, blkno, nsects);

		/* Setup DMA */
		setup_dma(hdc, bufp, nsects * SECTOR_SIZE, BM_CR_READ);

		/* Start write */
		outb(HDCMD_WRITEDMA, hdc->iobase + HDC_COMMAND);
		start_dma(hdc);

		/* Wait for interrupt */
		/*
		if (wait_for_object(&hdc->ready, HDTIMEOUT_XFER) < 0) {
			//kprintf(KERN_WARNING "hd: timeout waiting for write to complete\n");
			stop_dma(hdc);
			result = -EIO;
			break;
		}
		*/

		/* Stop DMA channel and check DMA status */
		result = stop_dma(hdc);
		if (result < 0) {
			break;
		}

		/* Check controller status */
		if (hdc->status & HDCS_ERR) {
			error = inb(hdc->iobase + HDC_ERR);
			hd_error("hdwrite", error);

			/*kprintf(KERN_ERR "hd: write error (0x%02x)\n", hdc->status); */
			result = -EIO;
			break;
		}

		/* Advance to next */
		sectsleft -= nsects;
		bufp += nsects * SECTOR_SIZE;
	}

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;

	return result == 0 ? count : result;
}

static int cd_read(block_dev_t *dev, char *buffer,
					size_t count, blkno_t blkno) {
	unsigned char pkt[12];
	unsigned int blks;
	hd_t *hd = (hd_t *) dev->privdata;

	/* kprintf("cd_read: blk %d %d bytes\n", blkno, count); */

	blks = count / CDSECTORSIZE;
	if (blks > 0xFFFF) {
		return -EINVAL;
	}

	memset(pkt, 0, 12);
	pkt[0] = ATAPI_CMD_READ10;
	pkt[2] = blkno >> 24;
	pkt[3] = (blkno >> 16) & 0xFF;
	pkt[4] = (blkno >> 8) & 0xFF;
	pkt[5] = blkno & 0xFF;
	pkt[7] = (blks >> 8) & 0xFF;
	pkt[8] = blks & 0xFF;

	return atapi_packet_read(hd, pkt, 12, buffer, count);
}

static int cd_write(block_dev_t *dev, char *buffer,
					size_t count, blkno_t blkno) {
	return -ENODEV;
}

static int cd_ioctl(block_dev_t *dev, int cmd, void *args, size_t size) {
	hd_t *hd = (hd_t *) dev->privdata;
	int rc;

	switch (cmd) {
	case IOCTL_GETDEVSIZE:
		if (hd->blks <= 0) {
			hd->blks = atapi_read_capacity(hd);
		}
		return hd->blks;

	case IOCTL_GETBLKSIZE:
		return CDSECTORSIZE;

	case IOCTL_REVALIDATE:
		rc = atapi_request_sense(hd);
		if (rc < 0) {
			return rc;
		}

		rc = hd->blks = atapi_read_capacity(hd);
		if (rc < 0) {
			return rc;
		}

		return 0;
	}

	return -ENOSYS;
}

void hd_dpc(void *arg) {
	hdc_t *hdc = (hdc_t *) arg;
	int nsects;
	int n;

	/* kprintf("[hddpc]"); */
	switch (hdc->dir) {
	case HD_XFER_READ:
		/* Check status */
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		if (hdc->status & HDCS_ERR) {
			unsigned char error;

			error = inb(hdc->iobase + HDC_ERR);
			hd_error("hdread", error);

			/* printf(KERN_ERR "hd: read error (0x%02x)\n", hdc->status); */
			hdc->result = -EIO;
			/* set_event(&hdc->ready);*/
		}
		else
		{
			/* Read sector data */
			nsects = hdc->active->multsect;
			if (nsects > hdc->nsects) {
				nsects = hdc->nsects;
			}
			for (n = 0; n < nsects; n++) {
				pio_read_buffer(hdc->active, hdc->bufp, SECTOR_SIZE);
				hdc->bufp += SECTOR_SIZE;
			}

			/* Signal event if we have read all sectors */
			hdc->nsects -= nsects;
			/* if (hdc->nsects == 0) set_event(&hdc->ready);*/
		}
		break;

	case HD_XFER_WRITE:
		/* Check status */
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		if (hdc->status & HDCS_ERR) {
			unsigned char error;

			error = inb(hdc->iobase + HDC_ERR);
			hd_error("hdwrite", error);

			/* kprintf(KERN_ERR "hd: write error (0x%02x)\n", hdc->status); */
			hdc->result = -EIO;
			/* set_event(&hdc->ready);*/
		}
		else {
			/* Transfer next sector(s) or signal end of transfer */
			nsects = hdc->active->multsect;
			if (nsects > hdc->nsects) {
				nsects = hdc->nsects;
			}
			hdc->nsects -= nsects;

			if (hdc->nsects > 0) {
				nsects = hdc->active->multsect;
				if (nsects > hdc->nsects) {
					nsects = hdc->nsects;
				}

				for (n = 0; n < nsects; n++) {
					pio_write_buffer(hdc->active, hdc->bufp, SECTOR_SIZE);
					hdc->bufp += SECTOR_SIZE;
				}
			}
			else {
			/*  set_event(&hdc->ready);*/
			}
		}
		break;

	case HD_XFER_DMA:
		outb(inb(hdc->bmregbase + BM_STATUS_REG),
				hdc->bmregbase + BM_STATUS_REG);
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		/* set_event(&hdc->ready);*/
		break;

	case HD_XFER_IGNORE:
		/* Read status to acknowledge interrupt */
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		//hdc->result = 1;
		/* set_event(&hdc->ready);*/
		break;

	case HD_XFER_IDLE:
	default:
		/* Read status to acknowledge interrupt */
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		/* kprintf("unexpected intr from hdc\n"); */
		break;
	}

	if((0 == hdc->result) && (HD_XFER_IDLE != hdc->dir)
			              && (HD_XFER_IGNORE != hdc->dir)) {
		hdc->result = 1;
	}
}

static irq_return_t hdc_handler(unsigned int irq_num, void *arg) {
  	hd_dpc(arg);

	return IRQ_HANDLED;
}



static int part_ioctl(block_dev_t *dev, int cmd, void *args, size_t size) {
	struct partition *part = (struct partition *) dev->privdata;

	switch (cmd) {
	case IOCTL_GETDEVSIZE:
		return part->len;

	case IOCTL_GETBLKSIZE:
		return dev_ioctl(part->dev, IOCTL_GETBLKSIZE, NULL, 0);
	}

	return -ENOSYS;
}

static int part_read(block_dev_t *dev, char *buffer,
						size_t count, blkno_t blkno) {
	struct partition *part = (struct partition *) dev->privdata;
	if (blkno + count / SECTOR_SIZE > part->len) {
		return -EFAULT;
	}
	return dev_read(part->dev, buffer, count, blkno + part->start);
}

static int part_write(block_dev_t *dev, char *buffer,
						size_t count, blkno_t blkno) {
  struct partition *part = (struct partition *) dev->privdata;
  if (blkno + count / SECTOR_SIZE > part->len) {
	  return -EFAULT;
  }
  return dev_write(part->dev, buffer, count, blkno + part->start);
}

block_dev_driver_t harddisk_udma_driver = {
	"idedisk_udma_drv",
	DEV_TYPE_BLOCK,
	hd_ioctl,
	hd_read_udma,
	hd_write_udma
};

block_dev_driver_t harddisk_pio_driver = {
	"idedisk_drv",
	DEV_TYPE_BLOCK,
	hd_ioctl,
	hd_read_pio,
	hd_write_pio
};

block_dev_driver_t cdrom_pio_driver = {
	"idecd_drv",
	DEV_TYPE_BLOCK,
	cd_ioctl,
	cd_read,
	cd_write
};

block_dev_driver_t partition_driver = {
	"partition_drv",
	DEV_TYPE_BLOCK,
	part_ioctl,
	part_read,
	part_write
};

static int create_partitions(hd_t *hd) {
	mbr_t mbrdata;
	mbr_t *mbr = &mbrdata;
	//lbr_t lbrdata;
	//lbr_t *lbr = &lbrdata;
	int rc;
	/* dev_t devno; */
	/* int i; */
	/* char devname[MAX_LENGTH_FILE_NAME]; */

	/* Read partition table */
	rc = dev_read(hd->devno, (char *)mbr, SECTOR_SIZE, 0);
	if (rc < 0) {
		/* kprintf(KERN_ERR "%s: error %d reading partition table\n", device(hd->devno)->name, rc); */
		return rc;
	}
	//lbr = (lbr_t *) mbr;

	/* Create partition devices */
	if ((mbr->sig_55 != 0x55) || (mbr->sig_aa != 0xAA)) {
		/*kprintf(KERN_ERR "%s: illegal boot sector signature\n", device(hd->devno)->name); */
		return -EIO;
	}
	/*
	for (i = 0; i < HD_PARTITIONS; i++) {
		hd->parts[i].dev = hd->devno;
		hd->parts[i].bootid = mbr->ptable[i].active;
		hd->parts[i].systid = mbr->ptable[i].type;
		hd->parts[i].start = mbr->ptable[i].relsect;
		hd->parts[i].len = mbr->ptable[i].numsect;

		if (mbr->parttab[i].systid != 0) {
			sprintf(devname, "%s%c", ((block_dev_module_t *)
			&(__block_dev_registry[hd->devno]))->name, 'a' + i);
			devno = dev_open(devname);
			if (devno == NODEV) {
				devno = dev_make(devname, &partition_driver, NULL, &hd->parts[i]);
				//kprintf(KERN_INFO "%s: partition %d on %s, %dMB (type %02x)\n", devname, i, device(hd->devno)->name, mbr->parttab[i].numsect / ((1024 * 1024) / SECTORSIZE), mbr->parttab[i].systid);
			}
			else {
				dev_close(devno);
			}
		}
	}
	*/
	return 0;
}

static int probe_device(hdc_t *hdc, int drvsel) {
	unsigned char sc, sn;

	/* Probe for device on controller */
	outb(drvsel, hdc->iobase + HDC_DRVHD);
	idedelay();

	outb(0x55, hdc->iobase + HDC_SECTORCNT);
	outb(0xAA, hdc->iobase + HDC_SECTOR);

	outb(0xAA, hdc->iobase + HDC_SECTORCNT);
	outb(0x55, hdc->iobase + HDC_SECTOR);

	outb(0x55, hdc->iobase + HDC_SECTORCNT);
	outb(0xAA, hdc->iobase + HDC_SECTOR);

	sc = inb(hdc->iobase + HDC_SECTORCNT);
	sn = inb(hdc->iobase + HDC_SECTOR);

	if (sc == 0x55 && sn == 0xAA) {
		return 1;
	}
	else {
		return -EIO;
	}
}

static int wait_reset_done(hdc_t *hdc, int drvsel) {

	outb(drvsel, hdc->iobase + HDC_DRVHD);
	idedelay();

	tmr_set_timeout();
	while (1) {
		hdc->status = inb(hdc->iobase + HDC_STATUS);
		if ((hdc->status & HDCS_BSY) == 0) {
			return 0;
		}
		if (tmr_chk_timeout(HDTIMEOUT_DRDY)) {
			break;
		}
	}

	return -EBUSY;
}

static int get_interface_type(hdc_t *hdc, int drvsel) {
	unsigned char sc, sn, cl, ch, st;

	outb(drvsel, hdc->iobase + HDC_DRVHD);
	idedelay();

	sc = inb(hdc->iobase + HDC_SECTORCNT);
	sn = inb(hdc->iobase + HDC_SECTOR);
	/* kprintf("%x: sc=0x%02x sn=0x%02x\n", hdc->iobase, sc, sn); */

	if (sc == 0x01 && sn == 0x01) {
		cl = inb(hdc->iobase + HDC_TRACKLSB);
		ch = inb(hdc->iobase + HDC_TRACKMSB);
		st = inb(hdc->iobase + HDC_STATUS);
		/* kprintf("%x: cl=0x%02x ch=0x%02x st=0x%02x\n", hdc->iobase, cl, ch, st); */

		if (cl == 0x14 && ch == 0xeb) {
			return HDIF_ATAPI;
		}
		if (cl == 0x00 && ch == 0x00 && st != 0x00) {
			return HDIF_ATA;
		}
	}

	return HDIF_UNKNOWN;
}

static int setup_hdc(hdc_t *hdc, int iobase, int irq,
					int bmregbase, int *masterif, int *slaveif) {
	int res;

	memset(hdc, 0, sizeof(hdc_t));
	hdc->iobase = iobase;
	hdc->irq = irq;
	hdc->bmregbase = bmregbase;
	hdc->dir = HD_XFER_IGNORE;

	if (hdc->bmregbase) {
		/* Allocate one page for PRD list */
		hdc->prds = (struct prd *) malloc(PAGESIZE);
		/*    hdc->prds_phys = virt2phys(hdc->prds);*/
	}

	/*
	init_dpc(&hdc->xfer_dpc);

	init_mutex(&hdc->lock, 0);
	init_event(&hdc->ready, 0, 0);
	*/

	if (ideprobe) {
		/* Assume no devices connected to controller */
		*masterif = HDIF_NONE;
		*slaveif = HDIF_NONE;

		/* Setup device control register */
		outb(HDDC_HD15 | HDDC_NIEN, hdc->iobase + HDC_CONTROL);

		/* Probe for master and slave device on controller */
		if (probe_device(hdc, HD0_DRVSEL) >= 0) {
			*masterif = HDIF_PRESENT;
		}
		if (probe_device(hdc, HD1_DRVSEL) >= 0) {
			*slaveif = HDIF_PRESENT;
		}

		/* Reset controller */
		outb(HDDC_HD15 | HDDC_SRST | HDDC_NIEN, hdc->iobase + HDC_CONTROL);
		idedelay();
		outb(HDDC_HD15 | HDDC_NIEN, hdc->iobase + HDC_CONTROL);
		idedelay();

		/* Wait for reset to finish on all present devices */
		if (*masterif != HDIF_NONE) {
			int rc = wait_reset_done(hdc, HD0_DRVSEL);
			if (rc < 0) {
				*masterif = HDIF_NONE;
			}
		}

		if (*slaveif != HDIF_NONE) {
			int rc = wait_reset_done(hdc, HD1_DRVSEL);
			if (rc < 0) {
				*slaveif = HDIF_NONE;
			}
		}

		/* Determine interface types */
		if (*masterif != HDIF_NONE) {
			*masterif = get_interface_type(hdc, HD0_DRVSEL);
		}
		if (*slaveif != HDIF_NONE) {
			*slaveif = get_interface_type(hdc, HD1_DRVSEL);
		}
	}
	else {
		/*
		 * No IDE probing, assume both devices connected to force selection
		 * by BIOS settings
		 */
		*masterif = HDIF_ATA;
		*slaveif = HDIF_ATA;
	}

	/* Enable interrupts */
	res = irq_attach(hdc->irq, hdc_handler, 0, hdc, "ide");
	if (res < 0) {
		return res;
	}

	outb(HDDC_HD15, hdc->iobase + HDC_CONTROL);
	idedelay();

	return 0;
}

static int ide_devnode_create(dev_t *dev_number) {
	node_t *dev_node;

	char dev_path[MAX_LENGTH_PATH_NAME];
	char dev_name[MAX_LENGTH_FILE_NAME];

	*dev_path = 0;
	strcat(dev_path, "/dev/");
	dev_name[0] = 's';
	dev_name[1] = 'd';
	dev_name[2] = 'a' + *dev_number;
	dev_name[3] = 0;
	strcat(dev_path, dev_name);

	if (NULL == (dev_node = vfs_add_path(dev_path, NULL))) {
		if (NULL == (dev_node = vfs_find_node(dev_path, NULL))) {
			return NODEV;
		}
		else {
			return *dev_number;
		}
	}

	dev_node->dev_type = (void *) device(*dev_number)->driver;
	dev_node->dev_attr = (void *) dev_number;
	device(*dev_number)->dev_node = dev_node;

	return *dev_number;
}

static void setup_hd(hd_t *hd, hdc_t *hdc, char *devname,
						int drvsel, int udmasel, int iftype, int numslot) {
	/* static int udma_speed[] = {16, 25, 33, 44, 66, 100}; */

	int rc;
	double size;

	/* Initialize drive block */
	memset(hd, 0, sizeof(hd_t));
	hd->hdc = hdc;
	hd->drvsel = drvsel;
	hd->iftype = iftype;

	/* Get info block from device */
	rc = hd_identify(hd);
	if (rc < 0) {
		/* Try other interface type */
		if (hd->iftype == HDIF_ATA) {
			hd->iftype = HDIF_ATAPI;
		}
		else if (hd->iftype == HDIF_ATAPI) {
			hd->iftype = HDIF_ATA;
		}
		rc = hd_identify(hd);
		if (rc < 0) {
			/* kprintf("hd: device %s not responding, ignored.\n", devname);*/
			ide.drive[numslot] = NULL;
			return;
		}
	}
	ide.drive[numslot]  = (hd_t *)hd;

	/* Determine UDMA mode */
	if (!hdc->bmregbase) {
		hd->udmamode = -1;
	}
	else if ((hd->param.valid & 4) &&
			(hd->param.dmaultra & (hd->param.dmaultra >> 8) & 0x3F)) {
		if ((hd->param.dmaultra >> 13) & 1) {
			hd->udmamode = 5; /* UDMA 100 */
		}
		else if ((hd->param.dmaultra >> 12) & 1) {
			hd->udmamode = 4; /* UDMA 66 */
		}
		else if ((hd->param.dmaultra >> 11) & 1) {
			hd->udmamode = 3; /* UDMA 44 */
		}
		else if ((hd->param.dmaultra >> 10) & 1) {
			hd->udmamode = 2; /* UDMA 33 */
		}
		else if ((hd->param.dmaultra >> 9) & 1) {
			hd->udmamode = 1; /* UDMA 25 */
		}
		else {
			hd->udmamode = 0; /* UDMA 16 */
		}
	}
	else {
		hd->udmamode = -1;
	}

	/* Set multi-sector mode if drive supports it */
	if (hd->multsect > 1) {
		rc = hd_cmd(hd, HDCMD_SETMULT, 0, hd->multsect);
		if (rc < 0) {
			/* kprintf(KERN_WARNING "hd: unable to set multi sector mode\n"); */
			hd->multsect = 1;
		}
	}

	/* Enable UDMA for drive if it supports it. */
	if (hd->udmamode != -1) {
		/* Enable drive in bus master status register */
		int dmastat = inb(hdc->bmregbase + BM_STATUS_REG);
		outb(dmastat | udmasel, hdc->bmregbase + BM_STATUS_REG);

		/* Set feature in IDE controller */
		rc = hd_cmd(hd, HDCMD_SETFEATURES, HDFEAT_XFER_MODE,
				HDXFER_MODE_UDMA | hd->udmamode);
		/*
		if (rc < 0) {
			kprintf(KERN_WARNING "hd: unable to enable UDMA mode\n");
		}
		*/
	}

	/* Enable read ahead and write caching if supported */
	if (hd->param.csfo & 2) {
		hd_cmd(hd, HDCMD_SETFEATURES, HDFEAT_ENABLE_RLA, 0);
	}
	if (hd->param.csfo & 1) {
		hd_cmd(hd, HDCMD_SETFEATURES, HDFEAT_ENABLE_WCACHE, 0);
	}

	/* Make new device */
	if (hd->media == IDE_DISK) {
		if (hd->udmamode != -1) {
			hd->devno = dev_make(devname, &harddisk_udma_driver, hd);
		}
		else {
			hd->devno = dev_make(devname, &harddisk_pio_driver, hd);
		}
	}
	else if (hd->media == IDE_CDROM) {
		hd->devno = dev_make("cd#", &cdrom_pio_driver, hd);
	}
	else {
		/* kprintf(KERN_ERR "%s: unknown media type 0x%02x (iftype %d, config 0x%04x)\n", devname, hd->media, hd->iftype, hd->param.config); */
		return;
	}

	if(0 <= hd->devno) {
		if(0 > ide_devnode_create(&hd->devno)) {
			dev_destroy (hd->devno);
			return;
		}
		size =
		(double) hd->param.cylinders *
		(double) hd->param.heads *
		(double) hd->param.unfbytes *
		(double) (hd->param.sectors + 1);
		device(hd->devno)->size = (size_t) size;
	}

	if (hd->media == IDE_DISK) {
		create_partitions(hd);
	}
	else {
		hd->blks = 0;
	}
	/*
	kprintf(KERN_INFO "%s: %s", device(hd->devno)->name, hd->param.model);
	if (hd->size > 0) {
		kprintf(" (%d MB)", hd->size);
	}
	if (hd->lba) {
		kprintf(", LBA");
	}
	if (hd->udmamode != -1) {
		kprintf(", UDMA%d", udma_speed[hd->udmamode]);
	}
	if (hd->param.csfo & 2) {
		kprintf(", read ahead");
	}
	if (hd->param.csfo & 1) {
		kprintf(", write cache");
	}
	if (hd->udmamode == -1 && hd->multsect > 1) {
		kprintf(", %d sects/intr", hd->multsect);
	}
	if (!hd->use32bits) {
		kprintf(", word I/O");
	}
	if (hd->hdc->bmregbase) {
		kprintf(", bmregbase=0x%x", hd->hdc->bmregbase);
	}
	kprintf("\n");
	*/
}

EMBOX_UNIT_INIT(unit_init);

int unit_init(void) {
	int numhd;
	int rc;
	int masterif;
	int slaveif;

	numhd = 4;
	if (numhd >= 1)  {
		/*
		rc = setup_hdc(&hdctab[0], HDC0_IOBASE, HDC0_IRQ,
						ide ? bmiba : 0, &masterif, &slaveif);
		*/
		rc = setup_hdc(&hdctab[0], HDC0_IOBASE, HDC0_IRQ, 0, &masterif, &slaveif);
		if (rc < 0) {
		/*kprintf(KERN_ERR "hd: error %d initializing primary IDE controller\n", rc); */
		}
		else {
			if (numhd >= 1 && masterif > HDIF_UNKNOWN) {
				setup_hd(&hdtab[0], &hdctab[0], "hd0",
						HD0_DRVSEL, BM_SR_DRV0, masterif, 0);
			}
			if (numhd >= 2 && slaveif > HDIF_UNKNOWN) {
				setup_hd(&hdtab[1], &hdctab[0], "hd1",
						HD1_DRVSEL, BM_SR_DRV1, slaveif, 1);
			}
		}
	}

	if (numhd >= 3) {
		/*
		rc = setup_hdc(&hdctab[1], HDC1_IOBASE,
						HDC1_IRQ, ide ? bmiba + 8 : 0, &masterif, &slaveif);
		*/
		rc = setup_hdc(&hdctab[1], HDC1_IOBASE,
				HDC1_IRQ, 0, &masterif, &slaveif);
		if (rc < 0) {
			/* kprintf(KERN_ERR "hd: error %d initializing secondary IDE controller\n", rc); */
		}
		else {
			if (numhd >= 3 && masterif > HDIF_UNKNOWN) {
				setup_hd(&hdtab[2], &hdctab[1], "hd2",
						HD0_DRVSEL, BM_SR_DRV0, masterif, 2);
			}
			if (numhd >= 4 && slaveif > HDIF_UNKNOWN) {
				setup_hd(&hdtab[3], &hdctab[1], "hd3",
						HD1_DRVSEL, BM_SR_DRV1, slaveif, 3);
			}
		}
	}
	return 0;
}

slot_t *get_ide_drive(void) {
	return &ide;
}
