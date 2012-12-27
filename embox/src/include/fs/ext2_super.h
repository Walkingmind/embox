/**
 * @file
 * @brief
 *
 * @date 24.12.2012
 * @author Andrey Gazukin
 */
#ifndef EXT2_SUPER_H_
#define EXT2_SUPER_H_

/* Super block table. The root file system and every mounted file system
 * has an entry here. The entry holds information about the sizes of the bit
 * maps and inodes.
 *
 * A super_block slot is free if s_dev == NO_DEV.
 *
 */


/* super_block (on-disk part) was taken from linux/include/linux/ext2_fs.h */
struct super_block {
    uint32_t  s_inodes_count;         /* Inodes count */
    uint32_t  s_blocks_count;         /* Blocks count */
    uint32_t  s_r_blocks_count;       /* Reserved blocks count */
    uint32_t  s_free_blocks_count;    /* Free blocks count */
    uint32_t  s_free_inodes_count;    /* Free inodes count */
    uint32_t  s_first_data_block;     /* First Data Block */
    uint32_t  s_log_block_size;       /* Block size */
    uint32_t  s_log_frag_size;        /* Fragment size */
    uint32_t  s_blocks_per_group;     /* # Blocks per group */
    uint32_t  s_frags_per_group;      /* # Fragments per group */
    uint32_t  s_inodes_per_group;     /* # Inodes per group */
    uint32_t  s_mtime;                /* Mount time */
    uint32_t  s_wtime;                /* Write time */
    u16_t  s_mnt_count;            /* Mount count */
    u16_t  s_max_mnt_count;        /* Maximal mount count */
    u16_t  s_magic;                /* Magic signature */
    u16_t  s_state;                /* File system state */
    u16_t  s_errors;               /* Behaviour when detecting errors */
    u16_t  s_minor_rev_level;      /* minor revision level */
    uint32_t  s_lastcheck;            /* time of last check */
    uint32_t  s_checkinterval;        /* max. time between checks */
    uint32_t  s_creator_os;           /* OS */
    uint32_t  s_rev_level;            /* Revision level */
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
    uint32_t  s_first_ino;            /* First non-reserved inode */
    u16_t  s_inode_size;           /* size of inode structure */
    u16_t  s_block_group_nr;       /* block group # of this superblock */
    uint32_t  s_feature_compat;       /* compatible feature set */
    uint32_t  s_feature_incompat;     /* incompatible feature set */
    uint32_t  s_feature_ro_compat;    /* readonly-compatible feature set */
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
    uint32_t   s_journal_inum;         /* inode number of journal file */
    uint32_t   s_journal_dev;          /* device number of journal file */
    uint32_t   s_last_orphan;          /* start of list of inodes to delete */
    uint32_t   s_hash_seed[4];         /* HTREE hash seed */
    u8_t    s_def_hash_version;     /* Default hash version to use */
    u8_t    s_reserved_char_pad;
    u16_t   s_reserved_word_pad;
    uint32_t   s_default_mount_opts;
    uint32_t   s_first_meta_bg;        /* First metablock block group */
    uint32_t   s_reserved[190];        /* Padding to the end of the block */

    /* The following items are only used when the super_block is in memory. */
    uint32_t   s_inodes_per_block;     /* Number of inodes per block */
    uint32_t   s_itb_per_group;        /* Number of inode table blocks per group */
    uint32_t   s_gdb_count;            /* Number of group descriptor blocks */
    uint32_t   s_desc_per_block;       /* Number of group descriptors per block */
    uint32_t   s_groups_count;         /* Number of groups in the fs */
    u8_t    s_blocksize_bits;       /* Used to calculate offsets
                                     * (e.g. inode block),
                                     * always s_log_block_size+10.
                                     */
    struct group_desc *s_group_desc; /* Group descriptors read into RAM */

    u16_t   s_block_size;       /* block size in bytes. */
    u16_t   s_sectors_in_block; /* s_block_size / 512 */
    uint32_t   s_max_size;         /* maximum file size on this device */
    dev_t   s_dev;              /* whose super block is this? */
    int     s_rd_only;          /* set to 1 if file sys mounted read only */
    uint32_t s_bsearch;	/* all data blocks  below this block are in use*/
    int     s_igsearch; /* all groups below this one have no free inodes */
    char    s_is_root;
    uint32_t   s_dirs_counter;

};


/* Structure of a blocks group descriptor.
 * On disk stored in little endian format.
 */
struct group_desc
{
    uint32_t  block_bitmap;        /* Blocks bitmap block */
    uint32_t  inode_bitmap;        /* Inodes bitmap block */
    uint32_t  inode_table;         /* Inodes table block */
    u16_t  free_blocks_count;   /* Free blocks count */
    u16_t  free_inodes_count;   /* Free inodes count */
    u16_t  used_dirs_count;     /* Directories count */
    u16_t  pad;
    uint32_t  reserved[3];
};

#define IMAP	0           /* operating on the inode bit map */
#define BMAP	1           /* operating on the block bit map */
#define IMAPD	2           /* operating on the inode bit map, inode is dir */

#endif /* EXT2_SUPER_H_ */
