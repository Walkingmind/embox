/**
 * @file
 * @brief Reads flash info.
 *
 * @date 14.07.09
 * @author Alexandr Batyukov
 */

#include <embox/cmd.h>
#include <getopt.h>
#include <drivers/flash_template.h>
#include <drivers/flash_if.h>
//#include <fs/mbfs.h>  // mbfs_format_flash
#include <drivers/flash_drv_wrap.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: flashinfo [-h] [-i;f;u;a;e;l;s;r;w]\n");
}

static int showdevinfo(void) {
//	uint32_t mcode;
//	uint32_t deviceid;
//	FLASH_QUERY_DATA query;
//	FLASH_STATUS stat;
//
//	flash_read_device_ID(&mcode, &deviceid); //TO FIX
//
//	TRACE ("\tmanuf.: 0x%04X\t\t0x%04X\n", ((mcode >> 16)& 0xFFFF), (mcode & 0xFFFF));
//	TRACE ("\ttype  : 0x%04X\t\t0x%04X\n", ((deviceid >> 16)& 0xFFFF), (deviceid & 0xFFFF));
//
//	stat = flash_query(&query);    //TO FIX
//	if (stat.Result != StatCompleted) {
//		TRACE("flash_query error!\n");
//		TRACE("status reg: ");
//		PRINTREG32_BIN(stat.SR);
//		return -1;
//	}
//
//
//	TRACE("\n");
//	TRACE("\ttotal size 2*%d Mbyte\n", (1 << (query.DeviceSize - 20)));
//	TRACE("\n");
//	TRACE("\tCFI information\n");
//	TRACE("\n");
////	TRACE("flash query str %s\n", query.QueryStr);
////	TRACE("\tvendor id by CFI                     : 0x%8x\n", query.VendorId);
////	TRACE("\talternative vendor id by CFI         : 0x%8x\n", query.AltVendorId);
////	TRACE("\twidth capabilities 0x%x\n", query.DeviceInterface);
//	TRACE("\tflash size      %d Mbit\n", (1 << (query.DeviceSize - 17)));
//	TRACE("\terase regions   %d\n", query.NumEraseBlocks);
//	TRACE("\tregion 1        %d blocks of %d Kbytes\n", (((query.EraseBlock1Information & 0xFF000000) >> 24) + 1), ((((query.EraseBlock1Information) & 0xFF00) >> 8)/ 4));
//	TRACE("\tregion 2        %d blocks of %d Kbytes\n", (((query.EraseBlock2Information & 0xFF000000) >> 24) + 1), ((((query.EraseBlock2Information) & 0xFF) << 8) / 4));
//	TRACE("\twrite buffer    %d bytes\n", 1 << (query.MaxWriteBufferBytes >> 8));
//
	return 0;
}

static int exec(int argc, char **argv) {
	int opt;
	getopt_init();
	do {
		opt = getopt(argc, argv, "hi");
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		case 'i':
			showdevinfo();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != opt);

	/*
	if (!strcmp (argv[0],"-f")) {
		mbfs_format_flash();
		return 0;
	}

	int bnum;

	if (!strcmp (argv[0],"-u")) {
		if (argc==1)
			s_unlock_all_blocks();
		else {
			sscanf(argv[1], "%d", &bnum);
			s_unlock_block(bnum);
		}
		return 0;
	}

	if (argc<2) {
		print_usage();
		return -1;
	}

	if (!strcmp (argv[0],"-a")) {
		sscanf(argv[1], "%d", &bnum);
		uint32_t addr;
		flash_get_block_address(bnum,&addr);
		TRACE("addr: 0x%08x\n",addr);
		return 0;
	}

	if (!strcmp (argv[0],"-e")) {
		sscanf(argv[1], "%d", &bnum);
		s_erase_block(bnum);
		return 0;
	}

	if (!strcmp (argv[0],"-l")) {
		sscanf(argv[1], "%d", &bnum);
		s_lock_block(bnum);
		return 0;
	}

	if (!strcmp (argv[0],"-s")) {
		uint32_t bstat;
		sscanf(argv[1], "%d", &bnum);
		if (s_block_getstatus(bnum,&bstat)) {
			TRACE("error getting block %d status!\n",bnum);
			return -1;
		}
		TRACE("blkstat: 0b");
		PRINTREG32_BIN(bstat);
		return 0;
	}

	int i, addr,nwords=1;
	uint32_t buf[16];
	if (!strcmp (argv[0],"-r")) {
		if (strncmp(argv[1],"0x",2)) {
			TRACE("ERROR: hex address expected.\n");
			return -1;
		}

		if (argc>2) {
			sscanf(argv[2], "%d", &nwords);
			if (nwords>16) {
				TRACE("max nwords is 16");
				nwords = 16;
			}
		}

		sscanf(argv[1], "0x%x", &addr);
		if (s_read_flash(addr,buf,nwords*4)) {
			TRACE("error reading from %08x address!\n",addr);
			return -1;
		}

		for (i=0;i<nwords;i++) {
			if (i%4 == 0)
				TRACE("\n0x%08x : ", addr+i*4);
			TRACE("0x%08x ", buf[i]);
		}
		return 0;
	}

	if (argc<3) {
		print_usage();
		return -1;
	}

	if (!strncmp (argv[0],"-w",2)) {
		uint32_t val;
		if (strncmp(argv[1],"0x",2)) {
			TRACE("ERROR: hex address expected.\n");
			return -1;
		}

		if (strncmp(argv[2],"0x",2)) {
			TRACE("ERROR: hex value expected.\n");
			return -1;
		}

		sscanf(argv[1], "0x%x", &addr);
		sscanf(argv[2], "0x%x", &val);

		if (argc>3) {
			sscanf(argv[3], "%d", &nwords);
			if (nwords>16) {
				TRACE("max nwords is 16");
				nwords = 16;
			}
		}
		for (i=0;i<nwords;i++)
			buf[i] = val;

		//if (!strncmp (argv[0],"-wb",3))
		//	s_program32_flash_buffered(addr,buf,nwords);
		//else
			s_program32_flash_unbuffered(addr,buf,nwords);

		return 0;
	}*/

	return 0;
}
