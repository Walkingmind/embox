/**
 * @file
 * @brief
 *
 * @date 28.03.2012
 * @author Andrey Gazukin
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <util/array.h>
#include <mem/misc/pool.h>
#include <mem/phymem.h>

#include <fs/fs_drv.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <fs/fat.h>
#include <fs/mount.h>

#include <embox/block_dev.h>

#include <framework/mod/options.h>

static uint8_t sector_buff[SECTOR_SIZE];
static uint32_t bytecount;

/* fat filesystem description pool */
POOL_DEF(fat_fs_pool, struct fat_fs_description, OPTION_GET(NUMBER,fat_descriptor_quantity));

/* fat file description pool */
POOL_DEF(fat_file_pool, struct _fat_file_description, OPTION_GET(NUMBER,inode_quantity));

#define LABEL "EMBOX_DISK\0"
#define SYSTEM "FAT12"

char bootcode[130] =
	{ 0x0e, 0x1f, 0xbe, 0x5b, 0x7c, 0xac, 0x22, 0xc0, 0x74, 0x0b,
	  0x56, 0xb4, 0x0e, 0xbb, 0x07, 0x00, 0xcd, 0x10, 0x5e, 0xeb,
	  0xf0, 0x32, 0xe4, 0xcd, 0x16, 0xcd, 0x19, 0xeb, 0xfe, 0x54,
	  0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x6e, 0x6f, 0x74,
	  0x20, 0x61, 0x20, 0x62, 0x6f, 0x6f, 0x74, 0x61, 0x62, 0x6c,
	  0x65, 0x20, 0x64, 0x69, 0x73, 0x6b, 0x2e, 0x20, 0x20, 0x50,
	  0x6c, 0x65, 0x61, 0x73, 0x65, 0x20, 0x69, 0x6e, 0x73, 0x65,
	  0x72, 0x74, 0x20, 0x61, 0x20, 0x62, 0x6f, 0x6f, 0x74, 0x61,
	  0x62, 0x6c, 0x65, 0x20, 0x66, 0x6c, 0x6f, 0x70, 0x70, 0x79,
	  0x20, 0x61, 0x6e, 0x64, 0x0d, 0x0a, 0x70, 0x72, 0x65, 0x73,
	  0x73, 0x20, 0x61, 0x6e, 0x79, 0x20, 0x6b, 0x65, 0x79, 0x20,
	  0x74, 0x6f, 0x20, 0x74, 0x72, 0x79, 0x20, 0x61, 0x67, 0x61,
	  0x69, 0x6e, 0x20, 0x2e, 0x2e, 0x2e, 0x20, 0x0d, 0x0a, 0x00 };


static fs_drv_t fatfs_drv;
static int fat_write_sector(void *fdsc, uint8_t *buffer,
		uint32_t sector, uint32_t count);
static int fat_read_sector(void *fdsc, uint8_t *buffer,
		uint32_t sector, uint32_t count);
static uint32_t fat_get_next(void *fd,
		p_dir_info_t dirinfo, p_dir_ent_t dirent);
static int fat_create_dir_entry(char *dir_name);


static int fatfs_partition(void *fdes) {
	lbr_t lbr;
	size_t num_sect;
	uint16_t bytepersec, secperfat, rootentries;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdes;

	memset ((void *)&lbr.jump, 0x00, SECTOR_SIZE); /* set all by ZERO */
	lbr.jump[0] = 0xeb;
	lbr.jump[1] = 0x3c;
	lbr.jump[2] = 0x90;
	memset ((void *)&lbr.oemid, 0x45, 0x08); /* EEEEEEEE */
	bytepersec = SECTOR_SIZE;
	lbr.bpb.bytepersec_l = (uint8_t)(bytepersec & 0xFF);
	lbr.bpb.bytepersec_h = (uint8_t)((bytepersec & 0xFF00) >> 8);
	lbr.bpb.secperclus = 0x04;
	lbr.bpb.reserved_l = 0x01; /* reserved sectors */
	lbr.bpb.numfats = 0x02;/* 2 FAT copy */
	lbr.bpb.mediatype = 0xF8;
	lbr.bpb.secpertrk_l = 0x3f;
	lbr.bpb.heads_l = 0xff;
	lbr.sig_55 = 0x55;
	lbr.sig_aa = 0xAA;
	memcpy(lbr.ebpb.ebpb.system + 8, bootcode, 130);

	num_sect = block_dev(fd->fs->dev_id)->size / bytepersec;
	if (0xFFFF > num_sect)	{
		lbr.bpb.sectors_s_l = (uint8_t)(0x00000FF & num_sect);
		lbr.bpb.sectors_s_h = (uint8_t)(0x00000FF & (num_sect >> 8));
	}
	else {
		lbr.bpb.sectors_l_0 = (uint8_t)(0x00000FF & num_sect );
		lbr.bpb.sectors_l_1 = (uint8_t)(0x00000FF & (num_sect >> 8));
		lbr.bpb.sectors_l_2 = (uint8_t)(0x00000FF & (num_sect >> 16));
		lbr.bpb.sectors_l_3 = (uint8_t)(0x00000FF & (num_sect >> 24));
	}

	secperfat = (uint16_t)(0xFFFF & (num_sect / bytepersec));
	if(0 == secperfat) {
		secperfat++;
	}
	lbr.bpb.secperfat_l = (uint8_t)(0x00FF & secperfat );
	lbr.bpb.secperfat_h = (uint8_t)(0x00FF & (secperfat >> 8));
	rootentries = 0x0200; /* 512 for FAT16 */
	lbr.bpb.rootentries_l = (uint8_t)(0x00FF & rootentries );
	lbr.bpb.rootentries_h = (uint8_t)(0x00FF & (rootentries >> 8));
	lbr.ebpb.ebpb.signature = 0x29;
	lbr.ebpb.ebpb.serial_0 = 0x81;
	lbr.ebpb.ebpb.serial_1 = 0xdb;
	lbr.ebpb.ebpb.serial_2 = 0xf7;
	lbr.ebpb.ebpb.serial_3 = 0xbb;
	strcpy ((void *)&lbr.ebpb.ebpb.label, LABEL);
	strcpy ((void *)&lbr.ebpb.ebpb.system, SYSTEM);
	memcpy ((void *)&sector_buff[0], (void *)&lbr, SECTOR_SIZE);

	return fat_write_sector(fd, sector_buff, 0, 1);
}


/**
 *	Get starting sector# of specified partition on drive #unit
 *	NOTE: This code ASSUMES an MBR on the disk.
 *	p_scratchsector should point to a SECTOR_SIZE scratch area
 *	Returns 0xffffffff for any error.
 *	If pactive is non-NULL, this function also returns partition active flag.
 *	If pptype is non-NULL, this function also returns the partition type.
 *	If psize is non-NULL, this function also returns the partition size.
 */
static uint32_t fat_get_ptn_start(void *fd,
		uint8_t *p_scratchsector,	uint8_t pnum, uint8_t *pactive,
		uint8_t *pptype, uint32_t *psize) {
	uint32_t result;
	p_mbr_t mbr = (p_mbr_t) p_scratchsector;

	/* DOS ptable supports maximum 4 partitions */
	if (pnum > 3) {
		return DFS_ERRMISC;
	}

	/* Read MBR from target media */
	if (fat_read_sector(fd, p_scratchsector, 0, 1)) {
		return DFS_ERRMISC;
	}
	/* check if that a lbr */
	if((mbr->bootcode[0] == 0xeb) &&
	   (mbr->bootcode[1] == 0x3c) &&
	   (mbr->bootcode[2] == 0x90)) {
		return 0;
	}

	result = (uint32_t) mbr->ptable[pnum].start_0 |
	  (((uint32_t) mbr->ptable[pnum].start_1) << 8) |
	  (((uint32_t) mbr->ptable[pnum].start_2) << 16) |
	  (((uint32_t) mbr->ptable[pnum].start_3) << 24);

	if (pactive) {
		*pactive = mbr->ptable[pnum].active;
	}

	if (pptype) {
		*pptype = mbr->ptable[pnum].type;
	}

	if (psize) {
		*psize = (uint32_t) mbr->ptable[pnum].size_0 |
		  (((uint32_t) mbr->ptable[pnum].size_1) << 8) |
		  (((uint32_t) mbr->ptable[pnum].size_2) << 16) |
		  (((uint32_t) mbr->ptable[pnum].size_3) << 24);
	}

	return result;
}


/**
 * Retrieve volume info from BPB and store it in a vol_info_t structure
 * You must provide the unit and starting sector of the filesystem, and
 * a pointer to a sector buffer for scratch
 * Attempts to read BPB and glean information about the FS from that.
 * Returns 0 OK, nonzero for any error.
 */
static uint32_t fat_get_vol_info(void *fd,
		uint8_t *p_scratchsector,	uint32_t startsector) {
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;
	p_lbr_t lbr = (p_lbr_t) p_scratchsector;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;
	volinfo->startsector = startsector;

	if(fat_read_sector(fd, p_scratchsector, startsector, 1)) {
		return DFS_ERRMISC;
	}

	volinfo->secperclus = lbr->bpb.secperclus;
	volinfo->reservedsecs = (uint16_t) lbr->bpb.reserved_l |
		  (((uint16_t) lbr->bpb.reserved_h) << 8);

	volinfo->numsecs =  (uint16_t) lbr->bpb.sectors_s_l |
		  (((uint16_t) lbr->bpb.sectors_s_h) << 8);

	if (!volinfo->numsecs) {
		volinfo->numsecs = (uint32_t) lbr->bpb.sectors_l_0 |
		  (((uint32_t) lbr->bpb.sectors_l_1) << 8) |
		  (((uint32_t) lbr->bpb.sectors_l_2) << 16) |
		  (((uint32_t) lbr->bpb.sectors_l_3) << 24);
	}

	/**
	 * If secperfat is 0, we must be in a FAT32 volume; get secperfat
	 * from the FAT32 EBPB. The volume label and system ID string are also
	 * in different locations for FAT12/16 vs FAT32.
	 */
	volinfo->secperfat =  (uint16_t) lbr->bpb.secperfat_l |
		  (((uint16_t) lbr->bpb.secperfat_h) << 8);
	if (!volinfo->secperfat) {
		volinfo->secperfat = (uint32_t) lbr->ebpb.ebpb32.fatsize_0 |
		  (((uint32_t) lbr->ebpb.ebpb32.fatsize_1) << 8) |
		  (((uint32_t) lbr->ebpb.ebpb32.fatsize_2) << 16) |
		  (((uint32_t) lbr->ebpb.ebpb32.fatsize_3) << 24);

		memcpy(volinfo->label, lbr->ebpb.ebpb32.label, MSDOS_NAME);
		volinfo->label[11] = 0;

	}
	else {
		memcpy(volinfo->label, lbr->ebpb.ebpb.label, MSDOS_NAME);
		volinfo->label[11] = 0;

	}

	/* note: if rootentries is 0, we must be in a FAT32 volume. */
	volinfo->rootentries =  (uint16_t) lbr->bpb.rootentries_l |
		  (((uint16_t) lbr->bpb.rootentries_h) << 8);

	/* after extracting raw info we perform some useful precalculations */
	volinfo->fat1 = startsector + volinfo->reservedsecs;

	/**
	 * The calculation below is designed to round up the root directory size
	 * for FAT12/16 and to simply ignore the root directory for FAT32, since
	 * it's a normal, expandable file in that situation.
	 */

	if (volinfo->rootentries) {
		volinfo->rootdir = volinfo->fat1 + (volinfo->secperfat * 2);
		volinfo->dataarea = volinfo->rootdir + (((volinfo->rootentries * 32) +
				(SECTOR_SIZE - 1)) / SECTOR_SIZE);
	}
	else {
		volinfo->dataarea = volinfo->fat1 + (volinfo->secperfat * 2);
		volinfo->rootdir = (uint32_t) lbr->ebpb.ebpb32.root_0 |
		  (((uint32_t) lbr->ebpb.ebpb32.root_1) << 8) |
		  (((uint32_t) lbr->ebpb.ebpb32.root_2) << 16) |
		  (((uint32_t) lbr->ebpb.ebpb32.root_3) << 24);
	}

	/*
	 * Calculate number of clusters in data area and infer FAT type from
	 * this information.
	 */
	if(0 == volinfo->secperclus) {
		volinfo->numclusters = 0;
		return DFS_ERRMISC;
	}
	else {
		volinfo->numclusters =
				(volinfo->numsecs - volinfo->dataarea) / volinfo->secperclus;
	}

	/* try to set FAT type by filesystem ID */
	if ((0 == strcmp((const char *)lbr->ebpb.ebpb.system, "FAT12")) ||
		(0 == strcmp((const char *)lbr->ebpb.ebpb32.system, "FAT12"))) {
		volinfo->filesystem = FAT12;
	}
	else if ((0 == strcmp((const char *)lbr->ebpb.ebpb.system, "FAT16")) ||
			(0 == strcmp((const char *)lbr->ebpb.ebpb32.system, "FAT16"))) {
		volinfo->filesystem = FAT16;
	}
	else if ((0 == strcmp((const char *)lbr->ebpb.ebpb.system, "FAT32")) ||
			(0 == strcmp((const char *)lbr->ebpb.ebpb32.system, "FAT32"))) {
		volinfo->filesystem = FAT32;
	}
	/* set FAT type by size */
	else if (volinfo->numclusters < 4085) {
		volinfo->filesystem = FAT12;
	}
	else if (volinfo->numclusters < 65525) {
		volinfo->filesystem = FAT16;
	}
	else {
		volinfo->filesystem = FAT32;
	}

	return DFS_OK;
}

/*
 *	Fetch FAT entry for specified cluster number You must provide a scratch
 *	buffer for one sector (SECTOR_SIZE) and a populated vol_info_t
 *	Returns a FAT32 BAD_CLUSTER value for any error, otherwise the contents
 *	of the desired FAT entry.
 *	p_scratchcache should point to a UINT32. This variable caches the physical
 *	sector number last read into the scratch buffer for performance
 *	enhancement reasons.
 */
static uint32_t fat_get_fat_(void *fd, uint8_t *p_scratch,
		uint32_t *p_scratchcache, uint32_t cluster) {
	uint32_t offset, sector, result;
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;

	if (volinfo->filesystem == FAT12) {
		offset = cluster + (cluster / 2);
	}
	else if (volinfo->filesystem == FAT16) {
		offset = cluster * 2;
	}
	else if (volinfo->filesystem == FAT32) {
		offset = cluster * 4;
	}
	else
		return 0x0ffffff7;	/* FAT32 bad cluster */

	/*
	 * at this point, offset is the BYTE offset of the desired sector from
	 * the start of the FAT. Calculate the physical sector containing this
	 *  FAT entry.
	 */
	sector = ldiv(offset, SECTOR_SIZE).quot + volinfo->fat1;

	/* If this is not the same sector we last read, then read it into RAM */
	if (sector != *p_scratchcache) {
		if(fat_read_sector(fd, p_scratch, sector, 1)) {
			/*
			 * avoid anyone assuming that this cache value is still valid,
			 * which might cause disk corruption
			 */
			*p_scratchcache = 0;
			return 0x0ffffff7;	/* FAT32 bad cluster */
		}
		*p_scratchcache = sector;
	}

	/*
	 * At this point, we "merely" need to extract the relevant entry.
	 * This is easy for FAT16 and FAT32, but a royal PITA for FAT12 as
	 * a single entry may span a sector boundary. The normal way around this is
	 * always to read two FAT sectors, but that luxury is (by design intent)
	 * unavailable to DOSFS.
	 */
	offset = ldiv(offset, SECTOR_SIZE).rem;

	if (volinfo->filesystem == FAT12) {
		/* Special case for sector boundary - Store last byte of current sector
		 * Then read in the next sector and put the first byte of that sector
		 * into the high byte of result.
		 */
		if (offset == SECTOR_SIZE - 1) {
			result = (uint32_t) p_scratch[offset];
			sector++;
			if(fat_read_sector(fd, p_scratch, sector, 1)) {
				/*
				 * avoid anyone assuming that this cache value is still valid,
				 *  which might cause disk corruption
				 */
				*p_scratchcache = 0;
				return 0x0ffffff7;	/* FAT32 bad cluster */
			}
			*p_scratchcache = sector;
			result |= ((uint32_t) p_scratch[0]) << 8;
		}
		else {
			result = (uint32_t) p_scratch[offset] |
			  ((uint32_t) p_scratch[offset+1]) << 8;
		}
		if (cluster & 1) {
			result = result >> 4;
		}
		else {
			result = result & 0xfff;
		}
	}
	else if (volinfo->filesystem == FAT16) {
		result = (uint32_t) p_scratch[offset] |
		  ((uint32_t) p_scratch[offset+1]) << 8;
	}
	else if (volinfo->filesystem == FAT32) {
		result = ((uint32_t) p_scratch[offset] |
		  ((uint32_t) p_scratch[offset+1]) << 8 |
		  ((uint32_t) p_scratch[offset+2]) << 16 |
		  ((uint32_t) p_scratch[offset+3]) << 24) & 0x0fffffff;
	}
	else {
		result = 0x0ffffff7;	/* FAT32 bad cluster */
	}
	return result;
}


/*
 * Set FAT entry for specified cluster number
 * You must provide a scratch buffer for one sector (SECTOR_SIZE)
 * and a populated vol_info_t Returns DFS_ERRMISC for any error, otherwise
 * DFS_OK p_scratchcache should point to a UINT32. This variable caches the
 * physical sector number last read into the scratch buffer for performance
 * enhancement reasons.
 *
 * NOTE: This code is HIGHLY WRITE-INEFFICIENT, particularly for flash media.
 * Considerable performance gains can be realized by caching the sector.
 * However this is difficult to achieve on FAT12 without requiring 2 sector
 * buffers of scratch space, and it is a design requirement of this code to
 * operate on a single 512-byte scratch. If you are operating DOSFS over flash,
 * you are strongly advised to implement a writeback cache in your physical
 * I/O driver. This will speed up your code significantly and will
 * also conserve power and flash write life.
 */

static uint32_t fat_set_fat_(void *fd, uint8_t *p_scratch,
		uint32_t *p_scratchcache, uint32_t cluster, uint32_t new_contents) {
	uint32_t offset, sector, result;
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;

	if (volinfo->filesystem == FAT12) {
		offset = cluster + (cluster / 2);
		new_contents &=0xfff;
	}
	else if (volinfo->filesystem == FAT16) {
		offset = cluster * 2;
		new_contents &=0xffff;
	}
	else if (volinfo->filesystem == FAT32) {
		offset = cluster * 4;
		new_contents &=0x0fffffff;	/* FAT32 is really "FAT28" */
	}
	else
		return DFS_ERRMISC;

	/*
	 * at this point, offset is the BYTE offset of the desired sector from
	 * the start of the FAT.
	 * Calculate the physical sector containing this FAT entry.
	 */
	sector = ldiv(offset, SECTOR_SIZE).quot + volinfo->fat1;

	/* If this is not the same sector we last read, then read it into RAM */
	if (sector != *p_scratchcache) {
		if(fat_read_sector(fd, p_scratch, sector, 1)) {
			/*
			 * avoid anyone assuming that this cache value is still valid,
			 * which might cause disk corruption
			 */
			*p_scratchcache = 0;
			return DFS_ERRMISC;
		}
		*p_scratchcache = sector;
	}

	/*
	 * At this point, we "merely" need to extract the relevant entry.
	 * This is easy for FAT16 and FAT32, but a royal PITA for FAT12 as a
	 * single entry may span a sector boundary. The normal way around this
	 * is always to read two FAT sectors, but that luxury is (by design intent)
	 * unavailable to DOSFS.
	 */
	offset = ldiv(offset, SECTOR_SIZE).rem;

	if (volinfo->filesystem == FAT12) {

		/*
		 * If this is an odd cluster, pre-shift the desired new contents
		 * 4 bits to make the calculations below simpler
		 */
		if (cluster & 1)
			new_contents = new_contents << 4;

		/* Special case for sector boundary */
		if (offset == SECTOR_SIZE - 1) {

			/* Odd cluster: High 12 bits being set */
			if (cluster & 1) {
				p_scratch[offset] = (p_scratch[offset] & 0x0f) |
						(new_contents & 0xf0);
			}
			/* Even cluster: Low 12 bits being set */
			else {
				p_scratch[offset] = new_contents & 0xff;
			}
			result = fat_write_sector(fd, p_scratch, *p_scratchcache, 1);
			/* mirror the FAT into copy 2 */
			if (DFS_OK == result) {
				result = fat_write_sector(fd, p_scratch,
						(*p_scratchcache) + volinfo->secperfat, 1);
			}

			/*
			 * If we wrote that sector OK, then read in the subsequent sector
			 * and poke the first byte with the remainder of this FAT entry.
			 */
			if (DFS_OK == result) {
				(*p_scratchcache)++;
				result = fat_read_sector(fd, p_scratch, *p_scratchcache, 1);
				if (DFS_OK == result) {
					/* Odd cluster: High 12 bits being set*/
					if (cluster & 1) {
						p_scratch[0] = new_contents & 0xff00;
					}
					/* Even cluster: Low 12 bits being set */
					else {
						p_scratch[0] = (p_scratch[0] & 0xf0) |
								(new_contents & 0x0f);
					}
					result = fat_write_sector(fd, p_scratch,
							*p_scratchcache, 1);
					/* mirror the FAT into copy 2 */
					if (DFS_OK == result) {
						result = fat_write_sector(fd, p_scratch,
								(*p_scratchcache)+volinfo->secperfat, 1);
					}
				}
				else {
					/*
					 * avoid anyone assuming that this cache value is still
					 * valid, which might cause disk corruption
					 */
					*p_scratchcache = 0;
				}
			}
		}

		/*
		 * Not a sector boundary. But we still have to worry about if it's an
		 * odd or even cluster number.
		 */
		else {
			/* Odd cluster: High 12 bits being set */
			if (cluster & 1) {
				p_scratch[offset] = (p_scratch[offset] & 0x0f) |
						(new_contents & 0xf0);
				p_scratch[offset + 1] = (new_contents & 0xff00) >> 8;
			}
			/* Even cluster: Low 12 bits being set */
			else {
				p_scratch[offset] = new_contents & 0xff;
				p_scratch[offset+1] = (p_scratch[offset+1] & 0xf0) |
						((new_contents & 0x0f00) >> 8);
			}
			result = fat_write_sector(fd, p_scratch, *p_scratchcache, 1);
			/* mirror the FAT into copy 2 */
			if (DFS_OK == result) {
				result = fat_write_sector(fd, p_scratch,
						(*p_scratchcache) + volinfo->secperfat, 1);
			}
		}
	}
	else if (volinfo->filesystem == FAT16) {
		p_scratch[offset] = (new_contents & 0xff);
		p_scratch[offset+1] = (new_contents & 0xff00) >> 8;
		result = fat_write_sector(fd, p_scratch, *p_scratchcache, 1);
		/* mirror the FAT into copy 2 */
		if (DFS_OK == result) {
			result = fat_write_sector(fd, p_scratch,
					(*p_scratchcache) + volinfo->secperfat, 1);
		}
	}
	else if (volinfo->filesystem == FAT32) {
		p_scratch[offset] = (new_contents & 0xff);
		p_scratch[offset + 1] = (new_contents & 0xff00) >> 8;
		p_scratch[offset + 2] = (new_contents & 0xff0000) >> 16;
		p_scratch[offset + 3] = (p_scratch[offset  + 3] & 0xf0) |
				((new_contents & 0x0f000000) >> 24);
		/*
		 * Note well from the above: Per Microsoft's guidelines we preserve the
		 * upper 4 bits of the FAT32 cluster value. It's unclear what these
		 * bits will be used for;
		 * in every example I've encountered they are always zero.
		 */
		result = fat_write_sector(fd, p_scratch, *p_scratchcache, 1);
		/* mirror the FAT into copy 2 */
		if (DFS_OK == result) {
			result = fat_write_sector(fd, p_scratch,
					(*p_scratchcache) + volinfo->secperfat, 1);
		}
	}
	else {
		result = DFS_ERRMISC;
	}

	return result;
}


/*
 * 	Find the first unused FAT entry
 * 	You must provide a scratch buffer for one sector (SECTOR_SIZE) and a
 * 	populated vol_info_t Returns a FAT32 BAD_CLUSTER value for any error,
 * 	otherwise the contents of the desired FAT entry.
 * 	Returns FAT32 bad_sector (0x0ffffff7) if there is no free cluster available
 */
static uint32_t fat_get_free_fat_(void *fd, uint8_t *p_scratch) {
	uint32_t i, result = 0xffffffff, p_scratchcache = 0;
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;

	/*
	 * Search starts at cluster 2, which is the first usable cluster
	 * NOTE: This search can't terminate at a bad cluster, because there might
	 * legitimately be bad clusters on the disk.
	 */
	for (i = 2; i < volinfo->numclusters; i++) {
		result = fat_get_fat_(fd, p_scratch, &p_scratchcache, i);
		if (!result) {
			return i;
		}
	}
	return 0x0ffffff7;		/* Can't find a free cluster */
}


/*
 * Open a directory for enumeration by fat_get_nextDirEnt
 * You must supply a populated vol_info_t (see fat_get_vol_info)
 * The empty string or a string containing only the directory separator are
 * considered to be the root directory.
 * Returns 0 OK, nonzero for any error.
 */
static uint32_t fat_open_dir(void *fd,
		uint8_t *dirname, p_dir_info_t dirinfo) {
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;
	/* Default behavior is a regular search for existing entries */
	dirinfo->flags = 0;

	if ((!strlen((char *) dirname)) || (((strlen((char *) dirname) == 1) &&
			(dirname[0] == DIR_SEPARATOR)))) {
		if (volinfo->filesystem == FAT32) {
			dirinfo->currentcluster = volinfo->rootdir;
			dirinfo->currentsector = 0;
			dirinfo->currententry = 0;

			/* read first sector of directory */
			return fat_read_sector(fd, dirinfo->p_scratch, volinfo->dataarea +
					((volinfo->rootdir - 2) * volinfo->secperclus), 1);
		}
		else {
			dirinfo->currentcluster = 0;
			dirinfo->currentsector = 0;
			dirinfo->currententry = 0;

			/* read first sector of directory */
			return fat_read_sector(fd, dirinfo->p_scratch,
					volinfo->rootdir, 1);
		}
	}

	/*
	 * This is not the root directory.
	 * We need to find the start of this subdirectory. We do this by devious
	 * means, using our own companion function fat_get_next.
	 */
	else {
		uint8_t tmpfn[12];
		uint8_t *ptr = dirname;
		uint32_t result;
		dir_ent_t de;

		if (volinfo->filesystem == FAT32) {
			dirinfo->currentcluster = volinfo->rootdir;
			dirinfo->currentsector = 0;
			dirinfo->currententry = 0;

			/* read first sector of directory */
			if (fat_read_sector(fd, dirinfo->p_scratch, volinfo->dataarea +
					((volinfo->rootdir - 2) * volinfo->secperclus), 1)) {
				return DFS_ERRMISC;
			}
		}
		else {
			dirinfo->currentcluster = 0;
			dirinfo->currentsector = 0;
			dirinfo->currententry = 0;

			/* read first sector of directory */
			if (fat_read_sector(fd,	dirinfo->p_scratch, volinfo->rootdir, 1)) {
				return DFS_ERRMISC;
			}
		}

		/* skip leading path separators */
		while (*ptr == DIR_SEPARATOR && *ptr) {
			ptr++;
		}

		/*
		 *  Scan the path from left to right, finding the start cluster
		 *  of each entry.  Observe that this code is inelegant, but obviates
		 *  the need for recursion.
		 */
		while (*ptr) {
			path_canonical_to_dir((char *) tmpfn, (char *) ptr);

			de.name[0] = 0;

			do {
				result = fat_get_next(fd, dirinfo, &de);
			} while (!result && memcmp(de.name, tmpfn, MSDOS_NAME));

			if (!memcmp(de.name, tmpfn, MSDOS_NAME) &&
					((de.attr & ATTR_DIRECTORY) == ATTR_DIRECTORY)) {
				if (volinfo->filesystem == FAT32) {
					dirinfo->currentcluster = (uint32_t) de.startclus_l_l |
					  ((uint32_t) de.startclus_l_h) << 8 |
					  ((uint32_t) de.startclus_h_l) << 16 |
					  ((uint32_t) de.startclus_h_h) << 24;
				}
				else {
					dirinfo->currentcluster = (uint32_t) de.startclus_l_l |
					  ((uint32_t) de.startclus_l_h) << 8;
				}
				dirinfo->currentsector = 0;
				dirinfo->currententry = 0;

				if (fat_read_sector(fd,	dirinfo->p_scratch, volinfo->dataarea +
						((dirinfo->currentcluster - 2) *
								volinfo->secperclus), 1)) {
					return DFS_ERRMISC;
				}
			}
			else if (!memcmp(de.name, tmpfn, MSDOS_NAME) &&
					!(de.attr & ATTR_DIRECTORY)) {
				return DFS_NOTFOUND;
			}

			/* seek to next item in list */
			while (*ptr != DIR_SEPARATOR && *ptr) {
				ptr++;
			}
			if (*ptr == DIR_SEPARATOR) {
				ptr++;
			}
		}

		if (!dirinfo->currentcluster) {
			return DFS_NOTFOUND;
		}
	}
	return DFS_OK;
}

/*
 * Get next entry in opened directory structure.
 * Copies fields into the dirent structure, updates dirinfo. Note that it is
 * the _caller's_ responsibility to	handle the '.' and '..' entries.
 * A deleted file will be returned as a NULL entry (first char of filename=0)
 * by this code. Filenames beginning with 0x05 will be translated to 0xE5
 * automatically. Long file name entries will be returned as NULL.
 * returns DFS_EOF if there are no more entries, DFS_OK if this entry is valid,
 * or DFS_ERRMISC for a media error
 */
static uint32_t fat_get_next(void *fd,
		p_dir_info_t dirinfo, p_dir_ent_t dirent) {
	uint32_t tempint;	/* required by fat_get_fat_ */
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;

	/* Do we need to read the next sector of the directory? */
	if (dirinfo->currententry >= SECTOR_SIZE / sizeof(dir_ent_t)) {
		dirinfo->currententry = 0;
		dirinfo->currentsector++;

		/* Root directory; special case handling
		 * Note that currentcluster will only ever be zero if both:
		 * (a) this is the root directory, and
		 * (b) we are on a FAT12/16 volume, where the root dir can't be
		 * expanded
		 */
		if (dirinfo->currentcluster == 0) {
			/* Trying to read past end of root directory? */
			if (dirinfo->currentsector * (SECTOR_SIZE / sizeof(dir_ent_t)) >=
					volinfo->rootentries) {
				return DFS_EOF;
			}

			/* Otherwise try to read the next sector */
			if (fat_read_sector(fd, dirinfo->p_scratch,
					volinfo->rootdir + dirinfo->currentsector, 1)) {
				return DFS_ERRMISC;
			}
		}

		/* Normal handling */
		else {
			if (dirinfo->currentsector >= volinfo->secperclus) {
				dirinfo->currentsector = 0;
				if ((dirinfo->currentcluster >= 0xff7 &&
						volinfo->filesystem == FAT12) ||
						(dirinfo->currentcluster >= 0xfff7 &&
						volinfo->filesystem == FAT16) ||
						(dirinfo->currentcluster >= 0x0ffffff7 &&
						volinfo->filesystem == FAT32)) {

				  	/* We are at the end of the directory chain.
				  	 * If this is a normal find operation, we should indicate
				  	 * that there is nothing more to see.
				  	 */
				  	if (!(dirinfo->flags & DFS_DI_BLANKENT)) {
				  		return DFS_EOF;
				  	}

					/*
					 * On the other hand, if this is a "find free entry"
					 * search, we need to tell the caller to allocate a
					 * new cluster
					 */
					else {
						return DFS_ALLOCNEW;
					}
				}
				dirinfo->currentcluster = fat_get_fat_(fd,
						dirinfo->p_scratch, &tempint, dirinfo->currentcluster);
			}
			if (fat_read_sector(fd,	dirinfo->p_scratch, volinfo->dataarea +
					((dirinfo->currentcluster - 2) * volinfo->secperclus) +
					dirinfo->currentsector, 1)) {
				return DFS_ERRMISC;
			}
		}
	}

	memcpy(dirent, &(((p_dir_ent_t) dirinfo->p_scratch)[dirinfo->currententry]),
			sizeof(dir_ent_t));

	if (dirent->name[0] == 0) {		/* no more files in this directory */
		/* If this is a "find blank" then we can reuse this name. */
		if (dirinfo->flags & DFS_DI_BLANKENT) {
			dirinfo->currententry++; // DOSFS 1.03 BUG, currententry was not incremented in this case
			return DFS_OK;
		}
		else {
			return DFS_EOF;
		}
	}

	if (dirent->name[0] == 0xe5) {	/* handle deleted file entries */
		dirent->name[0] = 0;
	}
	else if ((dirent->attr & ATTR_LONG_NAME) == ATTR_LONG_NAME) {
		dirent->name[0] = 0;
	}
	/* handle kanji filenames beginning with 0xE5*/
	else if (dirent->name[0] == 0x05) {
		dirent->name[0] = 0xe5;
	}

	dirinfo->currententry++;

	return DFS_OK;
}

/*
 * INTERNAL
 * Find a free directory entry in the directory specified by path
 * This function MAY cause a disk write if it is necessary to extend the
 * directory size.
 * Note - di.p_scratch must be preinitialized to point to a sector scratch buffer
 * de is a scratch structure
 * Returns DFS_ERRMISC if a new entry could not be located or created
 * de is updated with the same return information you would expect
 * from fat_get_next
 */
static uint32_t fat_get_free_dir_ent(void *fd, uint8_t *path,
		p_dir_info_t di, p_dir_ent_t de) {
	uint32_t tempclus,i;
	p_vol_info_t volinfo;
	fat_file_description_t *fdsc;

	fdsc = (fat_file_description_t *) fd;

	volinfo = &fdsc->fs->vi;

	if (fat_open_dir(fd, path, di)) {
		return DFS_NOTFOUND;
	}

	/* Set "search for empty" flag so fat_get_next knows what we're doing */
	di->flags |= DFS_DI_BLANKENT;

	/*
	 * We seek through the directory looking for an empty entry
	 * Note we are reusing tempclus as a temporary result holder.
	 */
	tempclus = 0;
	do {
		tempclus = fat_get_next(fd, di, de);

		/* Empty entry found */
		if (tempclus == DFS_OK && (!de->name[0])) {
			return DFS_OK;
		}
		/* End of root directory reached */
		else if (tempclus == DFS_EOF) {
			return DFS_ERRMISC;
		}

		else if (tempclus == DFS_ALLOCNEW) {
			tempclus = fat_get_free_fat_(fd, di->p_scratch);
			if (tempclus == 0x0ffffff7) {
				return DFS_ERRMISC;
			}

			/* write out zeroed sectors to the new cluster */
			memset(di->p_scratch, 0, SECTOR_SIZE);
			for (i=0;i<volinfo->secperclus;i++) {
				if (fat_write_sector(fd, di->p_scratch,
						volinfo->dataarea + ((tempclus - 2) *
								volinfo->secperclus) + i, 1)) {
					return DFS_ERRMISC;
				}
			}
			/* Point old end cluster to newly allocated cluster */
			i = 0;
			fat_set_fat_(fd, di->p_scratch, &i,	di->currentcluster, tempclus);

			/* Update dir_info_t so caller knows where to place the new file */
			di->currentcluster = tempclus;
			di->currentsector = 0;
			/* since the code coming after this expects to subtract 1 */
			/*di->currententry = 1; *//* DOSFS 1.03 BUG */
			di->currententry = 0; /* tempclus is not zero but contains fat entry, so next loop will call */


			/* Mark newly allocated cluster as end of chain */
			switch(volinfo->filesystem) {
				case FAT12:		tempclus = 0xfff;	break;
				case FAT16:		tempclus = 0xffff;	break;
				case FAT32:		tempclus = 0x0fffffff;	break;
				default:		return DFS_ERRMISC;
			}
			fat_set_fat_(fd, di->p_scratch,	&i, di->currentcluster, tempclus);
		}
	} while (!tempclus);

	/* We shouldn't get here */
	return DFS_ERRMISC;
}



#define MSDOS_DOT     ".          "
#define MSDOS_DOTDOT  "..         "
static void fatfs_set_direntry (uint32_t dir_cluster, uint32_t cluster) {
	p_dir_ent_t de;

	de = (dir_ent_t *) sector_buff;

	memset(sector_buff, 0, SECTOR_SIZE);
	memcpy(de[0].name, MSDOS_DOT, MSDOS_NAME);
	memcpy(de[1].name, MSDOS_DOTDOT, MSDOS_NAME);
	de[0].attr = de[1].attr = ATTR_DIRECTORY;
	fat_set_filetime(&de[0]);
	fat_set_filetime(&de[1]);

	/*point to the directory containing cluster */
	de[0].startclus_l_l = cluster & 0xff;
	de[0].startclus_l_h = (cluster & 0xff00) >> 8;
	de[0].startclus_h_l = (cluster & 0xff0000) >> 16;
	de[0].startclus_h_h = (cluster & 0xff000000) >> 24;
	/*point to the directory parents cluster */
	de[1].startclus_l_l = dir_cluster & 0xff;
	de[1].startclus_l_h = (dir_cluster & 0xff00) >> 8;
	de[1].startclus_h_l = (dir_cluster & 0xff0000) >> 16;
	de[1].startclus_h_h = (dir_cluster & 0xff000000) >> 24;
}

/*
 * Create a file or directory. You supply a file_create_param_t
 * structure.
 * Returns various DFS_* error states. If the result is DFS_OK, file
 * was created and can be used.
 */
static int fatfs_create_file(void *par) {
	char tmppath[MAX_LENGTH_PATH_NAME];
	uint8_t filename[12];
	dir_info_t di;
	dir_ent_t de;

	p_vol_info_t volinfo;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;
	file_create_param_t *param;
	node_t *node;
	uint32_t cluster, temp;

	param = (file_create_param_t *) par;

	node = (node_t *) param->node;
	fd = (fat_file_description_t *) node->fd;

	volinfo = &fd->fs->vi;
	fileinfo = &fd->fi;

	memset(fileinfo, 0, sizeof(file_info_t));
	fileinfo->volinfo = volinfo;

	/* Get a local copy of the path. */
	strncpy((char *) tmppath,
			(char *) param->path, MAX_LENGTH_PATH_NAME);

	/* set relative path in this file system */
	path_cut_mount_dir(tmppath, (char *) fd->fs->root_name);

	fat_get_filename(tmppath, (char *) filename);

	/*
	 *  At this point, if our path was MYDIR/MYDIR2/FILE.EXT,
	 *  filename = "FILE    EXT" and  tmppath = "MYDIR/MYDIR2".
	 */
	di.p_scratch = sector_buff;
	if (fat_open_dir(fd, (uint8_t *) tmppath, &di)) {
		return DFS_NOTFOUND;
	}

	while (!fat_get_next(fd, &di, &de));

	/* Locate or create a directory entry for this file */
	if (DFS_OK != fat_get_free_dir_ent(fd, (uint8_t *) tmppath, &di, &de)) {
		return DFS_ERRMISC;
	}

	/* put sane values in the directory entry */
	memset(&de, 0, sizeof(de));
	memcpy(de.name, filename, MSDOS_NAME);
	de.attr = node->properties;
	fat_set_filetime(&de);

	/* allocate a starting cluster for the directory entry */
	cluster = fat_get_free_fat_(fd, sector_buff);

	de.startclus_l_l = cluster & 0xff;
	de.startclus_l_h = (cluster & 0xff00) >> 8;
	de.startclus_h_l = (cluster & 0xff0000) >> 16;
	de.startclus_h_h = (cluster & 0xff000000) >> 24;

	/* update file_info_t for our caller's sake */
	fileinfo->volinfo = volinfo;
	fileinfo->pointer = 0;
	/*
	 * The reason we store this extra info about the file is so that we can
	 * speedily update the file size, modification date, etc. on a file
	 * that is opened for writing.
	 */
	if (di.currentcluster == 0) {
		fileinfo->dirsector = volinfo->rootdir + di.currentsector;
	}
	else {
		fileinfo->dirsector = volinfo->dataarea +
				((di.currentcluster - 2) * volinfo->secperclus) +
				di.currentsector;
	}
	fileinfo->diroffset = di.currententry - 1;
	fileinfo->cluster = cluster;
	fileinfo->firstcluster = cluster;
	fileinfo->filelen = 0;

	/*
	 * write the directory entry
	 * note that we no longer have the sector containing the directory
	 * entry, tragically, so we have to re-read it
	 */

	if (fat_read_sector(fd, sector_buff, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	memcpy(&(((p_dir_ent_t) sector_buff)[di.currententry - 1]),
			&de, sizeof(dir_ent_t));
	if (fat_write_sector(fd, sector_buff, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	/* Mark newly allocated cluster as end of chain */
	switch(volinfo->filesystem) {
		case FAT12:		cluster = 0xfff;	break;
		case FAT16:		cluster = 0xffff;	break;
		case FAT32:		cluster = 0x0fffffff;	break;
		default:		return DFS_ERRMISC;
	}

	temp = 0;
	fat_set_fat_(fd, sector_buff, &temp, fileinfo->cluster, cluster);

	if (ATTR_DIRECTORY == (node->properties & DIRECTORY_NODE_TYPE)) {
		/* create . and ..  files of this catalog */
		fatfs_set_direntry(di.currentcluster, fileinfo->cluster);
		cluster = fileinfo->volinfo->dataarea +
				  ((fileinfo->cluster - 2) * fileinfo->volinfo->secperclus);
		if (fat_write_sector(fd, sector_buff, cluster, 1)) {
			return DFS_ERRMISC;
		}
	}

	return DFS_OK;
}

/*
 * Open a file for reading or writing. You supply populated vol_info_t,
 * a path to the file, mode (DFS_READ or DFS_WRITE) and an empty fileinfo
 * structure. You also need to provide a pointer to a sector-sized scratch
 * buffer.
 * Returns various DFS_* error states. If the result is DFS_OK, fileinfo
 * can be used to access the file from this point on.
 */
static uint32_t fat_open_file(void *fdsc, uint8_t *path, uint8_t mode,
		uint8_t *p_scratch) {
	char tmppath[MAX_LENGTH_PATH_NAME];
	uint8_t filename[12];
	dir_info_t di;
	dir_ent_t de;

	p_vol_info_t volinfo;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;

	volinfo = &fd->fs->vi;
	fileinfo = &fd->fi;

	memset(fileinfo, 0, sizeof(file_info_t));

	/* save access mode */
	fileinfo->mode = mode;

	/* Get a local copy of the path. If it's longer than MAX_PATH, abort.*/
	strncpy((char *) tmppath, (char *) path, MAX_LENGTH_PATH_NAME);
	tmppath[MAX_LENGTH_PATH_NAME - 1] = 0;
	if (strcmp((char *) path,(char *) tmppath)) {
		return DFS_PATHLEN;
	}

	fat_get_filename(tmppath, (char *) filename);

	/*
	 *  At this point, if our path was MYDIR/MYDIR2/FILE.EXT,
	 *  filename = "FILE    EXT" and  tmppath = "MYDIR/MYDIR2".
	 */

	di.p_scratch = p_scratch;
	if (fat_open_dir(fd, (uint8_t *) tmppath, &di)) {
		return DFS_NOTFOUND;
	}

	while (!fat_get_next(fd, &di, &de)) {
		path_canonical_to_dir(tmppath, (char *) de.name);
		if (!memcmp(tmppath, filename, MSDOS_NAME)) {
			/* You can't use this function call to open a directory. */
			if (de.attr & ATTR_DIRECTORY){
				//return DFS_NOTFOUND;
			}

			fileinfo->volinfo = volinfo;
			fileinfo->pointer = 0;
			/*
			 * The reason we store this extra info about the file is so that we
			 * can speedily update the file size, modification date, etc. on a
			 * file that is opened for writing.
			 */
			if (di.currentcluster == 0) {
				fileinfo->dirsector = volinfo->rootdir + di.currentsector;
			}
			else {
				fileinfo->dirsector = volinfo->dataarea +
						((di.currentcluster - 2) *
						volinfo->secperclus) + di.currentsector;
			}
			fileinfo->diroffset = di.currententry - 1;
			if (volinfo->filesystem == FAT32) {
				fileinfo->cluster = (uint32_t) de.startclus_l_l |
				  ((uint32_t) de.startclus_l_h) << 8 |
				  ((uint32_t) de.startclus_h_l) << 16 |
				  ((uint32_t) de.startclus_h_h) << 24;
			}
			else {
				fileinfo->cluster = (uint32_t) de.startclus_l_l |
				  ((uint32_t) de.startclus_l_h) << 8;
			}
			fileinfo->firstcluster = fileinfo->cluster;
			fileinfo->filelen = (uint32_t) de.filesize_0 |
			  ((uint32_t) de.filesize_1) << 8 |
			  ((uint32_t) de.filesize_2) << 16 |
			  ((uint32_t) de.filesize_3) << 24;

			return DFS_OK;
		}
	}
	return DFS_NOTFOUND;
}

/*
 * Read an open file
 * You must supply a prepopulated file_info_t as provided by fat_open_file,
 * and a pointer to a SECTOR_SIZE scratch buffer.
 * 	Note that returning DFS_EOF is not an error condition. This function
 * 	updates the	successcount field with the number of bytes actually read.
 */
static uint32_t fat_read_file(void *fdsc, uint8_t *p_scratch,
		uint8_t *buffer, uint32_t *successcount, uint32_t len) {
	uint32_t remain;
	uint32_t result;
	uint32_t sector;
	uint32_t bytesread;
	uint32_t clastersize;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;

	fileinfo = &fd->fi;

	/* Don't try to read past EOF */
	if (len > fileinfo->filelen - fileinfo->pointer) {
		len = fileinfo->filelen - fileinfo->pointer;
	}

	result = DFS_OK;
	remain = len;
	*successcount = 0;
	clastersize = fileinfo->volinfo->secperclus * SECTOR_SIZE;

	while (remain && result == DFS_OK) {
		/* This is a bit complicated. The sector we want to read is addressed
		 * at a cluster granularity by the fileinfo->cluster member. The file
		 * pointer tells us how many extra sectors to add to that number.
		 */
		sector = fileinfo->volinfo->dataarea +
		  ((fileinfo->cluster - 2) * fileinfo->volinfo->secperclus) +
		  div(div(fileinfo->pointer,clastersize).rem, SECTOR_SIZE).quot;

		/* Case 1 - File pointer is not on a sector boundary */
		if (div(fileinfo->pointer, SECTOR_SIZE).rem) {
			uint16_t tempreadsize;

			/* We always have to go through scratch in this case */
			result = fat_read_sector(fd, p_scratch, sector, 1);

			/*
			 * This is the number of bytes that we actually care about in the
			 * sector just read.
			 */
			tempreadsize = SECTOR_SIZE -
					(div(fileinfo->pointer, SECTOR_SIZE).rem);

			/* Case 1A - We want the entire remainder of the sector. After this
			 * point, all passes through the read loop will be aligned on a
			 * sector boundary, which allows us to go through the optimal path
			 *  2A below.
			 */
		   	if (remain >= tempreadsize) {
				memcpy(buffer, p_scratch + (SECTOR_SIZE - tempreadsize),
						tempreadsize);
				bytesread = tempreadsize;
				buffer += tempreadsize;
				fileinfo->pointer += tempreadsize;
				remain -= tempreadsize;
			}
			/* Case 1B - This read concludes the file read operation */
			else {
				memcpy(buffer, p_scratch +
						(SECTOR_SIZE - tempreadsize), remain);

				buffer += remain;
				fileinfo->pointer += remain;
				bytesread = remain;
				remain = 0;
			}
		}
		/* Case 2 - File pointer is on sector boundary */
		else {
			/*
			 * Case 2A - We have at least one more full sector to read and
			 * don't have to go through the scratch buffer. You could insert
			 * optimizations here to read multiple sectors at a time, if you
			 * were thus inclined (note that the maximum multi-read you could
			 * perform is a single cluster, so it would be advantageous to have
			 * code similar to case 1A above that would round the pointer to a
			 * cluster boundary the first pass through, so all subsequent
			 * [large] read requests would be able to go a cluster at a time).
			 */
			 if (remain >= SECTOR_SIZE) {
				result = fat_read_sector(fd, buffer, sector, 1);
				remain -= SECTOR_SIZE;
				buffer += SECTOR_SIZE;
				fileinfo->pointer += SECTOR_SIZE;
				bytesread = SECTOR_SIZE;
			}
			/* Case 2B - We are only reading a partial sector */
			else {
				result = fat_read_sector(fd, p_scratch, sector, 1);
				memcpy(buffer, p_scratch, remain);
				buffer += remain;
				fileinfo->pointer += remain;
				bytesread = remain;
				remain = 0;
			}
		}

		*successcount += bytesread;

		/* check to see if we stepped over a cluster boundary */
		if (div(fileinfo->pointer - bytesread, clastersize).quot !=
			div(fileinfo->pointer, clastersize).quot) {
			/*
			 * An act of minor evil - we use bytesread as a scratch integer,
			 * knowing that its value is not used after updating *successcount
			 * above
			 */
			bytesread = 0;
			if (((fileinfo->volinfo->filesystem == FAT12) &&
					(fileinfo->cluster >= 0xff8)) ||
					((fileinfo->volinfo->filesystem == FAT16) &&
							(fileinfo->cluster >= 0xfff8)) ||
							((fileinfo->volinfo->filesystem == FAT32) &&
									(fileinfo->cluster >= 0x0ffffff8))) {
				result = DFS_EOF;
			}
			else {
				fileinfo->cluster = fat_get_fat_(fd,
						p_scratch, &bytesread, fileinfo->cluster);
			}
		}
	}

	return result;
}

/*
 * Seek file pointer to a given position
 * This function does not return status - refer to the fileinfo->pointer value
 * to see where the pointer wound up.
 * Requires a SECTOR_SIZE scratch buffer
 */
static void fat_fseek(void *fdsc, uint32_t offset, uint8_t *p_scratch) {
	uint32_t tempint, clastersize;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;

	fileinfo = &fd->fi;

	/* Case 0a - Return immediately for degenerate case */
	if (offset == fileinfo->pointer) {
		return;
	}

	/* Case 0b - Don't allow the user to seek past the end of the file */
	if (offset > fileinfo->filelen) {
		offset = fileinfo->filelen;
		/* NOTE NO RETURN HERE! */
	}

	/*
	 * Case 1 - Simple rewind to start
	 * Note _intentional_ fallthrough from Case 0b above
	 */
	if (offset == 0) {
		fileinfo->cluster = fileinfo->firstcluster;
		fileinfo->pointer = 0;
		return;
	}
	/* Case 2 - Seeking backwards. Need to reset and seek forwards */
	else if (offset < fileinfo->pointer) {
		fileinfo->cluster = fileinfo->firstcluster;
		fileinfo->pointer = 0;
		/* NOTE NO RETURN HERE! */
	}

	clastersize = fileinfo->volinfo->secperclus * SECTOR_SIZE;
	if (div(fileinfo->pointer, clastersize).quot ==
			div(fileinfo->pointer + offset, fileinfo->volinfo->secperclus *
					SECTOR_SIZE).quot) {
		fileinfo->pointer = offset;
	}
	/*Case 3b - Seeking across cluster boundary(ies) */
	else {
		/* round file pointer down to cluster boundary */
		fileinfo->pointer = div(fileinfo->pointer,
				clastersize).quot * clastersize;

		/* seek by clusters */
		while (div(fileinfo->pointer, clastersize).quot !=
				div(fileinfo->pointer + offset,	clastersize).quot) {
			fileinfo->cluster = fat_get_fat_(fd, p_scratch,
					&tempint, fileinfo->cluster);
			/* Abort if there was an error */
			if (fileinfo->cluster == 0x0ffffff7) {
				fileinfo->pointer = 0;
				fileinfo->cluster = fileinfo->firstcluster;
				return;
			}
			fileinfo->pointer += SECTOR_SIZE * fileinfo->volinfo->secperclus;
			offset -= SECTOR_SIZE * fileinfo->volinfo->secperclus;
		}

		/* since we know the cluster is right, we have no more work to do */
		fileinfo->pointer += offset;
	}
}

/*
 * Delete a file
 * p_scratch must point to a sector-sized buffer
 */
static int fat_unlike_file(void *fdsc, uint8_t *path,
		uint8_t *p_scratch) {
	uint32_t cache;
	uint32_t tempclus;
	p_vol_info_t volinfo;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;
	volinfo = &fd->fs->vi;
	fileinfo = &fd->fi;

	cache = 0;

	/* fat_open_file gives us all the information we need to delete it */
	if (DFS_OK != fat_open_file(fd, path, O_RDONLY, p_scratch)) {
		return DFS_NOTFOUND;
	}

	/* First, read the directory sector and delete that entry */
	if (fat_read_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	((p_dir_ent_t) p_scratch)[fileinfo->diroffset].name[0] = 0xe5;
	if (fat_write_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}

	/* Now follow the cluster chain to free the file space */
	while (!((volinfo->filesystem == FAT12 && fileinfo->firstcluster >= 0x0ff7) ||
			(volinfo->filesystem == FAT16 && fileinfo->firstcluster >= 0xfff7) ||
			(volinfo->filesystem == FAT32 && fileinfo->firstcluster >= 0x0ffffff7))) {
		tempclus = fileinfo->firstcluster;

		fileinfo->firstcluster = fat_get_fat_(fd, p_scratch,
				&cache, fileinfo->firstcluster);

		fat_set_fat_(fd, p_scratch, &cache, tempclus, 0);
	}
	return DFS_OK;
}

/*
 * Delete a file
 * p_scratch must point to a sector-sized buffer
 */
static int fat_unlike_directory(void *fdsc, uint8_t *path,
		uint8_t *p_scratch) {
	uint32_t cache;
	uint32_t tempclus;
	p_vol_info_t volinfo;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;
	volinfo = &fd->fs->vi;
	fileinfo = &fd->fi;

	cache = 0;

	/* fat_open_file gives us all the information we need to delete it */
	if (DFS_OK != fat_open_file(fd, path, O_RDONLY, p_scratch)) {
		return DFS_NOTFOUND;
	}

	/* First, read the directory sector and delete that entry */
	if (fat_read_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	((p_dir_ent_t) p_scratch)[fileinfo->diroffset].name[0] = 0xe5;
	if (fat_write_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}

	/* Now follow the cluster chain to free the file space */
	while (!((volinfo->filesystem == FAT12 && fileinfo->firstcluster >= 0x0ff7) ||
			(volinfo->filesystem == FAT16 && fileinfo->firstcluster >= 0xfff7) ||
			(volinfo->filesystem == FAT32 && fileinfo->firstcluster >= 0x0ffffff7))) {
		tempclus = fileinfo->firstcluster;

		fileinfo->firstcluster = fat_get_fat_(fd, p_scratch,
				&cache, fileinfo->firstcluster);

		fat_set_fat_(fd, p_scratch, &cache, tempclus, 0);
	}
	return DFS_OK;
}

/*
 * Write an open file
 * You must supply a prepopulated file_info_t as provided by
 * fat_open_file, and a pointer to a SECTOR_SIZE scratch buffer.
 * This function updates the successcount field with the number
 * of bytes actually written.
 */
static uint32_t fat_write_file(void *fdsc, uint8_t *p_scratch,
		uint8_t *buffer, uint32_t *successcount, uint32_t len) {
	uint32_t remain;
	uint32_t result = DFS_OK;
	uint32_t sector;
	uint32_t byteswritten;
	uint32_t lastcluster, nextcluster;
	uint32_t clastersize;
	p_file_info_t fileinfo;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;
	fileinfo = &fd->fi;

	/* Don't allow writes to a file that's open as readonly */
	if (!(fileinfo->mode & O_WRONLY)) {
		return DFS_ERRMISC;
	}

	remain = len;
	*successcount = 0;
	clastersize = fileinfo->volinfo->secperclus * SECTOR_SIZE;

	while (remain && result == DFS_OK) {
		/*
		 * This is a bit complicated. The sector we want to read is addressed
		 * at a cluster granularity by  the fileinfo->cluster member.
		 * The file pointer tells us how many extra sectors to add to that
		 * number.
		 */
		sector = fileinfo->volinfo->dataarea +
		  ((fileinfo->cluster - 2) * fileinfo->volinfo->secperclus) +
		  div(div(fileinfo->pointer, clastersize).rem, SECTOR_SIZE).quot;

		/* Case 1 - File pointer is not on a sector boundary */
		if (div(fileinfo->pointer, SECTOR_SIZE).rem) {
			uint16_t tempsize;

			/* We always have to go through scratch in this case */
			result = fat_read_sector(fd, p_scratch, sector, 1);

			/*
			 * This is the number of bytes that we don't want to molest in the
			 * scratch sector just read.
			 */
			tempsize = div(fileinfo->pointer, SECTOR_SIZE).rem;

			/*
			 * Case 1A - We are writing the entire remainder of the sector.
			 * After this point, all passes through the read loop will be
			 * aligned on a sector boundary, which allows us to go through the
			 * optimal path
			 * 2A below.
			 */
		   	if (remain >= SECTOR_SIZE - tempsize) {
				memcpy(p_scratch + tempsize, buffer, SECTOR_SIZE - tempsize);
				if (!result) {
					result = fat_write_sector(fd, p_scratch, sector, 1);
				}

				byteswritten = SECTOR_SIZE - tempsize;
				buffer += SECTOR_SIZE - tempsize;
				fileinfo->pointer += SECTOR_SIZE - tempsize;
				if (fileinfo->filelen < fileinfo->pointer) {
					fileinfo->filelen = fileinfo->pointer;
				}
				remain -= SECTOR_SIZE - tempsize;
			}
			/* Case 1B - This concludes the file write operation */
			else {
				memcpy(p_scratch + tempsize, buffer, remain);
				if (!result) {
					result = fat_write_sector(fd, p_scratch, sector, 1);
				}

				buffer += remain;
				fileinfo->pointer += remain;
				if (fileinfo->filelen < fileinfo->pointer) {
					fileinfo->filelen = fileinfo->pointer;
				}
				byteswritten = remain;
				remain = 0;
			}
		} /* case 1 */
		/* Case 2 - File pointer is on sector boundary */
		else {
			/* Case 2A - We have at least one more full sector to write and
			 * don't have to go through the scratch buffer. You could insert
			 * optimizations here to write multiple sectors at a time, if you
			 * were thus inclined. Refer to similar notes in fat_read_file.
			 */
			if (remain >= SECTOR_SIZE) {
				result = fat_write_sector(fd, buffer, sector, 1);
				remain -= SECTOR_SIZE;
				buffer += SECTOR_SIZE;
				fileinfo->pointer += SECTOR_SIZE;
				if (fileinfo->filelen < fileinfo->pointer) {
					fileinfo->filelen = fileinfo->pointer;
				}
				byteswritten = SECTOR_SIZE;
			}
			/*
			 * Case 2B - We are only writing a partial sector and potentially
			 * need to go through the scratch buffer.
			 */
			else {
				/* If the current file pointer is not yet at or beyond the file
				 * length, we are writing somewhere in the middle of the file
				 * and need to load the original sector to do
				 * a read-modify-write.
				 */
				if (fileinfo->pointer < fileinfo->filelen) {
					result = fat_read_sector(fd, p_scratch, sector, 1);
					if (!result) {
						memcpy(p_scratch, buffer, remain);
						result = fat_write_sector(fd, p_scratch, sector, 1);
					}
				}
				else {
					memset(p_scratch, 0, SECTOR_SIZE);
					memcpy(p_scratch, buffer, remain);
					result = fat_write_sector(fd, p_scratch, sector, 1);
				}

				buffer += remain;
				fileinfo->pointer += remain;
				if (fileinfo->filelen < fileinfo->pointer) {
					fileinfo->filelen = fileinfo->pointer;
				}
				byteswritten = remain;
				remain = 0;
			}
		}

		*successcount += byteswritten;

		/* check to see if we stepped over a cluster boundary */
		if (div(fileinfo->pointer - byteswritten, clastersize).quot !=
				div(fileinfo->pointer, clastersize).quot) {

		  	/* We've transgressed into another cluster. If we were already
		  	 * at EOF, we need to allocate a new cluster.
		  	 * An act of minor evil - we use byteswritten as a scratch integer,
		  	 * knowing that its value is not used after updating *successcount
		  	 * above
		  	 */
		  	byteswritten = 0;

			lastcluster = fileinfo->cluster;
			fileinfo->cluster = fat_get_fat_(fd, p_scratch,
					&byteswritten, fileinfo->cluster);

			/* Allocate a new cluster? */
			if (((fileinfo->volinfo->filesystem == FAT12) &&
					(fileinfo->cluster >= 0xff8)) ||
					((fileinfo->volinfo->filesystem == FAT16) &&
					(fileinfo->cluster >= 0xfff8)) ||
					((fileinfo->volinfo->filesystem == FAT32) &&
					(fileinfo->cluster >= 0x0ffffff8))) {
			  	uint32_t tempclus;

				tempclus = fat_get_free_fat_(fd, p_scratch);
				byteswritten = 0; /* invalidate cache */
				if (tempclus == 0x0ffffff7) {
					return DFS_ERRMISC;
				}
				/* Link new cluster onto file */
				fat_set_fat_(fd, p_scratch, &byteswritten,
						lastcluster, tempclus);
				fileinfo->cluster = tempclus;

				/* Mark newly allocated cluster as end of chain */
				switch(fileinfo->volinfo->filesystem) {
					case FAT12:		tempclus = 0xfff;	break;
					case FAT16:		tempclus = 0xffff;	break;
					case FAT32:		tempclus = 0x0fffffff;	break;
					default:		return DFS_ERRMISC;
				}
				fat_set_fat_(fd, p_scratch, &byteswritten,
						fileinfo->cluster, tempclus);

				result = DFS_OK;
			}
		}
	}
	    /* If cleared, then mark free clusters*/
		if(fileinfo->filelen > fileinfo->pointer) {
			if (div(fileinfo->filelen, clastersize).quot !=
				div(fileinfo->pointer, clastersize).quot) {

				byteswritten = 0;/* invalidate cache */
				nextcluster = fat_get_fat_(fd, p_scratch,
						&byteswritten, fileinfo->cluster);

				/* Mark last cluster as end of chain */
				switch(fileinfo->volinfo->filesystem) {
					case FAT12:		lastcluster = 0xfff;	break;
					case FAT16:		lastcluster = 0xfff;	break;
					case FAT32:		lastcluster = 0x0fffffff;	break;
					default:		return DFS_ERRMISC;
				}
				fat_set_fat_(fd, p_scratch, &byteswritten,
						fileinfo->cluster, lastcluster);

				/* Now follow the cluster chain to free the file space */
				while (!((fileinfo->volinfo->filesystem == FAT12 &&
						nextcluster >= 0x0ff7) ||
						(fileinfo->volinfo->filesystem == FAT16 &&
						nextcluster >= 0xfff7) ||
						(fileinfo->volinfo->filesystem == FAT32 &&
						nextcluster >= 0x0ffffff7))) {
					lastcluster = nextcluster;

					nextcluster = fat_get_fat_(fd, p_scratch,
							&byteswritten, nextcluster);

					fat_set_fat_(fd, p_scratch, &byteswritten, lastcluster, 0);
				}

			}
		}

		fileinfo->filelen = fileinfo->pointer;

		/* Update directory entry */
		if (fat_read_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
			return DFS_ERRMISC;
		}

		((p_dir_ent_t) p_scratch)[fileinfo->diroffset].filesize_0 =
				fileinfo->filelen & 0xff;

		((p_dir_ent_t) p_scratch)[fileinfo->diroffset].filesize_1 =
				(fileinfo->filelen & 0xff00) >> 8;

		((p_dir_ent_t) p_scratch)[fileinfo->diroffset].filesize_2 =
				(fileinfo->filelen & 0xff0000) >> 16;

		((p_dir_ent_t) p_scratch)[fileinfo->diroffset].filesize_3 =
				(fileinfo->filelen & 0xff000000) >> 24;

		if (fat_write_sector(fd, p_scratch, fileinfo->dirsector, 1)) {
			return DFS_ERRMISC;
		}

	return result;
}

static int fat_read_sector(void *fdsc, uint8_t *buffer,
		uint32_t sector, uint32_t count) {
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;

	if(0 > block_dev_read(fd->fs->dev_id, (char *) buffer, count * SECTOR_SIZE, sector)) {
		return DFS_ERRMISC;
	}
	else {
		return DFS_OK;
	}
}

static int fat_write_sector(void *fdsc, uint8_t *buffer,
		uint32_t sector, uint32_t count) {
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdsc;

	if(0 > block_dev_write(fd->fs->dev_id, (char *) buffer, count * SECTOR_SIZE, sector)) {
		return DFS_ERRMISC;
	}
	else {
		return DFS_OK;
	}
}

static int fatfs_root_create(void *fdes) {
	uint32_t cluster;
	p_vol_info_t volinfo;
	p_file_info_t fileinfo;
	uint32_t pstart, psize;
	uint8_t pactive, ptype;
	dir_info_t di;
	dir_ent_t de;
	fat_file_description_t *fd;

	fd = (fat_file_description_t *) fdes;

	fileinfo = &fd->fi;
	volinfo = (p_vol_info_t) &fd->fs->vi;

	/* Obtain pointer to first partition on first (only) unit */
	pstart = fat_get_ptn_start(fd, sector_buff, 0, &pactive, &ptype, &psize);
	if (pstart == 0xffffffff) {
		/*printf("Cannot find first partition\n"); */
		return -1;
	}

	if (fat_get_vol_info(fd, sector_buff, pstart)) {
		/* printf("Error getting volume information\n"); */
		return -1;
	}
	di.p_scratch = sector_buff;

	/* Locate or create a directory entry for this file */
	if (DFS_OK != fat_get_free_dir_ent(fd, (uint8_t *)ROOT_DIR, &di, &de)) {
		return DFS_ERRMISC;
	}

	/* put sane values in the directory entry */
	memset(&de, 0, sizeof(de));
	memcpy(de.name, "/ROOT       ", MSDOS_NAME);
	de.attr = ATTR_DIRECTORY;
	fat_set_filetime(&de);

	/* allocate a starting cluster for the directory entry */
	cluster = fat_get_free_fat_(fd, sector_buff);

	de.startclus_l_l = cluster & 0xff;
	de.startclus_l_h = (cluster & 0xff00) >> 8;
	de.startclus_h_l = (cluster & 0xff0000) >> 16;
	de.startclus_h_h = (cluster & 0xff000000) >> 24;

	/* update file_info_t for our caller's sake */
	fileinfo->volinfo = volinfo;
	fileinfo->pointer = 0;
	fileinfo->dirsector = volinfo->rootdir;

	fileinfo->diroffset = 0;
	fileinfo->cluster = cluster;
	fileinfo->firstcluster = cluster;
	fileinfo->filelen = 0;
	fileinfo->mode = O_WRONLY;

	/*
	 * write the directory entry
	 * note that we no longer have the sector containing the directory
	 * entry, tragically, so we have to re-read it
	 */

	if (fat_read_sector(fd, sector_buff, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	memcpy(&(((p_dir_ent_t) sector_buff)[0]), &de, sizeof(dir_ent_t));

	if (fat_write_sector(fd, sector_buff, fileinfo->dirsector, 1)) {
		return DFS_ERRMISC;
	}
	/* Mark newly allocated cluster as end of chain */
	switch(volinfo->filesystem) {
		case FAT12:		cluster = 0xfff;	break;
		case FAT16:		cluster = 0xffff;	break;
		case FAT32:		cluster = 0x0fffffff;	break;
		default:		return DFS_ERRMISC;
	}
	psize = 0;
	fat_set_fat_(fd, sector_buff, &psize, fileinfo->cluster, cluster);

	return DFS_OK;
}

static int fat_mount_files (void *dir_node) {
	uint32_t cluster;
	node_t *node, *root_node;
	uint32_t pstart, psize;
	uint8_t pactive, ptype;
	dir_info_t di;
	dir_ent_t de;
	fat_file_description_t *fd, *root_fd;
	char full_path[MAX_LENGTH_PATH_NAME];
	uint8_t name[MSDOS_NAME + 2];

	root_node = (node_t *)dir_node;
	root_fd = (fat_file_description_t *) root_node->fd;

	/* Obtain pointer to first partition */
	pstart = fat_get_ptn_start(root_fd, sector_buff, 0, &pactive, &ptype, &psize);
	if (pstart == 0xffffffff) {
		return -1;
	}
	if (fat_get_vol_info(root_fd, sector_buff, pstart)) {
		return -1;
	}
	di.p_scratch = sector_buff;
	if (fat_open_dir(root_fd, (uint8_t *) ROOT_DIR, &di)) {
		return -EBUSY;
	}
	/* move out from first root directory entry table*/
	cluster = fat_get_next(root_fd, &di, &de);

	while(DFS_EOF != (cluster = fat_get_next(root_fd, &di, &de))) {
		/* after fat_get_next de.name[0]=0, if it is not a valid name */
		if(0 != de.name[0]) {
			path_dir_to_canonical((char *) name, (char *) de.name,
								  de.attr & ATTR_DIRECTORY);
			/* Create node and file descriptor*/
			memset(full_path, 0, sizeof(full_path));
			strcpy(full_path, (const char *) root_fd->fs->root_name);
			strcat(full_path, "/");
			strcat (full_path, (const char *) name);

			if(NULL == (node = vfs_add_path (full_path, NULL))) {
				return -ENOMEM;
			}
			if(NULL == (fd = pool_alloc(&fat_file_pool))) {
				vfs_del_leaf(node);
				return -ENOMEM;
			}
			fd->fs = root_fd->fs;
			node->fs_type = &fatfs_drv;
			node->dev_id = root_node->dev_id;
			node->fd = (void *)fd;

			if ((ATTR_DIRECTORY & de.attr) == ATTR_DIRECTORY) {
				node->properties = DIRECTORY_NODE_TYPE;
				if ((0 != strncmp((char *) de.name, ".  ", 3)) &&
					(0 != strncmp((char *) de.name, ".. ", 3))) {
					fat_create_dir_entry(full_path);
				}
			}
			else {
				node->properties = FILE_NODE_TYPE;
			}
		}
	}
	return DFS_OK;
}

static int fat_create_dir_entry(char *dir_name) {
	uint32_t cluster;
	node_t *parent_node, *node;
	fat_file_description_t *parent_fd, *fd;
	dir_info_t di;
	dir_ent_t de;

	char full_path[MAX_LENGTH_PATH_NAME];
	uint8_t *rcv_buf;
	uint8_t name[MSDOS_NAME];

	if (NULL == (parent_node = vfs_find_node(dir_name, NULL))) {
		return -ENODEV;/*device not found*/
	}

	parent_fd = (fat_file_description_t *) parent_node->fd;

	if(NULL == (rcv_buf = page_alloc(__phymem_allocator, 1))) {
		return -ENOMEM;
	}
	memset(rcv_buf, 0, sizeof(rcv_buf));
	di.p_scratch = rcv_buf;

	/* set relative path in this file system */
	path_cut_mount_dir(dir_name, (char *)parent_fd->fs->root_name);
	if (fat_open_dir(parent_fd, (uint8_t *) dir_name, &di)) {
		page_free(__phymem_allocator, rcv_buf, 1);
		return -ENODEV;
	}

	while(DFS_EOF != (cluster = fat_get_next(parent_fd, &di, &de))) {
		if(0 != de.name[0]) {
			path_dir_to_canonical((char *) name, (char *) de.name,
								  de.attr & ATTR_DIRECTORY);
			/* Create node and file descriptor*/
			memset(full_path, 0, sizeof(full_path));
			strcpy(full_path, (const char *) parent_fd->fs->root_name);
			strcat(full_path, dir_name);
			strcat(full_path, "/");
			strncat (full_path, (const char *) name, MSDOS_NAME);

			if(NULL == (node = vfs_add_path (full_path, NULL))) {
				return -ENOMEM;
			}
			if(NULL == (fd = pool_alloc(&fat_file_pool))) {
				vfs_del_leaf(node);
				return -ENOMEM;
			}
			fd->fs = parent_fd->fs;
			node->fs_type = &fatfs_drv;
			node->dev_id = parent_node->dev_id;
			node->fd = (void *)fd;

			if ((ATTR_DIRECTORY & de.attr) == ATTR_DIRECTORY) {
				node->properties = DIRECTORY_NODE_TYPE;
				if ((0 != strncmp((char *) de.name, ".  ", 3)) &&
					(0 != strncmp((char *) de.name, ".. ", 3))) {
					fat_create_dir_entry(full_path);
				}
			}
			else {
				node->properties = FILE_NODE_TYPE;
			}
		}
	}
	page_free(__phymem_allocator, rcv_buf, 1);
	return 0;
}

/* File operations */

static void *fatfs_fopen(struct file_desc *desc,  const char *mode);
static int fatfs_fclose(struct file_desc *desc);
static size_t fatfs_fread(void *buf, size_t size, size_t count, void *file);
static size_t fatfs_fwrite(const void *buf, size_t size, size_t count,
		void *file);
static int fatfs_fseek(void *file, long offset, int whence);
static int fatfs_ioctl(void *file, int request, va_list args);

static file_operations_t fatfs_fop = { fatfs_fopen, fatfs_fclose, fatfs_fread,
		fatfs_fwrite, fatfs_fseek, fatfs_ioctl, NULL };
/*
 * file_operation
 */
static void *fatfs_fopen(struct file_desc *desc, const char *mode) {
	node_t *nod;
	uint8_t _mode;
	uint8_t path [MAX_LENGTH_PATH_NAME];
	fat_file_description_t *fd;

	nod = desc->node;
	fd = (fat_file_description_t *)nod->fd;

	if ('r' == *mode) {
		_mode = O_RDONLY;
	}
	else if ('w' == *mode) {
		_mode = O_WRONLY;
	}
	else {
		_mode = O_RDONLY;
	}

	vfs_get_path_by_node (nod, (char *) path);
	/* set relative path in this file system */
	path_cut_mount_dir((char *) path, (char *) fd->fs->root_name);

	if(DFS_OK == fat_open_file(fd, (uint8_t *)path, _mode, sector_buff)) {
		return desc;
	}
	return NULL;
}

static int fatfs_fseek(void *file, long offset, int whence) {
	struct file_desc *desc;
	fat_file_description_t *fd;
	uint32_t curr_offset;

	curr_offset = offset;

	desc = (struct file_desc *) file;
	fd = (fat_file_description_t *)desc->node->fd;

	switch (whence) {
	case SEEK_SET:
		break;
	case SEEK_CUR:
		curr_offset += fd->fi.pointer;
		break;
	case SEEK_END:
		curr_offset = fd->fi.filelen + offset;
		break;
	default:
		return -1;
	}

	fat_fseek(fd, curr_offset, sector_buff);
	return 0;
}

static int fatfs_fclose(struct file_desc *desc) {
	return 0;
}

static size_t fatfs_fread(void *buf, size_t size, size_t count, void *file) {
	size_t size_to_read;
	struct file_desc *desc;
	size_t rezult;
	fat_file_description_t *fd;

	size_to_read = size * count;
	desc = (struct file_desc *) file;
	fd = (fat_file_description_t *)desc->node->fd;

	rezult = fat_read_file(fd, sector_buff, buf, &bytecount, size_to_read);
	if (DFS_OK == rezult) {
		return bytecount;
	}
	return rezult;
}

static size_t fatfs_fwrite(const void *buf, size_t size,
	size_t count, void *file) {
	size_t size_to_write;
	struct file_desc *desc;
	size_t rezult;
	fat_file_description_t *fd;

	size_to_write = size * count;
	desc = (struct file_desc *) file;

	fd = (fat_file_description_t *)desc->node->fd;

	rezult = fat_write_file(fd, sector_buff, (uint8_t *)buf,
			&bytecount, size_to_write);
	if (DFS_OK == rezult) {
		return bytecount;
	}
	return rezult;
}

static int fatfs_ioctl(void *file, int request, va_list args) {
	return 0;
}


static int fat_mount_files (void *dir_node);
static int fatfs_create_file(void *par);
static int fat_create_dir_entry (char *dir_name);
static int fatfs_partition (void *fdes);
static int fatfs_root_create(void *fdesc);
static int fat_unlike_file(void *fd, uint8_t *path, uint8_t *scratch);
static int fat_unlike_directory(void *fd, uint8_t *path, uint8_t *scratch);

/* File system operations */

static int fatfs_init(void * par);
static int fatfs_format(void * dev);
static int fatfs_mount(void * par);
static int fatfs_create(void *par);
static int fatfs_delete(const char *fname);

static fsop_desc_t fatfs_fsop = { fatfs_init, fatfs_format, fatfs_mount,
		fatfs_create, fatfs_delete };

static fs_drv_t fatfs_drv = { "vfat", &fatfs_fop, &fatfs_fsop };

static int fatfs_init(void * par) {
	return 0;
}

static int fatfs_format(void *path) {
	node_t *nod;
	fat_fs_description_t *fs_des;
	fat_file_description_t *fd;

	if (NULL == (nod = vfs_find_node((char *) path, NULL))) {
		return -ENODEV;/*device not found*/
	}

	if((NULL == (fs_des = pool_alloc(&fat_fs_pool))) ||
			(NULL == (fd = pool_alloc(&fat_file_pool)))) {
		if(NULL != fs_des) {
			pool_free(&fat_fs_pool, fs_des);
		}
		return -ENOMEM;
	}
	fs_des->dev_id = nod->dev_id;
	strcpy((char *) fs_des->root_name, "\0");

	fd->fs = fs_des;
	nod->fs_type = &fatfs_drv;
	nod->file_info = (void *) &fatfs_fop;
	nod->fd = (void *)fd;

	fatfs_partition(fd);
	fatfs_root_create(fd);

	return 0;
}

static int fatfs_mount(void *par) {
	mount_params_t *params;
	node_t *dir_node, *dev_node;
	fat_file_description_t *fd, *dev_fd;

	params = (mount_params_t *) par;
	dev_node = params->dev_node;
	if (NULL == (dir_node = vfs_find_node(params->dir, NULL))) {
		/*FIXME: usually mount doesn't create a directory*/
		if (NULL == (dir_node = vfs_add_path (params->dir, NULL))) {
			return -ENODEV;/*device not found*/
		}
		dir_node->properties = DIRECTORY_NODE_TYPE;
	}

	/* If dev_node created, but not attached to the filesystem driver */
	if (NULL == (dev_fd = (fat_file_description_t *) dev_node->fd)) {
		if((NULL == (dev_fd = pool_alloc(&fat_file_pool))) ||
				(NULL == (dev_fd->fs = pool_alloc(&fat_fs_pool)))) {
			if(NULL != dev_fd) {
				pool_free(&fat_file_pool, dev_fd);
			}
			return -ENOMEM;
		}
		dev_node->fd = dev_fd;
		dev_fd->fs->dev_id = dev_node->dev_id;
		dev_node->file_info = (void *) &fatfs_fop;
	}

	strcpy((char *) dev_fd->fs->root_name, params->dir);

	if(NULL == (fd = pool_alloc(&fat_file_pool))) {
		return -ENOMEM;
	}

	fd->fs = dev_fd->fs;
	dir_node->fs_type = &fatfs_drv;
	dir_node->fd = (void *) fd;

	return fat_mount_files(dir_node);
}

static int fatfs_create(void *par) {
	file_create_param_t *param;
	fat_file_description_t *fd, *parents_fd;
	node_t *node, *parents_node;
	int node_quantity;

	param = (file_create_param_t *) par;

	node = (node_t *)param->node;
	parents_node = (node_t *)param->parents_node;
	parents_fd = (fat_file_description_t *) parents_node->fd;

	if (DIRECTORY_NODE_TYPE == (node->properties & DIRECTORY_NODE_TYPE)) {
		node_quantity = 3; /* need create . and .. directory */
	}
	else {
		node_quantity = 1;
	}

	for (int count = 0; count < node_quantity; count ++) {
		if(0 < count) {
			if(1 == count) {
				strcat(param->path, "/.");
			}
			else if(2 == count) {
				strcat(param->path, ".");
			}
			if(NULL == (node = vfs_add_path (param->path, NULL))) {
				return -ENOMEM;
			}
		}

		if(NULL == (fd = pool_alloc(&fat_file_pool))) {
			vfs_del_leaf(node);
			return -ENOMEM;
		}
		fd->fs = parents_fd->fs;
		node->fs_type = &fatfs_drv;
		node->dev_id = parents_node->dev_id;
		node->fd = (void *)fd;

		/*
		 * fatfs_create_file called only once for the newly created directory.
		 * Creation of dir . and .. occurs into the function fatfs_create_file.
		 */
		if(0 >= count) {
			fatfs_create_file(par);
		}
	}
	/* cut /.. from end of PATH, if need */
	if (1 < node_quantity) {
		param->path[strlen(param->path) - 3] = '\0';
	}

	return 0;
}

static int fatfs_delete(const char *fname) {
	fat_file_description_t *fd;
	node_t *nod, *pointnod;
	char path [MAX_LENGTH_PATH_NAME];

	if(NULL == (nod = vfs_find_node(fname, NULL))) {
		return -1;
	}
	fd = (fat_file_description_t *)nod->fd;

	vfs_get_path_by_node(nod, path);

	/* need delete "." and ".." node for directory */
	if (DIRECTORY_NODE_TYPE == (nod->properties & DIRECTORY_NODE_TYPE)) {

		strcat(path, "/.");
		pointnod = vfs_find_node(path, NULL);
		vfs_del_leaf(pointnod);

		strcat(path, ".");
		pointnod = vfs_find_node(path, NULL);
		vfs_del_leaf(pointnod);

		path[strlen(path) - 3] = '\0';
	}

	/*
	 * remove the root name to give a name to fat file system name
	 * and set relative path in this file system
	 */
	path_cut_mount_dir(path, (char *) fd->fs->root_name);
	/* delete file system descriptor when delete root dir */
	if(0 == *path) {
		pool_free(&fat_fs_pool, fd->fs);
	}
	else {
		if (DIRECTORY_NODE_TYPE == (nod->properties & DIRECTORY_NODE_TYPE)) {
			if(fat_unlike_directory(fd, (uint8_t *) path,
				(uint8_t *) sector_buff)) {
				return -1;
			}
		}
		else {
			/* delete file from fat fs*/
			if(fat_unlike_file(fd, (uint8_t *) path,
				(uint8_t *) sector_buff)) {
				return -1;
			}
		}
	}
	pool_free(&fat_file_pool, fd);

	vfs_del_leaf(nod);
	return 0;
}

const fs_drv_t *fatfs_get_fs(void) {
    return &fatfs_drv;
}

DECLARE_FILE_SYSTEM_DRIVER(fatfs_drv);

