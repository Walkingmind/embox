/**
 * @file
 * @brief ELF (Executable and Linkable Format) parser.
 *
 * @date 27.04.10
 * @author Aleksandr Kirov
 */

#ifndef LIB_ELF_H_
#define LIB_ELF_H_

#include <hal/arch.h>

#include <lib/elf_consts.h>
#include <lib/elf_types.h>

extern int elf_read_header(int fd, Elf32_Ehdr *header);
extern int elf_read_ph_table(int fd, Elf32_Ehdr *header, Elf32_Phdr *ph_table);
extern int elf_read_segment(int fd, Elf32_Phdr *ph, void *addr);
extern int elf_read_interp(int fd, Elf32_Phdr *ph, char *interp);

#endif /* LIB_ELF_H_ */
