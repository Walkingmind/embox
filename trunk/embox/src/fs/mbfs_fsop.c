/*
 * @file
 *
 * @date 28.08.2009
 * @author Roman Evstifeev
 */
#include <fs/mbfs.h>
#include <drivers/flash_drv_wrap.h>
#include <fs/fsop.h>

extern BLK_USEFLAG blk_usetable[FLASH_TOTAL_NUMBLOCKS];
extern MBFS_FILE mbfs_filetable[MBFS_FIDX_MAX];

static bool init(void) {
	int i;
	TRACE("mbfs init..\n");

	FLASH_WRITE_ENABLE;
	
	//s_unlock_block(0);
	TRACE("\nunlocking blocks..\n");
	// unlock all needed blocks
	for (i=0; i<=MBFS_FTABLE_BLOCKNUM; i++) {
		TRACE("%d ",i);
		if (i%20==0)
			TRACE("\n");
		if (s_unlock_block(i)<0) {
			TRACE ("FS init failed! (can't unlock blocks)\n");
			return false;
		}
	}
	
	TRACE("\nreading filetable..\n");
	if (!reread_filetable())
		return false;
	
	TRACE("biulding blk_usetable..\n");
	if (build_blk_usetable()!=NULL)
		return false;
		
	return true;
}

static size_t list_files (FLIST_ITEM* out_flist, int max_nitems) {
	//TODO: max_nitems check
	short fidx, flist_idx = 0;
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++)
		if (IS_FTBL_ITEM_USED(mbfs_filetable,fidx)) {
			strcpy (out_flist[flist_idx].name, mbfs_filetable[fidx].name);
			out_flist[flist_idx].size = mbfs_filetable[fidx].nbytes;
			flist_idx++;
		}
	return flist_idx;
}

static short get_file_idx (const char* file_name) {
	return mbfs_get_file_idx (file_name);
}

static size_t file_read (short fidx, size_t start_offset, void *buf, size_t nbytes) {
	if (start_offset >= mbfs_filetable[fidx].nbytes)
		return -1;
	
	TRACE ("start_offset 0x%08x\n",start_offset);
	short start_blockoffset = start_offset%(FLASH_MAIN_BLOCK_NUMBYTES*2);
	TRACE ("start_blockoffset 0x%08x\n",start_blockoffset);
	short starting_ownblock = (start_offset-start_blockoffset)/(FLASH_MAIN_BLOCK_NUMBYTES*2);
	TRACE ("starting_ownblock %d\n",starting_ownblock);
	short start_blocknum = mbfs_filetable[fidx].ownblocks[starting_ownblock];
	/*TRACE ("ownblocks: ");
	int i;
	for (i=0; i<MAX_NOWNBLOCKS; i++)
		TRACE ("%d ",ftable[fidx].ownblocks[i]);
	TRACE ("\n");*/
	
	if (!IS_BLOCKNUM_SANE(start_blocknum)) {
		LOG_WARN("FS inconsistency: file size and it's ownblocks struct conflict!");
		LOG_WARN("ownblocks entry for offset 0x%08x (%dth block) is invalid!", start_offset, starting_ownblock);
		return -1;
	}
	
	int block_nbytes_rest = FLASH_MAIN_BLOCK_NUMBYTES*2 - start_blockoffset;
	if (start_offset+nbytes > mbfs_filetable[fidx].nbytes)
		nbytes = mbfs_filetable[fidx].nbytes-start_offset;
	int nbytes_to_read = (nbytes>block_nbytes_rest)? block_nbytes_rest : nbytes;
	
	uint8_t* fblock;
	b_get_blockdata(start_blocknum, &fblock);
	memcpy(buf,fblock+start_blockoffset, nbytes_to_read);
	
	return nbytes_to_read;
}

static size_t file_write (short fidx, long start_offset, const void *buf, size_t nbytes) {
	//TODO: do we want to allow write start position above current file size? currently no
	//TODO: probably provide special constant for start_offset to start appending to the end of file
	if (start_offset > mbfs_filetable[fidx].nbytes)
		return -1;
	
	TRACE ("start_offset 0x%08x\n",start_offset);
	long start_blockoffset = start_offset%(FLASH_MAIN_BLOCK_NUMBYTES*2);
	TRACE ("start_blockoffset 0x%08x\n",start_blockoffset);
	short starting_ownblock = (start_offset-start_blockoffset)/(FLASH_MAIN_BLOCK_NUMBYTES*2);
	TRACE ("starting_ownblock %d\n",starting_ownblock);
	short start_blocknum = mbfs_filetable[fidx].ownblocks[starting_ownblock];
	/*TRACE ("ownblocks: ");
	int i;
	for (i=0; i<MAX_NOWNBLOCKS; i++)
		TRACE ("%d ",ftable[fidx].ownblocks[i]);
	TRACE ("\n");*/
	size_t block_nbytes_rest;
	if (IS_BLOCKNUM_SANE(start_blocknum)) {
		block_nbytes_rest = FLASH_MAIN_BLOCK_NUMBYTES*2 - start_blockoffset;
	}
	else {
		start_blocknum = find_free_block();
		if (!IS_BLOCKNUM_SANE(start_blocknum)) {
			TRACE ("no more free blocks for writing to file!\n");
			return -1;
		}
		TRACE ("new block @%d allocated for file\n",start_blocknum);
		blk_usetable[start_blocknum]=BLOCK_USED;
		block_nbytes_rest = FLASH_MAIN_BLOCK_NUMBYTES*2;
	}
	
	size_t nbytes_to_write = (nbytes>block_nbytes_rest)? block_nbytes_rest : nbytes;
	TRACE ("block_nbytes_rest: %d ;  nbytes: %d ;  nbytes_to_write: %d\n",block_nbytes_rest,nbytes,nbytes_to_write);
	
	uint8_t* fblock;
	// get the whole block data
	b_get_blockdata(start_blocknum, &fblock);
	// rewrite needed bytes
	memcpy(fblock+start_blockoffset, buf, nbytes_to_write);
	// put block back to flash
	if (b_put_blockdata(start_blocknum, B_PUT_WHOLE_BLOCK)) {
		// TODO: journalig? retry with other block?
		mbfs_filetable[fidx].ownblocks[starting_ownblock] = MBFS_INVALID_BLOCKNUM;
		return -1;
	}
	
	
	if (mbfs_filetable[fidx].nbytes < start_offset+nbytes_to_write)
		mbfs_filetable[fidx].nbytes = start_offset+nbytes_to_write;
	
	mbfs_filetable[fidx].ownblocks[starting_ownblock] = start_blocknum;
	
	// WARNING: sync_filetable currently diasbled here to prevent wearing of ftable block
	// WARNING: remember to call sync() or close() to ensure filetable was modified on flash
	/*
	if (!sync_filetable()) {
		return -1;
	}*/
	
	return nbytes_to_write;
}

static bool format_flash() {
	return mbfs_format_flash();
}

static bool sync() {
	return sync_filetable();
}

static short create_file (const char *file_name) {
	short fidx, obidx;
	for (fidx=0; fidx<MBFS_FIDX_MAX; fidx++)
		if (!IS_FTBL_ITEM_USED(mbfs_filetable,fidx)) {
			TRACE("creating %s with idx %d\n",file_name, fidx);
			ACQUIRE_FTBL_ITEM(mbfs_filetable,fidx);
			//TRACE("after : %d\n", ftable[fidx].nbytes);
			strncpy(mbfs_filetable[fidx].name, file_name, MAX_FILENAME_LEN);
			for (obidx=0; obidx<MAX_NOWNBLOCKS; obidx++)
				mbfs_filetable[fidx].ownblocks[obidx] = IDX_INVALID;
			break;
		}
	
	if (fidx == MBFS_FIDX_MAX)
		return IDX_INVALID;
	
	if (!sync_filetable())
		return IDX_INVALID;
	
	return fidx;
}

static bool delete_file (const char *file_name) {
	short fidx,obidx; 
	if (fidx=mbfs_get_file_idx(file_name) == IDX_INVALID)
		return false;
	
	for (obidx=0; obidx<MAX_NOWNBLOCKS; obidx++) {
		int bnum = mbfs_filetable[fidx].ownblocks[obidx];
		if (bnum == MBFS_INVALID_BLOCKNUM)
			break;
		blk_usetable[bnum]=BLOCK_UNUSED;
	}
	
	RELEASE_FTBL_ITEM(mbfs_filetable,fidx);
	
	return sync_filetable();
}

static int get_capacity() {
	return FLASH_MAIN_BLOCK_NUMBYTES*2;
}

static int get_freespace() {
	//TODO
	return FLASH_MAIN_BLOCK_NUMBYTES*2;
}

FSOP mbfs_fsop ={
	(FS_INIT_FUNC) init,
	
	(FS_LISTFILES_FUNC) list_files,
	(FS_GETFILEIDX_FUNC) get_file_idx,
	
	(FILE_CREATE_FUNC) create_file,
	(FILE_DELETE_FUNC) delete_file,
	
	(FILE_READ_FUNC) file_read,
	(FILE_WRITE_FUNC) file_write,
	
	(FS_FORMAT_FUNC) format_flash,
	(FS_SYNC_FUNC) sync,
	
	(FS_GETCAPACITY_FUNC) get_capacity,
	(FS_GETFREESPACE_FUNC) get_freespace
};
