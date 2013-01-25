/**
 * @file
 * @brief
 *
 * @date 04.12.2012
 * @author Andrey Gazukin
 */


#ifndef EXT_H_
#define EXT_H_
#include <mem/page.h>
/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)fs.h	8.10 (Berkeley) 10/27/94
 *  Modified for ext2fs by Manuel Bouyer.
 */

/*
 * Copyright (c) 1997 Manuel Bouyer.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	@(#)fs.h	8.10 (Berkeley) 10/27/94
 *  Modified for ext2fs by Manuel Bouyer.
 */


#define SECTOR_SIZE 512
#define BBSIZE		1024
#define SBSIZE		1024
#define	BBOFF		((long)(0))
#define	SBOFF		((long)(BBOFF + BBSIZE))
/*#define	BBLOCK		((long long)(0))
#define	SBLOCK		((long long)(BBLOCK + BBSIZE / SECTOR_SIZE))
*/

/*
 * MINBSIZE is the smallest allowable block size.
 * MINBSIZE must be big enough to hold a cylinder group block,
 * thus changes to (struct cg) must keep its size within MINBSIZE.
 * Note that super blocks are always of size SBSIZE,
 * and that both SBSIZE and MAXBSIZE must be >= MINBSIZE.
 */
#define LOG_MINBSIZE	10
#define MINBSIZE	(1 << LOG_MINBSIZE)

/*
 * Filesystem identification
 */
#define	E2FS_MAGIC	0xef53	/* the ext2fs magic number */
#define E2FS_REV0	0	/* GOOD_OLD revision */
#define E2FS_REV1	1	/* Support compat/incompat features */

/* compatible/incompatible features */
#define EXT2F_COMPAT_PREALLOC		0x0001
#define EXT2F_COMPAT_HASJOURNAL		0x0004
#define EXT2F_COMPAT_RESIZE		    0x0010

#define EXT2F_ROCOMPAT_SPARSESUPER	0x0001
#define EXT2F_ROCOMPAT_LARGEFILE	0x0002
#define EXT2F_ROCOMPAT_BTREE_DIR	0x0004

//#define EXT2F_INCOMPAT_COMP			0x0001
//#define EXT2F_INCOMPAT_FTYPE		0x0002

#define EXT2F_INCOMPAT_COMPRESSION       0x0001
#define EXT2F_INCOMPAT_FILETYPE          0x0002
#define EXT2F_INCOMPAT_RECOVER           0x0004
#define EXT2F_INCOMPAT_JOURNAL_DEV       0x0008
#define EXT2F_INCOMPAT_META_BG           0x0010
#define EXT2F_INCOMPAT_ANY               0xffffffff

/*
 * Features supported in this implementation
 *
 * We support the following REV1 features:
 * - EXT2F_ROCOMPAT_SPARSESUPER
 *    superblock backups stored only in cg_has_sb(bno) groups
 * - EXT2F_ROCOMPAT_LARGEFILE
 *    use e2di_dacl in struct ext2fs_dinode to store
 *    upper 32bit of size for >2GB files
 * - EXT2F_INCOMPAT_FTYPE
 *    store file type to e2d_type in struct ext2fs_direct
 *    (on REV0 e2d_namlen is uint16_t and no e2d_type, like ffs)
 */
#define EXT2F_COMPAT_SUPP		0x0000
#define EXT2F_ROCOMPAT_SUPP		(EXT2F_ROCOMPAT_SPARSESUPER \
					 | EXT2F_ROCOMPAT_LARGEFILE)
#define EXT2F_INCOMPAT_SUPP		EXT2F_INCOMPAT_FILETYPE

#define HAS_COMPAT_FEATURE(sp, mask)                        \
        ( (sp)->s_feature_compat & (mask) )
#define HAS_RO_COMPAT_FEATURE(sp, mask)                     \
	( (sp)->s_feature_ro_compat & (mask) )
#define HAS_INCOMPAT_FEATURE(sp, mask)                      \
	( (sp)->s_feature_incompat & (mask) )
/*
 * If the EXT2F_ROCOMPAT_SPARSESUPER flag is set, the cylinder group has a
 * copy of the super and cylinder group descriptors blocks only if it's
 * 1, a power of 3, 5 or 7
 */

/* EXT2FS metadatas are stored in little-endian byte order. These macros
 * helps reading theses metadatas
 */

//#if defined(__LITTLE_ENDIAN)
#	define h2fs16(x) (x)
#	define h2fs32(x) (x)
#	define h2fs64(x) (x)
#	define fs2h16(x) (x)
#	define fs2h32(x) (x)
#	define fs2h64(x) (x)
#	define e2fs_sbload(old, new) memcpy((new), (old), SBSIZE);
#	define e2fs_cgload(old, new, size) memcpy((new), (old), (size));
#	define e2fs_sbsave(old, new) memcpy((new), (old), SBSIZE);
#	define e2fs_cgsave(old, new, size) memcpy((new), (old), (size));
/*#else
void e2fs_sb_bswap(struct ext2fs *, struct ext2fs *);
void e2fs_cg_bswap(struct ext2_gd *, struct ext2_gd *, int);
#	define h2fs16(x) bswap16(x)
#	define h2fs32(x) bswap32(x)
#	define h2fs64(x) bswap64(x)
#	define fs2h16(x) bswap16(x)
#	define fs2h32(x) bswap32(x)
#	define fs2h64(x) bswap64(x)
#	define e2fs_sbload(old, new) e2fs_sb_bswap((old), (new))
#	define e2fs_cgload(old, new, size) e2fs_cg_bswap((old), (new), (size));
#	define e2fs_sbsave(old, new) e2fs_sb_bswap((old), (new))
#	define e2fs_cgsave(old, new, size) e2fs_cg_bswap((old), (new), (size));
#endif
*/
/*
 * Turn file system block numbers into disk block addresses.
 * This maps file system blocks to device size blocks.
 */
#define fsbtodb(fs, b)	((b) << (fs)->s_fsbtodb)
#define dbtofsb(fs, b)	((b) >> (fs)->s_fsbtodb)

/*
 * Macros for handling inode numbers:
 *	 inode number to file system block offset.
 *	 inode number to cylinder group number.
 *	 inode number to file system block address.
 */
#define	ino_to_cg(fs, x)	(((x) - 1) / (fs)->e2sb.s_inodes_per_group)
#define	ino_to_fsba(fs, x)						\
	((fs)->e2fs_gd[ino_to_cg((fs), (x))].inode_table +		\
	(((x) - 1) % (fs)->e2sb.s_inodes_per_group) / (fs)->s_inodes_per_block)
#define	ino_to_fsbo(fs, x)	(((x) - 1) % (fs)->s_inodes_per_block)

/*
 * Give cylinder group number for a file system block.
 * Give cylinder group block number for a file system block.
 */
#define	dtog(fs, d) (((d) - (fs)->e2sb.e2fs_first_dblock) / (fs)->e2sb.e2fs_fpg)
#define	dtogd(fs, d) \
	(((d) - (fs)->e2sb.e2fs_first_dblock) % (fs)->e2sb.e2fs_fpg)

/*
 * The following macros optimize certain frequently calculated
 * quantities by using shifts and masks in place of divisions
 * modulos and multiplications.
 */
#define blkoff(fs, loc)		/* calculates (loc % fs->e2fs_bsize) */ \
	((loc) & (fs)->s_qbmask)
#define lblktosize(fs, blk)	/* calculates (blk * fs->e2fs_bsize) */ \
	((blk) << (fs)->s_bshift)
#define lblkno(fs, loc)		/* calculates (loc / fs->e2fs_bsize) */ \
	((loc) >> (fs)->s_bshift)
#define blkroundup(fs, size)	/* calculates roundup(size, fs->e2fs_bsize) */ \
	(((size) + (fs)->e2fs_qbmask) & (fs)->e2fs_bmask)
#define fragroundup(fs, size)	/* calculates roundup(size, fs->e2fs_bsize) */ \
	(((size) + (fs)->e2fs_qbmask) & (fs)->e2fs_bmask)
/*
 * Determine the number of available frags given a
 * percentage to hold in reserve.
 */
#define freespace(fs) \
   ((fs)->e2sb.e2fs_fbcount - (fs)->e2sb.e2fs_rbcount)

/*
 * Number of indirects in a file system block.
 */
#define	NINDIR(fs)	((fs)->s_block_size / sizeof(uint32_t))

#define NXADDR	2
#define	NDADDR	12			/* Direct addresses in inode. */
#define	NIADDR	3			/* Indirect addresses in inode. */

#define EXT2_MAXSYMLINKLEN ((NDADDR+NIADDR) * sizeof (uint32_t))

/*
 * The root inode is the root of the file system.  Inode 0 can't be used for
 * normal purposes and bad blocks are normally linked to inode 1, thus
 * the root inode is 2.
 * Inode 3 to 10 are reserved in ext2fs.
 */
#define	EXT2_BADBLKINO		((unsigned long)1)
#define	EXT2_ROOTINO		((unsigned long)2)
#define	EXT2_ACLIDXINO		((unsigned long)3)
#define	EXT2_ACLDATAINO		((unsigned long)4)
#define	EXT2_BOOTLOADERINO	((unsigned long)5)
#define	EXT2_UNDELDIRINO	((unsigned long)6)
#define	EXT2_RESIZEINO		((unsigned long)7)
#define	EXT2_JOURNALINO		((unsigned long)8)
#define	EXT2_FIRSTINO		((unsigned long)11)

#define	MAXPATHLEN      	1024
#define	MAXSYMLINKS			32
#define	EXT2FS_MAXNAMLEN	255

/* Size of on-disk inode. */
#define EXT2_REV0_DINODE_SIZE	sizeof(struct ext2fs_dinode)
#define EXT2_DINODE_SIZE(fs)	((fs)->e2sb.s_rev_level > E2FS_REV0 ?	\
				    (fs)->e2sb.s_inode_size :	\
				    EXT2_REV0_DINODE_SIZE)

#	define e2fs_iload(old, new)	\
		memcpy((new),(old),sizeof(struct ext2fs_dinode))
#	define e2fs_isave(old, new)	\
		memcpy((new),(old),sizeof(struct ext2fs_dinode))

#define	howmany(x, y)	(((x)+((y)-1))/(y))

#define NO_BLOCK		((uint32_t) 0)
#define ROOT_INODE         2   /* inode number for root directory */
#define BOOT_BLOCK       0 /* block number of boot block */
#define START_BLOCK      2 /* first block of FS (not counting SB) */
#define BLOCK_ADDRESS_BYTES	4     /* bytes per address */

#define EXT2_NDIR_BLOCKS        12
#define EXT2_IND_BLOCK          EXT2_NDIR_BLOCKS
#define EXT2_DIND_BLOCK         (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK         (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS           (EXT2_TIND_BLOCK + 1)

#define WMAP_FREE           (1 << 0)

#define EXT2_PREALLOC_BLOCKS		8
#define NR_INODES        512
#define CHAR_BIT 8

/* Ext2 directory file types (not the same as FFS. Sigh.) */
#define EXT2_FT_UNKNOWN         0
#define EXT2_FT_REG_FILE        1
#define EXT2_FT_DIR             2
#define EXT2_FT_CHRDEV          3
#define EXT2_FT_BLKDEV          4
#define EXT2_FT_FIFO            5
#define EXT2_FT_SOCK            6
#define EXT2_FT_SYMLINK         7

#define LOOK_UP            0 /* tells search_dir to lookup string */
#define ENTER              1 /* tells search_dir to make dir entry */
#define DELETE             2 /* tells search_dir to delete entry */
#define IS_EMPTY           3 /* tells search_dir to ret. OK or ENOTEMPTY */

#define DIR_ENTRY_ALIGN         4
/* ino + rec_len + name_len + file_type, doesn't include name and padding */
#define MIN_DIR_ENTRY_SIZE	8

#define DIR_ENTRY_CONTENTS_SIZE(d) (MIN_DIR_ENTRY_SIZE + (d)->e2d_namlen)
/* size with padding */
#define DIR_ENTRY_ACTUAL_SIZE(d) (DIR_ENTRY_CONTENTS_SIZE(d) + \
        ((DIR_ENTRY_CONTENTS_SIZE(d) & 0x03) == 0 ? 0 : \
			DIR_ENTRY_ALIGN - (DIR_ENTRY_CONTENTS_SIZE(d) & 0x03) ))

/* How many bytes can be taken from the end of dentry */
#define DIR_ENTRY_SHRINK(d)    ((d)->e2d_reclen \
					- DIR_ENTRY_ACTUAL_SIZE(d))

/* Dentry can have padding, which can be used to enlarge namelen */
#define DIR_ENTRY_MAX_NAME_LEN(d)	((d)->e2d_reclen \
						- MIN_DIR_ENTRY_SIZE)

#define usizeof(t) ((unsigned) sizeof(t))

#define FS_BITMAP_CHUNKS(b) ((b)/usizeof (uint32_t))/* # map chunks/blk   */
#define FS_BITCHUNK_BITS		(usizeof(uint32_t) * CHAR_BIT)
#define FS_BITS_PER_BLOCK(b)	(FS_BITMAP_CHUNKS(b) * FS_BITCHUNK_BITS)

#define DIRTY 1

#define EXT2_GOOD_OLD_INODE_SIZE	128
#define EXT2_GOOD_OLD_FIRST_INO		11
#define EXT2_GOOD_OLD_REV		0

#define EXT2_INODE_SIZE(s)	(((s)->s_rev_level == EXT2_GOOD_OLD_REV) ? \
				EXT2_GOOD_OLD_INODE_SIZE : \
							(s)->s_inode_size)
#define EXT2_FIRST_INO(s)	(((s)->s_rev_level == EXT2_GOOD_OLD_REV) ? \
				EXT2_GOOD_OLD_FIRST_INO : \
							(s)->s_first_ino)

/*
 * Super block for an ext2fs file system.
 */
 struct ext2sb {
	uint32_t  s_inodes_count;      /* Inodes count */
	uint32_t  s_blocks_count;      /* Blocks count */
	uint32_t  s_r_blocks_count;    /* Reserved blocks count */
	uint32_t  s_free_blocks_count; /* Free blocks count */
	uint32_t  s_free_inodes_count; /* Free inodes count */
	uint32_t  s_first_data_block;  /* First Data Block */
	uint32_t  s_log_block_size;    /* Block size */
	uint32_t  s_log_frag_size;     /* Fragment size */
	uint32_t  s_blocks_per_group;  /* # Blocks per group */
	uint32_t  s_frags_per_group;   /* # Fragments per group */
	uint32_t  s_inodes_per_group;  /* # Inodes per group */
	uint32_t  s_mtime;             /* Mount time */
	uint32_t  s_wtime;             /* Write time */
	u16_t  s_mnt_count;            /* Mount count */
	u16_t  s_max_mnt_count;        /* Maximal mount count */
	u16_t  s_magic;                /* Magic signature */
	u16_t  s_state;                /* File system state */
	u16_t  s_errors;               /* Behaviour when detecting errors */
	u16_t  s_minor_rev_level;      /* minor revision level */
	uint32_t  s_lastcheck;         /* time of last check */
	uint32_t  s_checkinterval;     /* max. time between checks */
	uint32_t  s_creator_os;        /* OS */
	uint32_t  s_rev_level;         /* Revision level */
	u16_t  s_def_resuid;           /* Default uid for reserved blocks */
	u16_t  s_def_resgid;           /* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 *
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	uint32_t  s_first_ino;         /* First non-reserved inode */
	u16_t  s_inode_size;           /* size of inode structure */
	u16_t  s_block_group_nr;       /* block group # of this superblock */
	uint32_t  s_feature_compat;    /* compatible feature set */
	uint32_t  s_feature_incompat;  /* incompatible feature set */
	uint32_t  s_feature_ro_compat; /* readonly-compatible feature set */
	u8_t   s_uuid[16];             /* 128-bit uuid for volume */
	char   s_volume_name[16];      /* volume name */
	char   s_last_mounted[64];     /* directory where last mounted */
	uint32_t  s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	u8_t    s_prealloc_blocks;      /* Nr of blocks to try to preallocate*/
	u8_t    s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
	u16_t   s_padding1;
	/*
	 * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	u8_t    s_journal_uuid[16];     /* uuid of journal superblock */
	uint32_t   s_journal_inum;      /* inode number of journal file */
	uint32_t   s_journal_dev;       /* device number of journal file */
	uint32_t   s_last_orphan;       /* start of list of inodes to delete */
	uint32_t   s_hash_seed[4];      /* HTREE hash seed */
	u8_t    s_def_hash_version;     /* Default hash version to use */
	u8_t    s_reserved_char_pad;
	u16_t   s_reserved_word_pad;
	uint32_t   s_default_mount_opts;
	uint32_t   s_first_meta_bg;     /* First metablock block group */
	uint32_t   s_reserved[190];     /* Padding to the end of the block */
};

/* ext2 file system block group descriptor */
struct ext2_gd {
	uint32_t  block_bitmap;     /* Blocks bitmap block */
    uint32_t  inode_bitmap;     /* Inodes bitmap block */
    uint32_t  inode_table;      /* Inodes table block */
    u16_t  free_blocks_count;   /* Free blocks count */
    u16_t  free_inodes_count;   /* Free inodes count */
    u16_t  used_dirs_count;     /* Directories count */
    u16_t  pad;
    uint32_t  reserved[3];
};

/* ext2 file system directory descriptor */
struct	ext2fs_direct {
	uint32_t e2d_ino;		/* inode number of entry */
	uint16_t e2d_reclen;	/* length of this record */
	uint8_t e2d_namlen;		/* length of string in d_name */
	uint8_t e2d_type;		/* file type */
	char e2d_name[EXT2FS_MAXNAMLEN];/* name with length<=EXT2FS_MAXNAMLEN */
};

/* Current position in block */
#define CUR_DISC_DIR_POS(cur_desc, base)  ((char*)cur_desc - (char*)base)
/* Return pointer to the next dentry */
#define NEXT_DISC_DIR_DESC(cur_desc)	((struct ext2fs_direct*)\
					((char*)cur_desc + cur_desc->e2d_reclen))
/* Return next dentry's position in block */
#define NEXT_DISC_DIR_POS(cur_desc, base) (cur_desc->e2d_reclen +\
					   CUR_DISC_DIR_POS(cur_desc, base))

/*
 * To avoid having a lot of filesystem-block sized buffers lurking (which
 * could be 32k) we only keep a few entries of the indirect block map.
 * With 8k blocks, 2^8 blocks is ~500k so we reread the indirect block
 * ~13 times pulling in a 6M kernel.
 * The cache size must be smaller than the smallest filesystem block,
 * so LN2_IND_CACHE_SZ <= 9 (UFS2 and 4k blocks).
 */
#define LN2_IND_CACHE_SZ	6
#define IND_CACHE_SZ		(1 << LN2_IND_CACHE_SZ)
#define IND_CACHE_MASK		(IND_CACHE_SZ - 1)

struct ext2fs_dinode {
	uint16_t	i_mode;	/*   0: IFMT, permissions; see below. */
	uint16_t	i_uid;	/*   2: Owner UID */
	uint32_t	i_size;	/*	 4: Size (in bytes) */
	uint32_t	i_atime;	/*	 8: Acces time */
	uint32_t	i_ctime;	/*	12: Create time */
	uint32_t	i_mtime;	/*	16: Modification time */
	uint32_t	i_dtime;	/*	20: Deletion time */
	uint16_t	i_gid;	/*  24: Owner GID */
	uint16_t	i_links_count;	/*  26: File link count */
	uint32_t	i_blocks;	/*  28: Blocks count */
	uint32_t	i_flags;	/*  32: Status flags (chflags) */
	union {
		struct {
				u32_t  l_i_reserved1;
		} linux1;
		struct {
				u32_t  h_i_translator;
		} hurd1;
		struct {
				u32_t  m_i_reserved1;
		} masix1;
	} osd1;
	uint32_t	i_block[NDADDR + NIADDR]; /* 40: disk blocks */
	uint32_t	i_gen;	/* 100: generation number */
	uint32_t	i_facl;	/* 104: file ACL (not implemented) */
	uint32_t	i_dacl;	/* 108: dir ACL (not implemented) */
	uint32_t	i_faddr;	/* 112: fragment address */
    union {
        struct {
            u8_t    l_i_frag;       // Fragment number /
            u8_t    l_i_fsize;      // Fragment size /
            u16_t   i_pad1;
            u16_t  l_i_uid_high;   // these 2 fields    /
            u16_t  l_i_gid_high;   // were reserved2[0] /
            u32_t   l_i_reserved2;
        } linux2;
        struct {
            u8_t    h_i_frag;       // Fragment number /
            u8_t    h_i_fsize;      // Fragment size /
            u16_t  h_i_mode_high;
            u16_t  h_i_uid_high;
            u16_t  h_i_gid_high;
            u32_t  h_i_author;
        } hurd2;
        struct {
            u8_t    m_i_frag;       // Fragment number /
            u8_t    m_i_fsize;      // Fragment size /
            u16_t   m_pad1;
            u32_t   m_i_reserved2[2];
        } masix2;
    } osd2;                         // OS dependent 2 /
};

/* in-memory data for ext2fs */
typedef struct ext2_fs_info {
	char mntfrom[MAX_LENGTH_PATH_NAME];
	char mntto[MAX_LENGTH_PATH_NAME];
	struct ext2sb e2sb;

	int32_t s_bshift;	/* ``lblkno'' calc of logical blkno */
	int32_t s_bmask;	/* ``blkoff'' calc of blk offsets */
	int64_t s_qbmask;	/* ~fs_bmask - for use with quad size */
	int32_t	s_fsbtodb;	/* fsbtodb and dbtofsb shift constant */
	int32_t	s_ncg;	/* number of cylinder groups */

	/* The following items are only used when the super_block is in memory. */
	struct	ext2_gd *e2fs_gd; /* group descripors */
	uint32_t   s_block_size;           /* block size in bytes. */
	uint32_t   s_inodes_per_block;     /* Number of inodes per block */
	uint32_t   s_itb_per_group;        /* Number of inode table blocks per group */
	uint32_t   s_gdb_count;            /* Number of group descriptor blocks */
	uint32_t   s_desc_per_block;       /* Number of group descriptors per block */
	uint32_t   s_groups_count;         /* Number of groups in the fs */
	size_t     s_page_count;		   /* Number of pages of embox sor file r/w buffer*/
	u8_t    s_blocksize_bits;       /* Used to calculate offsets
									 * (e.g. inode block),
									 * always s_log_block_size+10.
									 */

	u16_t   s_sectors_in_block; /* s_block_size / 512 */
	uint32_t   s_max_size;         /* maximum file size on this device */
	uint32_t s_bsearch;	/* all data blocks  below this block are in use*/
	int     s_igsearch; /* all groups below this one have no free inodes */
	char    s_is_root;
	uint32_t   s_dirs_counter;
} ext2_fs_info_t;

/*
 * In-core open file.
 */
typedef struct ext2_file_info {
	struct ext2fs_dinode	f_di;		/* copy of on-disk inode */
	uint		f_nishift;	/* for blocks in indirect block */
	int32_t		f_ind_cache_block;
	int32_t		f_ind_cache[IND_CACHE_SZ];

	char		*f_buf;		/* buffer for data block */
	size_t		f_buf_size;	/* size of data block */
	int64_t		f_buf_blkno;	/* block number of data block */
	long		f_pointer;	/* local seek pointer */

	ino_t f_num;                /* inode number on its (minor) device */
	uint32_t f_bsearch;         /* where to start search for new blocks,
								 * also this is last allocated block.
								 */
	long f_last_pos_bl_alloc;
								/* last write position for which we allocated
								 * a new block (should be block i_bsearch).
								 * used to check for sequential operation.
								 */
	//long f_last_dpos;           /* where to start dentry search */
	//int f_last_dentry_size;	    /* size of last found dentry */
} ext2_file_info_t;

union fsdata_u {
    char b__data[PAGE_SIZE()];             /* ordinary user data */
/* indirect block */
    uint32_t b__ind[PAGE_SIZE()/sizeof(uint32_t)];
/* bit map block */
    uint32_t b__bitmap[FS_BITMAP_CHUNKS(PAGE_SIZE())];
};

#define b_data(data)   ((union fsdata_u *) data)->b__data
#define b_ind(data) ((union fsdata_u *) data)->b__ind
#define b_bitmap(data) ((union fsdata_u *) data)->b__bitmap

/* balloc.c */
//void ext2_discard_preallocated_blocks(struct nas *nas);
uint32_t ext2_alloc_block(struct nas *nas, uint32_t goal);
void ext2_free_block(struct nas *nas, uint32_t bit);

int ext2_read_sector(struct nas *nas, char *buffer,
		uint32_t count, uint32_t sector);
int ext2_write_sector(struct nas *nas, char *buffer,
		uint32_t count, uint32_t sector);
struct ext2_gd* ext2_get_group_desc(unsigned int bnum, struct ext2_fs_info *fsi);

uint32_t ext2_setbit(uint32_t *bitmap, uint32_t max_bits, unsigned int word);
int ext2_unsetbit(uint32_t *bitmap, uint32_t bit);

#endif /* EXT_H_ */
