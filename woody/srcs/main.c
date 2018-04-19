/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/15 08:59:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"

#include "ft_printf.h"
#include "ft_fprintf.h"
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

static int				ft_fatal(char *str, t_env *e)
{
	ft_fprintf(stderr, "%s: ", e->progname);
	if (!str)
		perror(str);
	else
		ft_fprintf(stderr, "%s\n", str);
	if (e->fd > 0)
		close(e->fd);
	if (e->file != NULL)
		munmap(e->file, e->file_size);
	exit(1);
}

void print_hex(u_char *file, size_t size, size_t endian)
{
	for (size_t i = 0, j = 0; i < size; i += 4) {
		if (i % 16 == 0)
			ft_printf("%p ", file + i);
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
		if ((i + 4) >= size && j < i) {
			ft_printf("%17s", " ");
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

int				main(int ac, char **av)
{
	t_env		e;
	Elf64_Ehdr	*file_header;
	Elf64_Phdr	*program_header_table;
	Elf64_Shdr	*section_header_table;
	char		*string_table;

	if (ac == 1) {
		ft_fprintf(stderr, "usage: %s [program]\n", av[0]);
		return (1);
	}
	ft_memset(&e, 0, sizeof(e));
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname == NULL) ? av[0] : e.progname + 1;
	if ((e.fd = open(av[1], O_RDONLY)) == -1)
		ft_fatal(NULL, &e);
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		ft_fatal(NULL, &e);
	e.file = mmap(NULL, e.file_size, PROT_READ, MAP_PRIVATE, e.fd, 0);
	if (e.file == MAP_FAILED)
		ft_fatal(NULL, &e);
	if (close(e.fd) == -1)
		perror("close()");
	e.fd = 0;

	file_header = (Elf64_Ehdr *)e.file;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type.", &e);
	if (file_header->e_ident[EI_CLASS] != ELFCLASS64)
		ft_fatal("Unsupported ELF file class.", &e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order.", &e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", &e);
	if (file_header->e_type != ET_EXEC)
		ft_fatal("Unsupported ELF file type.", &e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", &e);

	program_header_table = (Elf64_Phdr *)(e.file + file_header->e_phoff);

	section_header_table = (Elf64_Shdr *)(e.file + file_header->e_shoff);

	string_table = (file_header->e_shstrndx == SHN_UNDEF) ? NULL :
		(char *)file_header + (section_header_table + file_header->e_shstrndx)->sh_offset;
	
	ft_printf(CO2);
	ft_printf("file info:\n");
	ft_printf(CO3);
	ft_printf("addr\t\t size\t class\t encoding\t version OS/ABI\t\t ABIv\t padding\n");
	ft_printf(DEF);
	ft_printf("%p\t %#x\t %s\t %s\t %d\t %s\t %d\t %d\n", e.file, e.file_size,
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
	ft_printf("type\t\t flags\t offset\t vaddr\t\t paddr\t\t filesz\t memsz\t align\n");
	ft_printf(DEF);
	for (size_t i = 0; i < file_header->e_phnum; i++) {
		Elf64_Phdr	*phdr = program_header_table + i;
		ft_printf("%.8x\t %#x\t %#x\t %.7p\t %.7p\t %#x\t %#x\t %#x\n",
				  phdr->p_type, phdr->p_flags, phdr->p_offset, phdr->p_vaddr,
				  phdr->p_paddr, phdr->p_filesz, phdr->p_memsz, phdr->p_align);
		ft_printf(DEF);
//		print_hex((u_char *)phdr, file_header->e_phentsize, file_header->e_ident[EI_DATA]);
	}

	ft_printf(CO2);
	ft_printf("\nsection header:\n");
	ft_printf(CO3);
	ft_printf("name\ntype\t\t flags\t addr\t\t offset\t size\t link\t info\t align\t entsize\n");
	ft_printf(DEF);
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*shdr = section_header_table + i;
		char		*name = (string_table) ? string_table + shdr->sh_name : NULL; 

		ft_printf("%-17s\n %#.8x\t %#x\t %.8p\t %#x\t %#x\t %#x\t %#x\t %#x\t %#x\t\n",
				  name,
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

	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}
