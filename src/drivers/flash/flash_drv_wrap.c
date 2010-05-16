/**
 * @file
 *
 * @date 28.08.2009
 * @author Roman Evstifeev
 */
#include <flash_template.h>
//#include <flash_intel_p30.h>
#include <common.h>

FLASH_STATUS s_stat;
uint8_t blockdata[FLASH_MAIN_BLOCK_NUMBYTES*2]; // MEGABUFFER of 256 KB "HELLO, MALLOC"

int s_block_getstatus(int NBLOCK, uint32_t* blkstat) {
	s_stat = flash_read_block_status(NBLOCK,(FLASH_FDATA *)blkstat);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_read_block_status %d error!\n", NBLOCK);
		return-1;
	}
	return 0;
}

int s_erase_block(int NBLOCK) {
	s_stat = flash_erase_block(NBLOCK, 1);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_erase_block %d error!\n", NBLOCK);
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_erase_block %d done\n", NBLOCK);
	TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
	return 0;
}


//************* LOCK / UNLOCK *****************

int s_lock_block(int NBLOCK) {
	s_stat = flash_lock_block(NBLOCK, 1);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_lock_block %d error!\n", NBLOCK);
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_lock_block %d done\n", NBLOCK);
	return 0;
}

int s_unlock_block(int NBLOCK) {
	s_stat = flash_unlock_block(NBLOCK, 1);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_unlock_block %d error!\n", NBLOCK);
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_unlock_block %d done\n", NBLOCK);
	return 0;
}

int s_unlock_all_blocks(void) {
	s_stat = flash_unlock_all_blocks(0);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_unlock_all_blocks error!\n");
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_unlock_all_blocks done\n");
	return 0;
}


//************* WRITE / READ *****************
/*
int s_program32_flash_buffered(uint32_t baddr, uint32_t* array, int nwords) {
	
	TRACE("currently unsupported!\n");
	return -1;
	
	s_stat = flash_program_flash_buffered(baddr, array,nwords, 1);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_program_flash_buffered error!\n");
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_program_flash_buffered done\n");
	return 0;
}*/

int s_program32_flash_unbuffered(uint32_t baddr, uint32_t* array, int nwords) {
	int i;
	if (baddr%4) {
		TRACE("address must be aligned on 4 byte boundary!\n");
		return -1;
	}
	for (i=0;i<nwords;i++) {
		s_stat = flash_program_flash(baddr+(i*4), array[i], 1);
		if (i%0x4000==0)
			printf("\n0x%08x",baddr+(i*4));
		if (i%0x400==0)
			printf(".");
		if (s_stat.Result != StatCompleted) {
			TRACE("flash_program_flash error!\n");
			TRACE("status reg: ");
			PRINTREG32_BIN(s_stat.SR);
			return -1;
		}
	}
	//TRACE("flash_program_flash done\n");
	return 0;
}

int s_read_flash (uint32_t baddr, void* array, int nbytes) {
	s_stat = flash_read_flash(baddr, array, nbytes, 1);
	if (s_stat.Result != StatCompleted) {
		TRACE("flash_read_flash error!\n");
		TRACE("status reg: ");
		PRINTREG32_BIN(s_stat.SR);
		return -1;
	}
	//TRACE("flash_read_flash done\n");
	return 0;
}


int b_get_blockdata (uint16_t bnum, void** pdata) {
	uint32_t addr,size;
	flash_get_block_address(bnum,&addr);
	size = flash_get_block_size (bnum);
	*pdata = (void*)blockdata;
	if (s_read_flash(addr, blockdata, size))
		return -1;
	return size;
}



int b_put_blockdata (uint16_t bnum, int nwords) {
	uint32_t addr, wrsize, blkstatus;
	
	if (s_block_getstatus(bnum, &blkstatus)<0)
		return -1;
	
	if (blkstatus&0x10001) {
		TRACE("block is locked, unlock it before write!\n");
		return -1;
	}
	
	flash_get_block_address(bnum,&addr);
	wrsize = flash_get_block_size (bnum);
	
	// B_PUT_WHOLE_BLOCK == (-1)
	wrsize = ((nwords*4>0) && (nwords*4<wrsize)) ? nwords*4 : wrsize;
	
	printf("blockdata addr: %08x ;  wrsz : %d\n",blockdata, wrsize);
	printf ("put: ");
	int i;
	for (i=0;i<80;i++) {
		if(i%16==0)
			printf ("\n");
		printf ("%08x ",*((uint32_t*)(blockdata)+i));
	}
	printf ("\n");
	if (s_erase_block(bnum))
		return -1;
	return s_program32_flash_unbuffered(addr, (uint32_t*)blockdata, wrsize/4);
}
