/* $Id: embox.lds.h 4913 2010-03-11 12:47:15Z eabusalimov $
 *
 * This file is part of Embox.
 */

/**
 * @file
 *
 * @date 10.12.09
 * @author Eldar Abusalimov
 */

#ifndef EMBOX_LDS_H_
#define EMBOX_LDS_H_

#define __SECTION_SYMBOLS(var_prefix, section_name) \
	var_prefix ## _vma =     ADDR(section_name); \
	var_prefix ## _lma = LOADADDR(section_name); \
	var_prefix ## _len =   SIZEOF(section_name); \

#define SECTION_SYMBOLS(section) \
	__SECTION_SYMBOLS(_##section, .##section) \

#define MEMORY_REGION(name) \
	name : ORIGIN = LDS_REGION_BASE_##name, LENGTH = LDS_REGION_SIZE_##name
#define HAS_MEMORY_REGION(name) \
	defined(LDS_REGION_BASE_##name)

#define SECTION_REGION(section) \
	> LDS_SECTION_VMA_##section AT> LDS_SECTION_LMA_##section
#define HAS_SECTION_REGION(section) \
	defined(LDS_SECTION_VMA_##section)

#define DEFAULT_TEXT_ALIGNMENT 16
#define DEFAULT_DATA_ALIGNMENT 32

#define ALIGNMENT() . = ALIGN(DEFAULT_DATA_ALIGNMENT)

#endif /* EMBOX_LDS_H_ */
