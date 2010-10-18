/**
 * @file
 * @brief
 *
 * @date 13.09.10
 * @author Alexander Batyukov
 */

#include <fs/partition.h>
#include <string.h>
#include <stdio.h>
#include <embox/unit.h>

/* temporary */
#include <drivers/flash_if.h>

EMBOX_UNIT_INIT(fs_init);

#define PARTITION_SIMPLE_TYPE	1
#define PARTITION_FREE_TYPE		0
#define PARTITION_END_TYPE		-1
#define PARTITION_LINK_TYPE		-2

#define PARTITION_MAX_USER_FILES		16

PARTITION_DESCRIPTOR fs_second_level_table[PARTITION_MAX_USER_FILES];

PARTITION_DESCRIPTOR *fs_get_head_entity(void) {
	extern PARTITION_DESCRIPTOR _romfs_start;
	return &_romfs_start;
}

PARTITION_DESCRIPTOR *fs_get_last_basic_entity(void) {
	extern PARTITION_DESCRIPTOR _romfs_start, _romfs_end;
	PARTITION_DESCRIPTOR *p_desc;

	for (p_desc = &_romfs_start; p_desc < &_romfs_end; p_desc++) {
		if ((PARTITION_END_TYPE == p_desc->type) || (PARTITION_LINK_TYPE
				== p_desc->type)) {
			return p_desc;
		}
	}
	return NULL;
}

static void fs_fill_entity(PARTITION_DESCRIPTOR *entity, char *name,
		uint32_t flags, uint32_t start_addr, uint32_t size, uint32_t type) {
	entity->name = name;
	entity->flags = flags;
	entity->start_addr = start_addr;
	entity->size = size;
	entity->type = type;
}

bool fs_is_second_table_inited (void) {
	PARTITION_DESCRIPTOR *last_entity;
	last_entity = fs_get_last_basic_entity();
	if (PARTITION_END_TYPE == last_entity->type) {
		return false;
	}
	return true;
}

int fs_init_second_level_table(uint32_t addr) {
	PARTITION_DESCRIPTOR *last_entity;
	PARTITION_DESCRIPTOR temp_entity;
	last_entity = fs_get_last_basic_entity();
	fs_fill_entity(&temp_entity, NULL, 0, addr, 0,PARTITION_LINK_TYPE);
	/* TODO : write(last_entity, &temp_entity, sizeof(PARTITION_DESCRIPTOR)); */
	/* temporary */
	flash_if_write(&flash_devices_table[0],
			(uint32_t) last_entity, &temp_entity, sizeof(PARTITION_DESCRIPTOR));

	return 0;
}

PARTITION_DESCRIPTOR *find_free_desc(void) {
	size_t i;
	for (i = 0; i < PARTITION_MAX_USER_FILES; i++) {
		if (PARTITION_FREE_TYPE == fs_second_level_table[i].type) {
			return &fs_second_level_table[i];
		}
	}
	return NULL;
}

/**
 * check available space
 * edit fs_second_level_table
 */
PARTITION_DESCRIPTOR *fs_add_new_partition(char *name, /* temp */ uint32_t addr,
		uint32_t size, uint32_t type) {
	PARTITION_DESCRIPTOR temp;
	PARTITION_DESCRIPTOR *free_desc;

	fs_fill_entity(&temp, name, 0, addr, size, type);

	if (!fs_is_second_table_inited()) {
		fs_init_second_level_table((uint32_t)&fs_second_level_table);
	}

	free_desc = find_free_desc();
	memcpy(free_desc, &temp, sizeof(PARTITION_DESCRIPTOR));

	return free_desc;
}

int fs_delete_partition(PARTITION_DESCRIPTOR *desc) {
	desc->type = PARTITION_FREE_TYPE;
	/* TODO what about 0 user parts..*/
	return 0;
}

bool fs_is_consistent(void) {
	/* check partitions consistency */
	return true;
}

static int fs_init(void) {
	return 0;
}

/* for debug only */
int fs_print_all_partitions(void) {
	extern PARTITION_DESCRIPTOR _romfs_start, _romfs_end;
	PARTITION_DESCRIPTOR *p_desc;

	printf("\n");
	for (p_desc = &_romfs_start; p_desc < &_romfs_end; p_desc++) {
		switch (p_desc->type) {
		case PARTITION_SIMPLE_TYPE:
			printf("kernel: %s\n", p_desc->name);
			break;
		case PARTITION_LINK_TYPE:
			break;
		case PARTITION_END_TYPE:
			return 0;
		default:
			printf("bad partition type\n");
			break;
		}
	}

	p_desc = (PARTITION_DESCRIPTOR *)p_desc->start_addr;

	while ((PARTITION_END_TYPE != p_desc->type)) {
		printf("user:   %s\n", p_desc->name);
		if (PARTITION_LINK_TYPE != p_desc->type) {
			p_desc++;
		} else {
			p_desc = (PARTITION_DESCRIPTOR *)p_desc->start_addr;
		}
	}
	return 0;
}

/* TODO: not here */

extern uint32_t _text_start;
extern uint32_t _reloc_text_start;
//extern PARTITION_DESCRIPTOR _fs_description_start;
extern uint32_t __mods_start;
extern uint32_t __express_tests_start;
extern uint32_t __modules_handlers_start;
extern uint32_t __init_handlers_start;
extern uint32_t __shell_commands_start;
//extern uint32_t __ipstack_packets_start;
//extern uint32_t __ipstack_sockets_start;
//extern uint32_t __ipstack_protos_start;
extern uint32_t _data_start;
//extern uint32_t _bstart;

DECLARE_PARTITION(0,  ".text", 0, (uint32_t)&_text_start, 0);
DECLARE_PARTITION(1,  ".reloc_text", 0, (uint32_t)&_reloc_text_start, 0);
//DECLARE_PARTITION(2,  ".fs_desc", 0, (uint32_t)&_fs_descriptor_start, 0);
DECLARE_PARTITION(3,  ".mods", 0, (uint32_t)&__mods_start, 0);
DECLARE_PARTITION(4,  ".express_tests", 0, (uint32_t)&__express_tests_start, 0);
DECLARE_PARTITION(5,  ".modules_handlers", 0, (uint32_t)&__modules_handlers_start, 0);
DECLARE_PARTITION(6,  ".init_handlers", 0, (uint32_t)&__init_handlers_start, 0);
DECLARE_PARTITION(7,  ".shell_commands", 0, (uint32_t)&__shell_commands_start, 0);
//DECLARE_PARTITION(8,  ".ipstack_packets", 0, (uint32_t)&__ipstack_packets_start, 0);
//DECLARE_PARTITION(9,  ".ipstack_sockets", 0, (uint32_t)&__ipstack_sockets_start, 0);
//DECLARE_PARTITION(10, ".ipstack_protos", 0, (uint32_t)&__ipstack_protos_start, 0);
DECLARE_PARTITION(11, ".data", 0, (uint32_t)&_data_start, 0);
//DECLARE_PARTITION(12, ".bss", 0, (uint32_t)&_bstart, 0);
DECLARE_END_PARTITION(".end_area", 0);
