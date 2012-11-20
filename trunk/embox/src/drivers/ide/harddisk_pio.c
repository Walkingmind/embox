/**
 * @file
 * @brief
 *
 * @date 26.10.2012
 * @author Andrey Gazukin
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
#include <mem/phymem.h>
#include <util/indexator.h>

extern int hd_ioctl(block_dev_t *dev, int cmd, void *args, size_t size);

static int hd_read_pio(block_dev_t *dev, char *buffer, size_t count, blkno_t blkno) {
	hd_t *hd;
	hdc_t *hdc;
	int sectsleft;
	int nsects;
	int result;
	char *bufp;

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;
	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;

	while (sectsleft > 0) {
		/* Select drive */
		ide_select_drive(hd);

		/* Wait for controller ready */
		result = ide_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
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

		/* Prepare transfer */
		hdc->bufp = bufp;
		hdc->nsects = nsects;
		hdc->result = 0;
		hdc->dir = HD_XFER_READ;
		hdc->active = hd;

		hd_setup_transfer(hd, blkno, nsects);
		outb(hd->multsect > 1 ? HDCMD_MULTREAD : HDCMD_READ,
				hdc->iobase + HDC_COMMAND);

    	/* Wait until data read */
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

	if (count == 0) {
		return 0;
	}
	bufp = (char *) buffer;
	hd = (hd_t *) dev->privdata;
	hdc = hd->hdc;
	sectsleft = count / SECTOR_SIZE;


	while (sectsleft > 0) {
		/* Select drive */
		ide_select_drive(hd);

		/* Wait for controller ready */
		result = ide_wait(hdc, HDCS_DRDY, HDTIMEOUT_DRDY);
		if (result != 0) {
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

		/* Prepare transfer */
		hdc->bufp = bufp;
		hdc->nsects = nsects;
		hdc->result = 0;
		hdc->dir = HD_XFER_WRITE;
		hdc->active = hd;

		hd_setup_transfer(hd, blkno, nsects);
		outb(hd->multsect > 1 ? HDCMD_MULTWRITE : HDCMD_WRITE,
				hdc->iobase + HDC_COMMAND);

		/* Wait for data ready */
		if (!(inb(hdc->iobase + HDC_ALT_STATUS) & HDCS_DRQ)) {
			result = ide_wait(hdc, HDCS_DRQ, HDTIMEOUT_DRQ);
			if (result != 0) {
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

		/* Wait until data written */
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

	/* Cleanup */
	hdc->dir = HD_XFER_IDLE;
	hdc->active = NULL;
	result = hdc->result;

	return result == 0 ? count : result;
}


static block_dev_driver_t idedisk_pio_driver = {
	"idedisk_drv",
	hd_ioctl,
	hd_read_pio,
	hd_write_pio
};

static int idedisk_init (void *args) {
	slot_t *ide;
	hd_t *drive;
	dev_t name_idx;
	double size;
	char   path[MAX_LENGTH_PATH_NAME];

	ide = ide_get_drive();

	for(int i = 0; i < 4; i++) {
		if(NULL == ide->drive[i]) {
			continue;
		}
		else {
			drive = (hd_t *) ide->drive[i];
			/* Make new device */
			if ((drive->media == IDE_DISK) && (drive->udmamode == -1)) {
				*path = 0;
				strcat(path, "/dev/");
				name_idx = (dev_t) index_alloc(idedisk_idx, INDEX_ALLOC_MIN);
				drive->dev_id = block_dev_create(strcat(path, "hd*"),
						&idedisk_pio_driver, drive, &name_idx);

				if(NULL != drive->dev_id) {
					size = (double) drive->param.cylinders *
						   (double) drive->param.heads *
						   (double) drive->param.unfbytes *
						   (double) (drive->param.sectors + 1);
					block_dev(drive->dev_id)->size = (size_t) size;
				}
				else {
					return -1;
				}

				create_partitions(drive);
			}
			else {
				continue;
			}
		}
	}
	return 0;
}

EMBOX_BLOCK_DEV("idedisk", &idedisk_pio_driver, idedisk_init);
