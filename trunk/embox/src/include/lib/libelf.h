/**
 * @file
 * @brief ELF (Executable and Linkable Format) parser.
 *
 * @date 27.04.10
 * @author Aleksandr Kirov
 */

#ifndef LIB_ELF_H_
#define LIB_ELF_H_

#include <lib/elf_types.h>
#include <hal/arch.h>

#if defined(__LITTLE_ENDIAN)
#define REV(rev) \
	((rev) == ELFDATA2MSB)
#elif defined(__BIG_ENDIAN)
#define REV(rev) \
	((rev) == ELFDATA2LSB)
#endif


/**
 * Function reverses order of bytes in received integer with size 4-bytes
 * if reversed value is 2 - according
 * specification and big-low type of bytes order in numbers
 *
 * @param num - integer to reverse
 * @param reversed - integer from specification
 *                 - property talking about data type
 */
#define L_REV(num, rev) \
	(REV(rev) ?                     \
	((((num) & 0x000000ff) << 24)   \
	+ (((num) & 0x0000ff00) << 8)   \
	+ (((num) & 0x00ff0000) >> 8)   \
	+ (((num) & 0xff000000) >> 24)) \
	: (num))

/**
 * Function reverses order of bytes in received integer with size 2-bytes
 * if reversed value is 2 - according
 * specification and big-low type of bytes order in numbers
 *
 * @param num - integer to reverse
 * @param reversed - integer from specification
 *                 - property talking about data type
 */
#define S_REV(num, rev) \
	(REV(rev) ?                \
	((((num) & 0x00ff ) << 8)  \
	+ (((num) & 0xff00) >> 8)) \
	: (num))

/**
 * Read header from fo and put it in header, returns error code
 *
 * @param fd - file descriptor to get information from
			   recomended : fopen(<file_name>,"rb")
 * @param head - head structure in file, describing main elements positions
 *
 * @return the number of items successfully read or error code.
 */
extern int32_t elf_read_header(FILE *fd, Elf32_Ehdr **head);

/**
 * Read table of section's headers
 *
 * @param fd - file descriptor to get information from
 * @param head - head structure in file, describing main elements positions
 * @param sh_table - array where will section's headers be stored
 *
 * @return the number of items successfully read or error code.
 */
extern int32_t elf_read_sections_table(FILE *fd, Elf32_Ehdr *head,
					Elf32_Shdr **sh_table);

/**
 * Read table of program segment's headers
 *
 * @param fd - file descriptor to get information from
 * @param head - head structure in file, describing main elements positions
 * @param st_table - array where will section's headers be stored
 *
 * @return the number of items successfully read or error code.
 */
extern int32_t elf_read_segments_table(FILE *fd, Elf32_Ehdr *head,
					Elf32_Phdr **st_table);

/**
 * Read string table from sections and put it into names,
 * real length - to length
 *
 * @param fd - file descriptor to get information from
 * @param head - head structure in file, describing main elements positions
 * @param section_header_table - array where func take info about sections
 * @param string_table - array where will be stored string
 * @param length - really used bytes in names
 *
 * @return the number of items successfully read or error code.
 * @retval -1 - not found in sections, "length" must be 0
 * @retval -2 - section header's table is empty
 */
extern int32_t elf_read_string_table(FILE *fd, Elf32_Ehdr *head,
			Elf32_Shdr *section_header_table, int8_t **string_table);

/**
 * Read symbol string table from sections and put it into names. Find
 * SHT_STRTAB and read it to array, number of symbols - to length. Symbol
 * string table contains names of symbols
 *
 * @param fd - file descriptor to get information from
 * @param head - head structure in file, describing main elements positions
 * @param section_header_table - array where func take info about sections
 * @param symb_names - array where will be stored string,
 * 		  which are names of symbols - with is return value
 * @param string_table array with names of sections
 * @param ret_length - really used bytes in names
 *
 * @return really used bytes in names or error code.
 * @retval -1 - not found in sections, "length" must be 0
 * @retval -2 - section header's table is empty
 * @retval -3 - empty array with sections name
 */
extern int32_t elf_read_symbol_string_table(FILE *fd, Elf32_Ehdr *head,
		Elf32_Shdr *section_header_table, int8_t *string_table,
		int8_t **symb_names, int32_t *ret_length);

/**
 * return name of string from names_array, starting from index index
 * and till first '/0', put it into name
 *
 * @param names_array - consist of strings(names)
 * @param index - index of substring in array
 * @param name - returns name in this array
 *
 * @return length of name
 * @retval 0 - more then MAX_NAME_LENGTH name - error
 * @retval >0 - real length
 */
extern int32_t read_name(int8_t *names_array, int32_t index, int8_t *name);

/**
 * Find SHT_SYMTAB and write it to array, number of symbols - to count
 *
 * @param fd - file descriptor to get information from
 * @param header - head structure in file, describing main elements positions
 * @param section_header_table - array where func take info about sections
 * @param symbol_table - array, will store structures describing symbols
 * @param count - really used number of structures stored
 *
 * @return the number of items successfully read or error code.
 * @retval -1 - not found in sections, "count" must be 0
 * @retval -2 - section header's table is empty
 */
extern int32_t elf_read_symbol_table(FILE *fd, Elf32_Ehdr *header,
		Elf32_Shdr *section_header_table,
		 Elf32_Sym **symbol_table, int32_t *count);

/**
 * find and read ALL rel structures from file and number of them puts to count
 *
 * @param fd - file descriptor to get information from
 * @param header - head structure in file, describing main elements positions
 * @param section_header_table - array where func take info about sections
 * @param rel_table - array, will store structures describing relocations
 * @param count - really used number of structures stored
 *
 * @return really used number of structures stored or error code.
 * @retval -1 - not found in sections, "count" must be 0
 * @retval -2 - section header's table is empty
 * @retval -3 - must be never returned
 */
extern int32_t elf_read_rel_table(FILE *fd, Elf32_Ehdr *header,
			Elf32_Shdr *section_header_table,
			Elf32_Rel **rel_table, int32_t *count);

/**
 * find and read ALL rela structures from file and number of them puts to count
 *
 * @param fd - file descriptor to get information from
 * @param header - head structure in file, describing main elements positions
 * @param section_header_table - array where func take info about sections
 * @param rela_table - array, will store structures describing relocations
 * @param count - really used number of structures stored
 *
 * @return really used number of structures stored or error code.
 * @retval -1 - not found in sections, "count" must be 0
 * @retval -2 - section header's table is empty
 */
extern int32_t elf_read_rela_table(FILE *fd, Elf32_Ehdr *header,
				Elf32_Shdr *section_header_table,
				Elf32_Rela *rela_table, int32_t *count);

extern int32_t elf_read_segment(FILE *fd, Elf32_Ehdr *head, Elf32_Phdr *EPH, int8_t *dst);

#endif /* LIB_ELF_H_ */
