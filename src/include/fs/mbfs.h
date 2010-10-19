/**
 * @file
 * @details monitor bootloader filesystem
 *
 * @date 21.07.2009
 * @author Roman Evstifeev
 */
#ifndef MBFS_H_
#define MBFS_H_

#include <drivers/flash_template.h>
//#include <fs/file_interface.h>

//#define FLASH_WRITE_ENABLE      *((volatile uint32_t*)0x80000000) |= (1<<11)
// TODO: use FLASH_WRITE_DISABLE after flash write operations
//#define FLASH_WRITE_DISABLE     *((volatile uint32_t*)0x80000000) &= ~(1<<11)

typedef enum {
	BLOCK_UNUSED,
	BLOCK_USED
} BLK_USEFLAG;

// blocks 255-258 are small params blocks
#define MBFS_FTABLE_BLOCKNUM 258 //255
#define MBFS_INVALID_BLOCKNUM (-1)
#define IS_BLOCKNUM_SANE(bnum) ((bnum>=0) && (bnum<MBFS_FTABLE_BLOCKNUM)) ? true : false

// 32 blocks per file is enough... probably
#define MAX_NOWNBLOCKS 32

typedef struct  {
	long nbytes;
	char name[MAX_FILENAME_LEN];
	short ownblocks[MAX_NOWNBLOCKS];
} MBFS_FILE;

// max possible files count depends on how much MBFS_FILE stucts can fit in mainblock
//#define MBFS_FIDX_MAX (FLASH_MAIN_BLOCK_NUMBYTES*2)/sizeof(MBFS_FILE)
#define MBFS_FIDX_MAX 100
#define IS_FIDX_VALID(idx) ((idx>0) && (idx<MBFS_FIDX_MAX)) ? true : false
#define IS_FTBL_ITEM_USED(ftable,idx) (ftable[idx].nbytes>=0) ? true : false
#define RELEASE_FTBL_ITEM(ftable,idx) ftable[idx].nbytes=(-2)
#define ACQUIRE_FTBL_ITEM(ftable,idx) ftable[idx].nbytes=0

bool reread_filetable(void);
bool sync_filetable(void);
bool mbfs_format_flash(void);
bool build_blk_usetable(void);
short find_free_block(void);
short mbfs_get_file_idx (const char* file_name);

#endif /* MBFS_H_ */
