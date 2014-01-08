/**
 * @file
 * @brief
 *
 * @date 16.10.2012
 * @author Anton Bulychev
 */

#include <lib/libelf.h>
#include <string.h>
#include <stdlib.h>

static inline void elf_reverse_sym(Elf32_Sym *sym) {
	REVERSE_L(sym->st_name);
	REVERSE_L(sym->st_value);
	REVERSE_L(sym->st_size);
	REVERSE_S(sym->st_shndx);
}

int elf_read_symbol_table(FILE *fd, Elf32_Obj *obj) {
	size_t offset, size, count;
	Elf32_Ehdr *header = obj->header;
	Elf32_Shdr *sh_table = obj->sh_table;

	if (!header->e_shoff) {
		return -1;
	}

	for (int i = 0; i < header->e_shnum; i++) {
		if (sh_table[i].sh_type == SHT_SYMTAB) {
			offset = sh_table[i].sh_offset;
			size = sh_table[i].sh_size;
			obj->sym_table = malloc(size);

			fseek(fd, offset, 0);

			if (fread(obj->sym_table, size, 1, fd)) {
				count = sh_table[i].sh_size / sizeof(Elf32_Sym);

				if (obj->need_reverse) {
					for (int i = 0; i < count; i++) {
						elf_reverse_sym(obj->sym_table + i);
					}
				}

				return count;
			}

			/* failed reading */
			return -1;
		}
	}

	return -1;
}