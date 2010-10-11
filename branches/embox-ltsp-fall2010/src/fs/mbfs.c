/**
 * @file
 * @details monitor bootloader filesystem
 *
 * @date 21.08.2009
 * @author Roman Ebstifeev
 */
#include <fs/mbfs.h>
#include <drivers/flash_drv_wrap.h>

// blk_usetable is temporary struct for faster free block searching

BLK_USEFLAG blk_usetable[FLASH_TOTAL_NUMBLOCKS];
MBFS_FILE mbfs_filetable[MBFS_FIDX_MAX];

bool reread_filetable() {
	void* _ftable_block;
	if (b_get_blockdata(MBFS_FTABLE_BLOCKNUM, &_ftable_block) < 0)
		return NULL;
	// in more complex flash interfaces we must check readed data
	// just assume it is not necessary for intel p30
	memcpy(mbfs_filetable, _ftable_block, sizeof(mbfs_filetable));
	return true;
}

bool sync_filetable() {
	void* _ftable_block;
	if (b_get_blockdata(MBFS_FTABLE_BLOCKNUM, &_ftable_block) < 0)
		return NULL;
	//if(_bdata[0]!=)
	memcpy(_ftable_block, mbfs_filetable, sizeof(mbfs_filetable));
	
	// last param is numwords
	if (b_put_blockdata(MBFS_FTABLE_BLOCKNUM, sizeof(mbfs_filetable)/4))
		return false;
	return true;
}

bool build_blk_usetable() {
	int nblock;
	for (nblock=0; nblock<MBFS_FTABLE_BLOCKNUM; nblock++)
		blk_usetable[nblock]=BLOCK_UNUSED;
	for (; nblock<FLASH_TOTAL_NUMBLOCKS; nblock++)
		blk_usetable[nblock]=BLOCK_USED;
	
	short fidx, obidx;
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++)
		for(obidx=0; obidx<MAX_NOWNBLOCKS; obidx++) {
			int bnum = mbfs_filetable[fidx].ownblocks[obidx];
			if (!IS_BLOCKNUM_SANE(bnum))
				break;
			if (blk_usetable[bnum] == BLOCK_USED) {
				TRACE("FS corrupted! (one block owned by two files)\n");
				return false;
			}
			blk_usetable[bnum]=BLOCK_USED;
		}
	
	return true;
}

bool mbfs_format_flash() {
	int i;
	
	blk_usetable[MBFS_FTABLE_BLOCKNUM] = BLOCK_USED;
	
	for (i=0; i<MBFS_FTABLE_BLOCKNUM; i++) {
		blk_usetable[i] = BLOCK_UNUSED;
	}
	
	short fidx;
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++) {
		RELEASE_FTBL_ITEM(mbfs_filetable,fidx);
		mbfs_filetable[fidx].name[0] = (char)0xAA; // it is only for easy debug
	}
	
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++)
		if (IS_FTBL_ITEM_USED(mbfs_filetable,fidx))
			TRACE(".");
	
	TRACE("rewriting filetable...\n");
	return sync_filetable();
}

short find_free_block() {
	short i;
	for (i=0; i<MBFS_FTABLE_BLOCKNUM; i++)
		if (blk_usetable[i] == BLOCK_UNUSED)
			return i;
	
	return MBFS_INVALID_BLOCKNUM;
}

short mbfs_get_file_idx (const char* file_name) {
	short fidx;
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++)
		if (strcmp(mbfs_filetable[fidx].name, file_name)==0)
			return fidx;

	return IDX_INVALID;
}
