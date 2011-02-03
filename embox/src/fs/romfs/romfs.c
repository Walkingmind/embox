/**
 * @file
 *
 * @date 29.06.2009
 * @author Anton Bondarev
 * @author Alexander Batyukov
 */
#include <string.h>
#include <fs/rootfs.h>
#include <fs/romfs.h>
#include <fs/fs.h>
#include <drivers/flash_template.h>
#include <drivers/flash_if.h>

typedef struct _FILE_DESC {
	int id;
	unsigned int size_in_bytes;
	unsigned int size_on_disk;
	char name[CONFIG_MAX_LENGTH_FILE_NAME];
	unsigned int mode;
	unsigned int is_busy;
} FILE_DESC;

// TODO this variable is never used
static int file_desc_cnt;

static FILE_INFO flist[MAX_FLASH_DEVS][CONFIG_MAX_FILE_QUANTITY];  //all files table
static uint32_t mlist[MAX_FLASH_DEVS][FLASH_TOTAL_NUMBLOCKS]; //memory table

typedef struct _BLOCK_INFO {
	int flash_dev;
	int block_num;
} BLOCK_INFO;

static void *romfs_fopen(const char *file_name, const char *mode);
static int romfs_fclose(void * file);
static size_t romfs_fread(void *buf, size_t size, size_t count, void *file);
static size_t romfs_fwrite(const void *buf, size_t size, size_t count, void *file);
static int romfs_fseek(void *file, long offset, int whence);

static file_operations_t fop = {
	romfs_fopen,
	romfs_fclose,
	romfs_fread,
	romfs_fwrite,
	romfs_fseek
};

#define FILE_DESC_QUANTITY 0x4
#define FILE_HANDLERS_QUANTITY		  0x4

typedef struct _FILE_HANDLER {
	file_operations_t *fileop;
	FILE_DESC *fdesc;
	int cur_pointer;
	unsigned int mode;
}FILE_HANDLER;

static FILE_DESC fdesc[FILE_DESC_QUANTITY];			 //open files table
static FILE_HANDLER file_handlers [FILE_HANDLERS_QUANTITY]; //files handlers table

//static int file_handler_cnt;

static int file_list_cnt;

static FILE_INFO * file_list_iterator(FILE_INFO *finfo) {
	size_t i;
	if (CONFIG_MAX_FILE_QUANTITY <= file_list_cnt)
		return NULL;
	while (!strcmp(flist[0][file_list_cnt].file_name, "")) {
		if (CONFIG_MAX_FILE_QUANTITY <= file_list_cnt)
			return NULL;
		file_list_cnt++;
	}

	if (CONFIG_MAX_FILE_QUANTITY <= file_list_cnt)
		return NULL;

	strcpy(finfo->file_name, flist[0][file_list_cnt].file_name);
	finfo->mode = FILE_MODE_RO;
	finfo->size_in_bytes = 0;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			finfo->size_in_bytes += flist[i][file_list_cnt].size_in_bytes;
		}
	}
	finfo->size_on_disk = 0;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			finfo->size_on_disk += flist[i][file_list_cnt].size_on_disk;
		}
	}
	file_list_cnt++;
	return finfo;
}

static FS_FILE_ITERATOR get_file_list_iterator(void) {
	file_list_cnt = 0;
	return file_list_iterator;
}

/**
 * find free file identificator in the table of all files
 * @return file id if success, -1 otherwise
 */
static int find_free_file_id(void) {
	size_t  j;
	for (j = 0; j < CONFIG_MAX_FILE_QUANTITY; j++) {
		if (0 == strcmp(flist[0][j].file_name, "")) {
			return j;
		} else {
			printf("%d - %8s\n", j, flist[0][j].file_name);
		}
	}
	return -1;
}

/**
 * find file identificator in the table of all files by name
 * @param file_name name of searched file
 * @return file id if success, -1 otherwise
 */
static int find_file_idx(const char *file_name) {
	size_t  j;
	for (j = 0; j < CONFIG_MAX_FILE_QUANTITY; j++) {
		if (0 == strcmp(flist[0][j].file_name, file_name)) {
			return j;
		}
	}
	return -1;
}

/**
 * find free file descriptor in opened files table
 * @return file descriptor id if success, -1 otherwise
 */
static int find_free_desc(void) {
	size_t i;
	if (FILE_DESC_QUANTITY <= file_desc_cnt)
		return -1;

	for (i = 0; i < FILE_DESC_QUANTITY; i++) {
		if (0 == fdesc[i].is_busy) {
			fdesc[i].id = i;
			fdesc[i].is_busy = 1;
			return i;
		}
	}
	return -1;
}

/**
 * find file descriptor in opened files table by name
 * @param file_name name of searched file
 * @return file descriptor id if success, -1 otherwise
 */
#if 0
static int find_file_desc(const char * file_name) {
	size_t i;
	for (i = 0; i < FILE_DESC_QUANTITY; i++) {
		if ((0 == strncmp(fdesc[i].name, file_name, ARRAY_SIZE(fdesc[i].name)))
		    && (CONFIG_FLASH_FREE_SPACE_ID!= fdesc[i].is_busy)) {
			return i;
		}
	}
	return -1;
}
#endif
/**
 * Get free memory quantity
 * @return quantity of free memory in blocks
 */
static int free_blocks_quantity(void) {
	size_t i, j;
	int quantity = 0, total_numblocks;
	//uint32_t value;^M
	printf("in free_blocks_quantity()\n\n");
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			total_numblocks = flash_devices_table[i].total_numblocks;
			printf("total_numblocks = %d\n\n", total_numblocks);
			for (j = 0; j < total_numblocks; j++) {
				if (mlist[i][j] == CONFIG_FLASH_FREE_SPACE_ID) {
					printf(".");
					quantity++;
				} else {
					printf("|");
				}
			}
			printf("\n\n");
		}
	}
	printf("quantity = %d\n", quantity);
	return quantity;
}

/**
 * find free file's handler in handlers table
 * @return handler id if success, -1 otherwise
 */
static int find_free_handler(void) {
	size_t i;
	if (FILE_HANDLERS_QUANTITY <= file_desc_cnt) {
		return -1;
	}

	for (i = 0; i < FILE_HANDLERS_QUANTITY; i++) {
		if (0 == file_handlers[i].fileop) {
			return i;
		}
	}
	return -1;
}

/**
 * memory table is placed in specified flash param block.
 * function load this table from flash to operative memory
 * @param slot_number describes flash dev which memory table we have to load
 * @return 0 if success
 */
static int load_memtable(int slot_number) {
	int start_address, memtable_block_num, memtable_base_offset, total_numblocks;
	FLASH_READ_FLASH read = flash_devices_table[slot_number].flash_if_read_flash;
	FLASH_GET_BLOCK_ADDRESS get_block_address =
		flash_devices_table[slot_number].flash_if_get_block_address;

	start_address = flash_devices_table[slot_number].start_address;
	memtable_block_num = flash_devices_table[slot_number].param_block_nums[0];
	get_block_address (&flash_devices_table[slot_number], memtable_block_num,
							&memtable_base_offset);
	total_numblocks = flash_devices_table[slot_number].total_numblocks;

	read(&flash_devices_table[slot_number], CONFIG_MAGIC_OFFSET /*+ start_address*/ + memtable_base_offset,
				mlist[slot_number], total_numblocks * sizeof (uint32_t), 0);

	return 0;
}

/**
 * load memory tables from all flash devices
 * @return 0 if success
 */
static int load_memtables(void) {
	size_t i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			load_memtable(i);
		}
	}
	return 0;
}

/**
 * files table is placed in specified flash param block.
 * function load this table from flash to operative memory
 * @param slot_number describes flash dev which files table we have to load
 * @return 0 if success
 */
static int load_filetable(int slot_number) {
	FLASH_READ_FLASH read_flash = flash_devices_table[slot_number].flash_if_read_flash;
	FLASH_GET_BLOCK_ADDRESS get_block_address = flash_devices_table[slot_number].flash_if_get_block_address;

	int start_address = flash_devices_table[slot_number].start_address;
	int filetable_block_num = flash_devices_table[slot_number].param_block_nums[1];
	int filetable_base_offset;
	get_block_address (&flash_devices_table[slot_number], filetable_block_num, &filetable_base_offset);

	printf("load filetable %d, block %d, start address 0x%x, offset 0x%x\n\n", slot_number, filetable_block_num, start_address, filetable_base_offset);
	read_flash(&flash_devices_table[slot_number], CONFIG_MAGIC_OFFSET /*+ start_address */+ filetable_base_offset,
	flist[slot_number], CONFIG_MAX_FILE_QUANTITY * sizeof(FILE_INFO), 0);
	return 0;
}

/**
 * load files tables from all flash devices
 * @return 0 if success
 */
static int load_filetables(void) {
	size_t i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			load_filetable(i);
		}
	}
	return 0;
}

#if 0
static void print_memtable(int slot_number) {
	int i, total_numblocks;
	printf("memtable\n");
	total_numblocks = flash_devices_table[slot_number].total_numblocks;
	printf("i\tmem\n");
	for (i = 0; i < /*0x4*/total_numblocks; i++) {
		printf("%3d\t0x%8x\n", i, mlist[slot_number][i]);
	}
	printf("\n");
}

static void print_memtables(void) {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			print_memtable(i);
		}
	}
}
#endif

static void print_filetable(int slot_number) {
	size_t i;
	printf("filetable\n\n");
	printf("i\tmode\tname\t\tbytes\tdisk\n\n");
	for (i = 0; i < CONFIG_MAX_FILE_QUANTITY; i++) {
		flist[slot_number][i].file_name[0x10] = '\0';
		if (strcmp(flist[slot_number][i].file_name, "")) {
			printf("%3d\t%d\t\"%8s\"\t%d\t%d\n", i,  flist[slot_number][i].mode,
								flist[slot_number][i].file_name, flist[slot_number][i].size_in_bytes,
								flist[slot_number][i].size_on_disk);
		}
	}
	printf("\n");
}

static void print_filetables(void) {
	size_t i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			print_filetable(i);
		}
	}
}

/**
 * update values of flash param block where memory table is placed
 * @param slot_number describes flash dev which mem table we have to rewrite
 * @return 0 if success
 */
static int rewrite_memtable(int slot_number) {
	int memtable_block_num, memtable_base_offset, total_numblocks,
		start_address, i, cur_addr, *ptr;
	FLASH_STATUS fls;

	FLASH_UNLOCK_BLOCK unlock_block = flash_devices_table[slot_number].flash_if_unlock_block;
	FLASH_ERASE_BLOCK erase_block = flash_devices_table[slot_number].flash_if_erase_block;
	FLASH_PROGRAM_FLASH program_flash = flash_devices_table[slot_number].flash_if_program_flash;
	FLASH_LOCK_BLOCK lock_block = flash_devices_table[slot_number].flash_if_lock_block;
	FLASH_GET_BLOCK_ADDRESS get_block_address = flash_devices_table[slot_number].flash_if_get_block_address;

	memtable_block_num = flash_devices_table[slot_number].param_block_nums[0];
	get_block_address (&flash_devices_table[slot_number], memtable_block_num, &memtable_base_offset);

	total_numblocks = flash_devices_table[slot_number].total_numblocks;
	start_address = flash_devices_table[slot_number].start_address;

	fls = unlock_block(&flash_devices_table[slot_number], memtable_block_num, 1);
	fls = erase_block(&flash_devices_table[slot_number], memtable_block_num, 1);
	//fls = program_flash_buffered(start_address + memtable_base_offset, mlist[slot_number],
	//							 total_numblocks * sizeof(uint32_t), 1);
	cur_addr = /*start_address + */memtable_base_offset + CONFIG_MAGIC_OFFSET;
	ptr =  (uint32_t *) mlist[slot_number];
	for (i = 0; i < total_numblocks * sizeof(uint32_t); i++) {//0X4??
		fls = program_flash(&flash_devices_table[slot_number], cur_addr, *ptr , 1);
		cur_addr += sizeof(uint32_t);
		ptr += 1;
	}

	fls = lock_block(&flash_devices_table[slot_number], memtable_block_num, 1);

	return 0;
}

/**
 * update values of all flash param blocks where memory tables are placed
 * @return 0 if success
 */
static int rewrite_memtables(void) {
	size_t i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			rewrite_memtable(i);
		}
	}
	return 0;
}

/**
 * update values of flash param block where files table is placed
 * @param slot_number describes flash dev which file table we have to rewrite
 * @return 0 if success
 */
static int rewrite_filetable(int slot_number) {
	int filetable_block_num, filetable_base_offset, total_numblocks,
		start_address, i, cur_addr, *ptr;
	FLASH_STATUS fls;

	FLASH_UNLOCK_BLOCK unlock_block = flash_devices_table[slot_number].flash_if_unlock_block;
	FLASH_ERASE_BLOCK erase_block = flash_devices_table[slot_number].flash_if_erase_block;
	FLASH_PROGRAM_FLASH program_flash = flash_devices_table[slot_number].flash_if_program_flash;
	FLASH_LOCK_BLOCK lock_block = flash_devices_table[slot_number].flash_if_lock_block;
	FLASH_GET_BLOCK_ADDRESS get_block_address = flash_devices_table[slot_number].flash_if_get_block_address;

	filetable_block_num = flash_devices_table[slot_number].param_block_nums[1];
	get_block_address (&flash_devices_table[slot_number], filetable_block_num, &filetable_base_offset);
	total_numblocks = flash_devices_table[slot_number].total_numblocks;
	start_address = flash_devices_table[slot_number].start_address;

	//test values
//	printf("slot 0x%x, block %d\n\n", slot_number, filetable_block_num);
	fls = unlock_block(&flash_devices_table[slot_number], filetable_block_num, 1);
//	printf("unlock status: 0x%x\n\n", fls);

	fls = erase_block(&flash_devices_table[slot_number], filetable_block_num, 1);
//	printf("erase status:  0x%x\n\n", fls);

	cur_addr =/* start_address +*/ filetable_base_offset + CONFIG_MAGIC_OFFSET;
//	printf("in rewrite_filetable, addr = 0x%x\n\n", cur_addr);
	ptr = (uint32_t *) flist[slot_number];
	for (i = 0; i < CONFIG_MAX_FILE_QUANTITY * sizeof(FILE_INFO) / 4; i++) {
		fls = program_flash(&flash_devices_table[slot_number], cur_addr, *ptr , 1);
//		printf("fls = 0x%x\n\n", fls.SR);
		cur_addr += sizeof(uint32_t);
		ptr += 1;
	}

	fls = lock_block(&flash_devices_table[slot_number], filetable_block_num, 1);
//	printf("lock status: 0x%x\n\n", fls);
	return 0;
}

/**
 *
 * @return
 */
static int rewrite_filetables(void) {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			rewrite_filetable(i);
		}
	}
	return 0;
}

int format_flash(int slot_number) {
	FLASH_STATUS fls;
	FLASH_UNLOCK_BLOCK unlock_block = flash_devices_table[slot_number].flash_if_unlock_block;
	FLASH_ERASE_BLOCK erase_block = flash_devices_table[slot_number].flash_if_erase_block;
	FLASH_LOCK_BLOCK lock_block = flash_devices_table[slot_number].flash_if_lock_block;
	FLASH_GET_BLOCK_ADDRESS get_block_address = flash_devices_table[slot_number].flash_if_get_block_address;
	int total_numblocks = flash_devices_table[slot_number].total_numblocks;
	//int start_address = flash_devices_table[slot_number].start_address;
	int i, j, memtable_block_num, filetable_block_num, config1_block_num, config2_block_num;
	uint32_t memtable_base_offset, filetable_base_offset;
	printf("Formatting flash start ... \n\n");
	for (j = 0; j < CONFIG_MAX_FILE_QUANTITY; j++) {
		strcpy(flist[slot_number][j].file_name, "");
		flist[slot_number][j].mode = 0;
		flist[slot_number][j].size_in_bytes = 0;
		flist[slot_number][j].size_on_disk = 0;
	}

	for (j = 0; j < total_numblocks; j++) {
		mlist[slot_number][j] = -1;
	}

	if (slot_number == 0) {	 //temporary
		for (i = 0; i < 0x4 /*total_numblocks */; i++) {
			printf("block %3d\t", i);
			fls = unlock_block(&flash_devices_table[slot_number], i, 1);
			printf("unlock 0x%8x\t", fls.SR);
			fls = erase_block(&flash_devices_table[slot_number], i, 1);
			printf("erase 0x%8x\t", fls.SR);
			fls = lock_block(&flash_devices_table[slot_number], i, 1);
			printf("lock 0x%8x\n\n", fls.SR);
	   }
	} else {
		for (i = 255; i < 259 /*total_numblocks */; i++) {
			printf("block %3d\t", i);
			fls = unlock_block(&flash_devices_table[slot_number], i, 1);
			printf("unlock 0x%8x\t", fls.SR);
			fls = erase_block(&flash_devices_table[slot_number], i, 1);
			printf("erase 0x%8x\t", fls.SR);
			fls = lock_block(&flash_devices_table[slot_number], i, 1);
			printf("lock 0x%8x\n\n", fls.SR);
		}
	}
	printf("... erase finished\n\n");

	printf("specified areas filling ...\n\n");

	memtable_block_num = flash_devices_table[slot_number].param_block_nums[0];
	filetable_block_num = flash_devices_table[slot_number].param_block_nums[1];
	config1_block_num = flash_devices_table[slot_number].param_block_nums[2];
	config2_block_num = flash_devices_table[slot_number].param_block_nums[3];

	get_block_address (&flash_devices_table[slot_number], memtable_block_num, &memtable_base_offset);
	printf("memtable base offset = 0x%x\n\n", memtable_base_offset);

	get_block_address (&flash_devices_table[slot_number], filetable_block_num, &filetable_base_offset);
	printf("filetable base offset = 0x%x\n\n", filetable_base_offset);

	free_blocks_quantity();
	//init memtable
	printf("... rewriting memtable ...\n\n");
	mlist[slot_number][memtable_block_num] = CONFIG_MEMTABLE_FILE_ID;
	mlist[slot_number][filetable_block_num] = CONFIG_FILETABLE_FILE_ID;
	mlist[slot_number][config1_block_num] = CONFIG_CONF_FILE_ID;
	mlist[slot_number][config2_block_num] = CONFIG_CONF_FILE_ID;

	rewrite_memtable(slot_number);
	free_blocks_quantity();
	//init_filetable
	printf("... rewriting filetable ...\n\n");
	strcpy(flist[slot_number][CONFIG_MEMTABLE_FILE_ID].file_name, "_mtt");
	flist[slot_number][CONFIG_MEMTABLE_FILE_ID].mode = FILE_MODE_RO;
	flist[slot_number][CONFIG_MEMTABLE_FILE_ID].size_in_bytes = total_numblocks * sizeof(uint32_t);
	flist[slot_number][CONFIG_MEMTABLE_FILE_ID].size_on_disk = 1;

	strcpy(flist[slot_number][CONFIG_FILETABLE_FILE_ID].file_name, "_ftt");
	flist[slot_number][CONFIG_FILETABLE_FILE_ID].mode = FILE_MODE_RO;
	flist[slot_number][CONFIG_FILETABLE_FILE_ID].size_in_bytes = CONFIG_MAX_FILE_QUANTITY * sizeof(FILE_INFO);
	flist[slot_number][CONFIG_FILETABLE_FILE_ID].size_on_disk = 1;

	rewrite_filetable(slot_number);

	printf("... successful\n\n");

	return 0;
}

int format_all_flash_devs(void) {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		printf("flash_devices_table[%d].dev = 0x%x\n\n", i, flash_devices_table[i].dev);
		if (-1 != flash_devices_table[i].dev) {
			format_flash(i);
		}
	}
	return 0;
}

static int create_file(void *params);
static int delete_file(const char *file_name);

static file_system_driver_t ramfs_fs_type = {
	.name           = "romfs",
};

/**
 * Initializing of romfs. Recreates existing files.
 * @return 0 if success
 */
static int init(void) {
	size_t i, j, slot_number;
	file_desc_cnt = 0;

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		for (j = 0; j < CONFIG_MAX_FILE_QUANTITY; j++) {
			strcpy(flist[i][j].file_name, "");
			flist[i][j].mode = 0;
			flist[i][j].size_in_bytes = 0;
			flist[i][j].size_on_disk = 0;
		}
	}

	//print_filetables();
	flash_if_init();

	slot_number = flash_if_device_init(0x00000000, 1);
	printf("flash_if_device_init() finished, slot number %d\n\n", slot_number);

//	slot_number = flash_if_device_init(0x04000000, 2);
//	printf("flash_if_device_init() finished, slot number %d\n\n", slot_number);

//	format_all_flash_devs();

	load_filetables();
	load_memtables();

	free_blocks_quantity();
	print_filetables();

	return register_filesystem(&romfs_fs_type);
}

static void *open_file(const char *file_name, char *mode) {
	FILE_HANDLER *fh;
	FILE_DESC *fd;
	int i, file_idx, desc_num, handler_num, size_on_disc = 0,
		size_in_bytes = 0, file_mode = 0;
	char buf[0x4000];

	if (-1 == (file_idx = find_file_idx(file_name)))
		return NULL;

	if (-1 == (desc_num = find_free_desc()))
		return NULL;

	if (-1 == (handler_num = find_free_handler()))
		return NULL;

	fd = &fdesc[desc_num];

	strcpy(fd->name, file_name);

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			size_on_disc+=flist[i][file_idx].size_on_disk;
			size_in_bytes+=flist[i][file_idx].size_in_bytes;
			file_mode |= flist[i][file_idx].mode;
		}
	}
	fd->size_in_bytes = size_in_bytes;
	fd->size_on_disk = size_on_disc;
	fd->mode = file_mode;
	printf("alloc descriptor %d\n\n", fd->id);
	//fd->id = desc_num;								  //new, to check

	fh = &file_handlers[handler_num];

	fh->cur_pointer = 0;
	fh->fdesc = fd;
	fh->mode = (unsigned int) *mode;
	fh->fileop = &fop;
	fh->fileop->fopen(file_name, mode);

	printf("test start\n\n");
//	//test only
	for (i = 0; i < sizeof(buf); i++) {
		buf[i] = 0x41 + i % (0x5B - 0x41);
	}
	printf("write start\n\n");
	//static size_t fwrite (const void *buf, size_t size, size_t count, void *file) {
	printf("%10s\n\n", fh->fdesc->name);
	for (i = 0; i < 3; i++) {
		fh->fileop->write(buf, sizeof(char), 0x4000, fh);
	}
	//
	printf("finish\n\n");
	return fh;
}

static int get_free_block(BLOCK_INFO *block_info) {
	int i, j;
	int total_numblocks;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			total_numblocks = flash_devices_table[i].total_numblocks;
			for (j = 0; j < total_numblocks; j++) {
				if (mlist[i][j] == CONFIG_FLASH_FREE_SPACE_ID) {
					block_info->flash_dev = i;
					block_info->block_num = j;
					return 0;
				}
			}
		}
	}
	return -1;
}

#if 0
static int get_block_with_id(int id, BLOCK_INFO *block_info) {
	int i, j;
	int total_numblocks;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			total_numblocks = flash_devices_table[i].total_numblocks;
			for (j = 0; j < total_numblocks; j++) {
				if (mlist[i][j] == id) {
					block_info->flash_dev = i;
					block_info->block_num = j;
					return 0;
				}
			}
		}
	}
	return -1;
}
#endif

/**
 * Creates file with specified parameters.
 * @param params
 * @return 0 if success, -1 if failed
 */
static int create_file(void *params) {
	ROMFS_CREATE_PARAM *par = (ROMFS_CREATE_PARAM *) params;
	int free_blocks, size, size_in_blocks, file_id, i, last_size;
	BLOCK_INFO block_info;
	printf("in create_file(), params %10s, %d\n", par->name, par->mode);

	//to check available freespace

	free_blocks = free_blocks_quantity();
	size = par->size;
	size_in_blocks = (size + 0x40000 - 1)/ 0x40000;
	if (free_blocks < size_in_blocks) {
		printf("No %d available space", size);
		return -1;
	}

	//find free file id in flist
	if (-1 == (file_id = find_free_file_id())) {
		printf("can't find free file id\n");
		return -1;
	}
	//printf("alloc file_id %d\n", file_id);
	//create new file record (filetable update)
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			//printf("boo! %d\n", i);
			strcpy(flist[i][file_id].file_name , par->name);
			flist[i][file_id].mode = par->mode;
			flist[i][file_id].size_in_bytes = 0;
			flist[i][file_id].size_on_disk = 0;
		}
	}

	//memtable update
	for (i = 0; i < size_in_blocks; i++) {
		if (-1 == get_free_block(&block_info)) {
			printf("error in space allocating, i\n\n");
			return -1;
		}
		last_size = (size < 0x40000) ? size : 0x40000;
		size -= 0x40000;
		mlist[block_info.flash_dev][block_info.block_num] = file_id;
		flist[block_info.flash_dev][file_id].size_in_bytes += last_size;
		flist[block_info.flash_dev][file_id].size_on_disk += 1;
		printf("flash_dev %d, block_num %d\n\n", block_info.flash_dev, block_info.block_num);
	}

	rewrite_filetables();
	rewrite_memtables();

	//print_memtables();
	open_file(par->name, (char *)&par->mode);
	return 0;
}

static int resize_file(void *params) {
	return 0;
}

static int get_file_id_by_name(const char *file_name) {
	int  j;
	for (j = 0; j < CONFIG_MAX_FILE_QUANTITY; j++) {
		if (0 == strncmp(file_name, flist[0][j].file_name, sizeof(file_name))) {
			return j;
		}
	}
	return -1;
}

/**
 * Delete specified file from file system
 * @param file_name
 * @return 0 if success
 */
static int delete_file(const char *file_name) {
	int i, j, file_id, total_numblocks;
	printf("in delete file %10s\n\n", file_name);
	if (-1 == (file_id = get_file_id_by_name(file_name))) {
		return -1;
	}

	printf("%d\n\n", file_id);
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			total_numblocks = flash_devices_table[i].total_numblocks;
			for (j = 0; j < total_numblocks; j++) {
				if (file_id == mlist[i][j]) {
					mlist[i][j] = CONFIG_FLASH_FREE_SPACE_ID;
					printf("bingo %d, %d, %d\n\n", file_id, mlist[i][j], j);
				}
			}
		}
	}

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			strcpy(flist[i][file_id].file_name, "");
			flist[i][file_id].mode = 0;
		}
	}

	rewrite_filetables();
	rewrite_memtables();

	free_blocks_quantity();
	printf("successful\n\n");
	return 0;
}

static int get_capacity(const char *file_name) {
	return 0;
}

static int get_freespace(const char *file_name) {
	return 0;
}

static int get_descriptors_info(void *params) {
	return 0;
}

fsop_desc_t romfsop = {
	init,
	open_file,
	create_file,
	resize_file,
	delete_file,
	get_capacity,
	get_freespace,
	get_descriptors_info,
	get_file_list_iterator
};

static void *romfs_fopen(const char *file_name, const char *mode) {
	TRACE("romfs file %s was opened\n", file_name);
	return NULL;
}

static int romfs_fclose(void * file) {
	FILE_HANDLER *fh = (FILE_HANDLER *) file;
	fh->fileop = NULL;
	fh->fdesc->is_busy = 0;
	TRACE("file %s was closed\n", fh->fdesc->name);
	return 0;
}

static int block_info_array_filling(int nblocks, BLOCK_INFO *array, FILE_HANDLER *fh) {
	int i, j, total_numblocks;
	int count = 0;
	//filling array containing blocks_info
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			total_numblocks = flash_devices_table[i].total_numblocks;
			for (j = 0; j < total_numblocks; j++) {
				if (mlist[i][j] == fh->fdesc->id) {
					array[count].flash_dev = i;
					array[count].block_num = j;
					count++;
				}
			}
		}
	}
	nblocks = count;
	//sort in future for fragmentation
	//
	return 0;
}

static size_t romfs_fread(void *buf, size_t size, size_t count, void *file) {
	FILE_HANDLER *fh = (FILE_HANDLER *) file;
	int i, maxnblocks = 0, nblocks = 0, cur_address, cur_nblock, cur_offset,
		cur_to_read, left_to_read, flash_dev;
	char *cur_ptr;
	BLOCK_INFO file_blocks[/*maxnblocks*/ 518];
	printf("romfs in fread()\n\n");

	if (fh->cur_pointer >= fh->fdesc->size_in_bytes) {
		TRACE("end read\n");
		return 0;
	}

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			maxnblocks += flash_devices_table[i].total_numblocks;
		}
	}
	printf("maxnblocks %d\n\n", maxnblocks);

	block_info_array_filling(nblocks, file_blocks, fh);

	//detect number of start block to read and offset in them
	//
	cur_address = fh->cur_pointer;
	cur_nblock = cur_address / 0x40000;
	cur_offset = cur_address % 0x40000;
	left_to_read = size * count;
	cur_ptr = (char *) buf;

	printf("In fread()\n\n cur_address = 0x%x, cur_nblock = %d, cur_offset = 0x%x\n\n",
			cur_address, cur_nblock, cur_offset);
	//flash_read
	for (i = cur_nblock; i < nblocks; i++) {
		flash_dev = file_blocks[i].flash_dev;
		cur_to_read = (left_to_read > 0x40000 - cur_offset) ?  0x40000 - cur_offset : left_to_read;
		left_to_read -= cur_to_read;
		flash_devices_table[flash_dev].flash_if_read_flash(&flash_devices_table[flash_dev],
															cur_offset, cur_ptr, cur_to_read / 4, 0);
		cur_ptr += cur_to_read;
		cur_offset = 0;
		cur_address += cur_to_read;

		if (left_to_read <= 0) {
			printf("read end\n");
			break;
		}
	}

	fh->cur_pointer += (uint32_t) cur_ptr - (uint32_t) buf;
//	if (NULL == (fh->cur_pointer % 0x10000)) {
//		TRACE("cur = 0x%X\t size = 0x%X\n",fh->cur_pointer,fh->fdesc->size_in_bytes);
//	}
	printf("successful %d\n\n", (uint32_t) cur_ptr - (uint32_t) buf);
	return (uint32_t) cur_ptr - (uint32_t) buf;

}

static size_t romfs_fwrite(const void *buf, size_t size, size_t count, void *file) {
	FILE_HANDLER *fh = (FILE_HANDLER *) file;
	FLASH_STATUS fls;
	FLASH_UNLOCK_BLOCK unlock_block;
	FLASH_ERASE_BLOCK erase_block;
	FLASH_PROGRAM_FLASH program_flash;
	FLASH_LOCK_BLOCK lock_block;
	FLASH_READ_FLASH read_flash;
	FLASH_GET_BLOCK_ADDRESS get_block_address;
	BLOCK_INFO file_blocks[/*maxnblocks*/518]; //domestic processor features
	//BLOCK_INFO free_block_info;
	int i, maxnblocks = 0, nblocks = 0, cur_address, cur_nblock, cur_offset,
	flash_dev, cur_to_write, left_to_write, address, temp_addr, *ptr, start_address; //bad
	char *cur_ptr;
	char read_buf [0x40000];
	printf("romfs in fwrite(), size = %d, count = %d\t", size, count);

	if (fh->cur_pointer >= fh->fdesc->size_in_bytes) {  //fixed
		TRACE("end write\n\n");
		return 0;
	}

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			maxnblocks += flash_devices_table[i].total_numblocks;
		}
	}
//	printf("maxnblocks %d\n\n", maxnblocks);

	block_info_array_filling(nblocks, file_blocks, fh);
//	printf("nblocks %d\n\n", nblocks);

	cur_address = fh->cur_pointer;
	cur_nblock = cur_address / 0x40000;
	cur_offset = cur_address % 0x40000;
	left_to_write = size * count;
	cur_ptr = (char *) buf;

	while (left_to_write > 0) {
//		printf("left to write %d\n\n", left_to_write);
		cur_to_write = (left_to_write > 0x40000 - cur_offset) ? 0x40000 - cur_offset : left_to_write;
//		printf("cur to write %d\n\n", cur_to_write);
//		if (0 == cur_offset) {		  //to fix
//			//in this wonderful case we will write to the end of file
//			printf("in if\t");
//			get_free_block(&free_block_info);
////			printf("free block info %d, %d\n\n",  free_block_info.flash_dev, free_block_info.block_num);
//			file_blocks[cur_nblock].flash_dev = free_block_info.flash_dev;
//			file_blocks[cur_nblock].block_num = free_block_info.block_num;
////			printf("copied		  %d, %d\n\n", file_blocks[cur_nblock].flash_dev, file_blocks[cur_nblock].block_num);
////			printf("flash_dev = %d\n\n", file_blocks[cur_nblock].flash_dev);
//
//			mlist[free_block_info.flash_dev][free_block_info.block_num] = fh->fdesc->id;
//			flist[free_block_info.flash_dev][fh->fdesc->id].size_on_disk += 1;
//		}
		//fill
		flash_dev = file_blocks[cur_nblock].flash_dev;
//		printf("try to get block address flash_dev = %d = %d\n\n", flash_dev, file_blocks[cur_nblock].flash_dev);
//		printf("dev 0x%x\n\n", flash_devices_table[flash_dev].dev);
		get_block_address = flash_devices_table[flash_dev].flash_if_get_block_address;

		get_block_address(&flash_devices_table[flash_dev], file_blocks[cur_nblock].block_num, &address);
//		printf("cur_nblock = %d, block num = %d, address = 0x%x\n\n", cur_nblock, file_blocks[cur_nblock].block_num, address);

//		printf("try to read_flash\n\n");
		read_flash =  flash_devices_table[flash_dev].flash_if_read_flash;
		fls = read_flash(&flash_devices_table[flash_dev], address, read_buf, sizeof(read_buf), 1);
//		printf("fls = 0x%x\n\n", fls.SR);

		memcpy(read_buf + cur_offset, cur_ptr, cur_to_write);
		printf("0x%x\n", read_buf[1024]);	 //successful there
//		printf("0x%x\n\n", read_buf[1025]);
		cur_ptr += cur_to_write;
		cur_offset = 0;
		cur_address += cur_to_write;

		start_address = flash_devices_table[flash_dev].start_address;
		unlock_block = flash_devices_table[flash_dev].flash_if_unlock_block;
		erase_block = flash_devices_table[flash_dev].flash_if_erase_block;
		program_flash = flash_devices_table[flash_dev].flash_if_program_flash;
		lock_block = flash_devices_table[flash_dev].flash_if_lock_block;

		fls = unlock_block(&flash_devices_table[flash_dev], file_blocks[cur_nblock].block_num, 1);
//		printf("unlock fls = 0x%x\n\n", fls.SR);
		fls = erase_block(&flash_devices_table[flash_dev], file_blocks[cur_nblock].block_num, 1);
//		printf("erase fls = 0x%x\n\n", fls.SR);
		printf("10 ");
		temp_addr = /*start_address + */address;
		ptr = (uint32_t *) read_buf;
		for (i = 0; i < 0x40000 / sizeof(uint32_t); i++) { //to fix
			fls = program_flash(&flash_devices_table[flash_dev], temp_addr, *ptr , 1);
//			printf("program fls = 0x%x\n\n", fls.SR);
			temp_addr += sizeof(uint32_t);
			ptr += 1;
		}
		printf("11 ");
		fls = lock_block(&flash_devices_table[flash_dev], file_blocks[cur_nblock].block_num, 1);
//		printf("lock fls = 0x%x\n\n", fls.SR);
		flist[flash_dev][fh->fdesc->id].size_in_bytes += cur_to_write;
		left_to_write -= cur_to_write;
	}

	fh->cur_pointer += (uint32_t) cur_ptr - (uint32_t) buf;

	printf("successful %d\n\n", (uint32_t) cur_ptr - (uint32_t) buf);
	return (uint32_t) cur_ptr - (uint32_t) buf;
}

static int romfs_fseek(void *file, long offset, int whence) {
	//FILE_HANDLER *fh = (FILE_HANDLER *) file;
	return -2;
}

//TODO format_part
int format_part(void *file) { //char *file_name ??
	FILE_HANDLER *fh = (FILE_HANDLER *) file;
	int i, file_id, maxnblocks = 0, nblocks = 0, flash_dev, block_num;
	//FLASH_STATUS fls;
	//FLASH_UNLOCK_BLOCK unlock_block;
	//FLASH_ERASE_BLOCK erase_block;
	//FLASH_LOCK_BLOCK lock_block;
	BLOCK_INFO file_blocks[/*maxnblocks*/518];

	printf("in format part %10s\n\n", fh->fdesc->name); //domestic processor features

	if (-1 == (file_id = get_file_id_by_name(fh->fdesc->name))) {
		return -1;
	}

	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (-1 != flash_devices_table[i].dev) {
			maxnblocks += flash_devices_table[i].total_numblocks;
		}
	}
//	printf("maxnblocks %d\n\n", maxnblocks);

	block_info_array_filling(nblocks, file_blocks, fh);
//	printf("nblocks %d\n\n", nblocks);

	for (i = 0; i < nblocks; i++) {
		flash_dev = file_blocks[i].flash_dev;
		block_num = file_blocks[i].block_num;
		flash_devices_table[flash_dev].flash_if_unlock_block(
									  &flash_devices_table[flash_dev], block_num, 0);
		flash_devices_table[flash_dev].flash_if_erase_block(
									  &flash_devices_table[flash_dev], block_num, 0);
		flash_devices_table[flash_dev].flash_if_lock_block(
									  &flash_devices_table[flash_dev], block_num, 0);

	}

	fh->cur_pointer = 0;
	printf("successful\n\n");
	return 0;
}
