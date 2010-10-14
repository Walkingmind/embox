/**
 * @file
 *
 * @date 28.08.2009
 * @author Roman Evstifeev
 */
#ifndef FLASHWRAP_H_
#define FLASHWRAP_H_

#define s_get_block_address(bnum,paddr) flash_get_block_address(bnum,paddr)

#define s_get_block_size(bnum) flash_get_block_size (bnum)

int s_block_getstatus(int NBLOCK, uint32_t* blkstat);
int s_erase_block(int NBLOCK);


//************* LOCK / UNLOCK *****************

int s_lock_block(int NBLOCK);
int s_unlock_block(int NBLOCK);
int s_unlock_all_blocks(void);
	

//************* WRITE / READ *****************

int s_program32_flash_unbuffered(uint32_t baddr, uint32_t* array, int nwords);

int s_read_flash (uint32_t baddr, void* array, int nbytes);

int s_get_blockdata (uint16_t bnum, void** pdata);
int s_put_blockdata (uint16_t bnum);

#define B_PUT_WHOLE_BLOCK (-1)

#endif
