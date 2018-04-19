/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:03:42 by root              #+#    #+#             */
/*   Updated: 2018/04/19 23:22:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "main.h"

#define DEF "\e[1;0m"
#define CO1 "\e[1;31m"
#define CO2 "\e[1;32m"
#define CO3 "\e[1;33m"
#define CO4 "\e[1;34m"
#define CO5 "\e[1;35m"
#define CO6 "\e[1;36m"

#define MY_LITTLE_ENDIAN	1
#define MY_BIG_ENDIAN		2

void			print_hex(u_char *file, size_t size, size_t endian);

void			file_info(t_env *e)
{
	Elf64_Ehdr	*file_header;
	Elf64_Phdr	*program_header_table;
	Elf64_Shdr	*section_header_table;
	char		*string_table;

	file_header = (Elf64_Ehdr *)e->file;
	program_header_table = (Elf64_Phdr *)(e->file + file_header->e_phoff);

	section_header_table = (Elf64_Shdr *)(e->file + file_header->e_shoff);

	string_table = (file_header->e_shstrndx == SHN_UNDEF) ? NULL :
		(char *)file_header + (section_header_table + file_header->e_shstrndx)->sh_offset;
	
	ft_printf(CO2);
	ft_printf("file info:\n");
	ft_printf(CO3);
	ft_printf("addr\t\t size\t class\t encoding\t version OS/ABI\t\t ABIv\t padding\n");
	ft_printf(DEF);
	ft_printf("%p\t %#x\t %s\t %s\t %d\t %s\t %d\t %d\n", e->file, e->file_size,
			  (file_header->e_ident[EI_CLASS] == 1) ? "32-bit" : "64-bit",
			  (file_header->e_ident[EI_DATA] == 1) ? "little-endian" : "big-endian",
			  file_header->e_ident[EI_VERSION],
			  (file_header->e_ident[EI_OSABI] == 0) ? "System V" : (file_header->e_ident[EI_OSABI] == 1) ? "HP-UX" : "Standalone",
			  file_header->e_ident[EI_ABIVERSION], file_header->e_ident[EI_PAD]);

	ft_printf(CO2);
	ft_printf("\nfile header:\n");
	ft_printf(CO3);
	ft_printf("entry\t\t phoff\t shoff\t ehsize\t phentsize\t phnum\t shentsize\t shnum\t shstrndx\n");
	ft_printf(DEF);
	ft_printf("%p\t %#x\t %#x\t %#x\t %#x\t\t %#d\t %#x\t\t %#d\t %#x\n",
			  file_header->e_entry, file_header->e_phoff,
			  file_header->e_shoff, file_header->e_ehsize, file_header->e_phentsize,
			  file_header->e_phnum, file_header->e_shentsize, file_header->e_shnum,
			  file_header->e_shstrndx);
	ft_printf(DEF);
//	print_hex((u_char *)file_header, file_header->e_ehsize, file_header->e_ident[EI_DATA]);

	ft_printf(CO2);
	ft_printf("\nprogram header:\n");
	ft_printf(CO3);
	ft_printf("type\t type\t\t flags\t offset\t vaddr\t\t paddr\t\t filesz\t memsz\t align\n");
	ft_printf(DEF);
	char			*program_types[] = { "NULL", "LOAD", "DYNAMIC", "INTERP", "NOTE",
										 "SHLIB", "PHDR"};
	for (size_t i = 0; i < file_header->e_phnum; i++) {
		Elf64_Phdr	*phdr = program_header_table + i;
		char		*type = (phdr->p_type <= 7) ? program_types[phdr->p_type] :
			(phdr->p_type == 0x60000000) ? "LOOS" :
			(phdr->p_type == 0x60000000) ? "HIOS" :
			(phdr->p_type == 0x60000000) ? "LOPROC" :
			(phdr->p_type == 0x60000000) ? "HIPROC" : NULL;

		ft_printf("%-7s\t %.8x\t %#x\t %#x\t %.7p\t %.7p\t %#x\t %#x\t %#x\n",
				  type,
				  phdr->p_type, phdr->p_flags, phdr->p_offset, phdr->p_vaddr,
				  phdr->p_paddr, phdr->p_filesz, phdr->p_memsz, phdr->p_align);
		ft_printf(DEF);
//		print_hex((u_char *)phdr, file_header->e_phentsize, file_header->e_ident[EI_DATA]);
	}

	ft_printf(CO2);
	ft_printf("\nsection header:\n");
	ft_printf(CO3);
	ft_printf("name\t\t\t type\ntype\t\t flags\t addr\t\t offset\t size\t link\t info\t align\t entsize\n");
	ft_printf(DEF);
	char			*section_types[] = { "UNUSED", "PROGBITS", "SYMTAB", "STRTAB", "RELA", "HASH",
								 "DYNAMIC", "NOTE", "NOBITS", "REL", "SHLIB", "DYNSYM"};
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*shdr = section_header_table + i;
		char		*name = (string_table) ? string_table + shdr->sh_name : NULL;
		char		*type = (shdr->sh_type <= 11) ? section_types[shdr->sh_type] :
			(shdr->sh_type == 0x60000000) ? "LOOS" :
			(shdr->sh_type == 0x6fffffff) ? "HIOS" :
			(shdr->sh_type == 0x70000000) ? "LOPROC" :
			(shdr->sh_type == 0x7fffffff) ? "HIPROC" : NULL;

		ft_printf("%-17s\t %s\n%#.8x\t %#x\t %.8p\t %#x\t %#x\t %#x\t %#x\t %#x\t %#x\t\n",
				  name, type,
				  shdr->sh_type, shdr->sh_flags, shdr->sh_addr,
				  shdr->sh_offset, shdr->sh_size, shdr->sh_link, shdr->sh_info,
				  shdr->sh_addralign, shdr->sh_entsize);
//		print_hex((u_char *)shdr, file_header->e_shentsize, file_header->e_ident[EI_DATA]);
	}

	/*ft_printf(CO2);
	ft_printf("\nsymbol header:\n");
	for (size_t i = 1; i < file_header->e_shnum; i++) {
		Elf64_Sym	*symbol = (Elf64_Sym *)(section_header_table + i);
		char		*name = (string_table) ? string_table + symbol->st_name : NULL;

		ft_printf(CO4);
		ft_printf("%s (%#x)\n", name, i);
		ft_printf(CO3);
		ft_printf("value\t size\t\t info\t other\t shndx\t\n");
		ft_printf("%p\t %#.7x\t %d|%d\t %#x\t %#x\n",
				  symbol->st_value, symbol->st_size,
				  symbol->st_info >> 4, symbol->st_info & 0x0F,
				  symbol->st_other & 0x3, symbol->st_shndx);
		ft_printf(DEF);
		print_hex((u_char *)symbol, file_header->e_shentsize, file_header->e_ident[EI_DATA]);
		}*/

	/* Prints STRTAB sections */
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*shdr = section_header_table + i;

//		if (shdr->sh_type == SHT_STRTAB) {
			ft_printf(CO2);
			ft_printf("\n%s\n", (string_table) ? string_table + shdr->sh_name : NULL);
			ft_printf(DEF);
			print_hex((u_char *)file_header + shdr->sh_offset,
					  shdr->sh_size, 2);
//		}
	}

}

void			print_hex(u_char *file, size_t size, size_t endian)
{
	for (size_t i = 0, j = 0; i < size; i += 4) {
		if (i % 16 == 0)
			ft_printf("%p ", file + i);
//		ft_printf(" -%d %d- ", i, j);
		if (endian == MY_LITTLE_ENDIAN) {
			for (int k = 3; k >= 0; k--) {
				ft_printf("%02x", file[i + k]);
			}
		} else {
			for (int k = 0; k < 4; k++) {
				ft_printf("%02x", file[i + k]);
			}
		}
		if ((i + 4) % 8 == 0)
			ft_printf(" ");
		if ((i + 4) % 16 == 0) {
			for (; j <= i; j += 4) {
				if (endian == MY_LITTLE_ENDIAN) {
					for (int k = 3; k >= 0; k--) {
						if (ft_isprint(file[j + k]))
							ft_printf("%c", file[j + k]);
						else
							ft_printf(".");
					}
				} else {
					for (int k = 0; k < 4; k++) {
						if (ft_isprint(file[j + k]))
							ft_printf("%c", file[j + k]);
						else
							ft_printf(".");
					}
				}					
			}
			ft_printf("\n");
		}
		if ((i + 4) >= size && j <= i) {
//			ft_printf("-%d %d-", i, j);
			int len = 26 - (i - j) * 2 - ((i - j) ? 1 : 0);
			write(1, "                                               ", len);
//			ft_printf("%17s", " ");
			for (; j <= i; j += 4) {
				if (endian == MY_LITTLE_ENDIAN) {
					for (int k = 3; k >= 0; k--) {
						if (ft_isprint(file[j + k]))
							ft_printf("%c", file[j + k]);
						else
							ft_printf(".");
					}
				} else {
					for (int k = 0; k < 4; k++) {
						if (ft_isprint(file[j + k]))
							ft_printf("%c", file[j + k]);
						else
							ft_printf(".");
					}
				}					
			}
			ft_printf("\n");
		}
	}
}
