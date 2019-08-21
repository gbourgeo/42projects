/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/21 04:18:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "ft_printf.h"
#include "libft.h"

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
void			file_info_32(void *file, int file_size);
void			file_info_64(void *file, int file_size);

int				ft_fatal(char *str)
{
	ft_printf("%s: ", str);
	exit(1);
}

int main(int ac, char **av)
{
	int		fd;
	int		file_size;
	void	*file;

	(void)ac;
	if (!av[1]) {
		ft_printf("arg missing\n");
		return 1;
	}
	if ((fd = open(av[1], O_RDWR)) == -1) {
		ft_printf("error open\n");
		return 1;
	}
	if ((file_size = lseek(fd, 1, SEEK_END)) == -1) {
		ft_printf("cant seek end of file\n");
		return 1;
	}
	file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
		ft_printf("cant map file\n");
		return 1;
	}
	if (close(fd) == -1) {
		perror("close()");
	}

	Elf64_Ehdr	*file_header;
	file_header = (Elf64_Ehdr *)file;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type.");
	if (file_header->e_ident[EI_CLASS] == ELFCLASSNONE)
		ft_fatal("Unsupported ELF file class.");
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order.");
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.");
	if (file_header->e_type != ET_EXEC && file_header->e_type != ET_DYN)
		ft_fatal("Unsupported ELF file type.");
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.");

	void		(*file_info[2])(void *, int) = { file_info_32, file_info_64 };
	file_info[file_header->e_ident[EI_CLASS] - 1](file, file_size);
	return 0;
}

void			file_info_64(void *file, int file_size)
{
	Elf64_Ehdr	*file_header;
	Elf64_Phdr	*program_header_table;
	Elf64_Shdr	*section_header_table;
	char		*string_table;

	file_header = (Elf64_Ehdr *)file;
	program_header_table = (Elf64_Phdr *)(file + file_header->e_phoff);
	section_header_table = (Elf64_Shdr *)(file + file_header->e_shoff);
	string_table = (file_header->e_shstrndx == SHN_UNDEF) ? NULL :
		(char *)file_header + (section_header_table + file_header->e_shstrndx)->sh_offset;

	ft_printf(CO2);
	ft_printf("file info:\n");
	ft_printf(CO3);
	ft_printf("addr\t\t size\t\t class\t encoding\t version OS/ABI\t\t ABIv\t padding\n");
	ft_printf(DEF);
	ft_printf("%p\t %.5p\t %s\t %s\t %d\t %s\t %d\t %d\n", file, file_size,
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
	ft_printf("%.12p\t %#x\t %#x\t %#x\t %#x\t\t %#d\t %#x\t\t %#d\t %#x\n",
			  file_header->e_entry, file_header->e_phoff,
			  file_header->e_shoff, file_header->e_ehsize, file_header->e_phentsize,
			  file_header->e_phnum, file_header->e_shentsize, file_header->e_shnum,
			  file_header->e_shstrndx);

	ft_printf(CO2);
	ft_printf("\nprogram header: (%d entries)\n", file_header->e_phnum);
	ft_printf(CO3);
	ft_printf("type\t\t flags\t offset\t vaddr\t\t paddr\t\t filesz\t memsz\t align\n");
	ft_printf(DEF);
	char			*program_types[] = { "NULL", "LOAD", "DYNAMIC", "INTERP", "NOTE",
										 "SHLIB", "PHDR", "TLS", "NUM", "LOOS", "GNU_EH_FRAME",
										 "GNU_STACK", "GNU_RELRO", "LOSUNW", "SUNWBSS",
										 "SUNWSTACK", "HISUNW", "HIOS", "LOPROC", "HIPROC"};
	size_t			program_types_values[] = { PT_NULL, PT_LOAD, PT_DYNAMIC, PT_INTERP, PT_NOTE,
											   PT_SHLIB, PT_PHDR, PT_TLS, PT_NUM, PT_LOOS,
											   PT_GNU_EH_FRAME, PT_GNU_STACK, PT_GNU_RELRO,
											   PT_LOSUNW, PT_SUNWBSS, PT_SUNWSTACK, PT_HISUNW,
											   PT_HIOS, PT_LOPROC, PT_HIPROC };
											   
	for (size_t i = 0; i < file_header->e_phnum; i++) {
		Elf64_Phdr	*phdr = program_header_table + i;
		char		*type = NULL;
		char		flags[6];

		for (size_t i = 0; i < sizeof(program_types_values); i++) {
			if (phdr->p_type == program_types_values[i]) {
				type = program_types[i];
				break;
			}
		}
		flags[0] = (phdr->p_flags & PF_R) ? 'R' : ' ';
		flags[1] = (phdr->p_flags & PF_W) ? 'W' : ' ';
		flags[2] = (phdr->p_flags & PF_X) ? 'X' : ' ';
		flags[3] = (phdr->p_flags & PF_MASKOS) ? 'O' : ' ';
		flags[4] = (phdr->p_flags & PF_MASKPROC) ? 'P' : ' ';

		ft_printf("%-15s\t %#5s\t %#x\t %.6p\t %.6p\t %#x\t %#x\t %.6p\n",
				  type, flags, phdr->p_offset, phdr->p_vaddr,
				  phdr->p_paddr, phdr->p_filesz, phdr->p_memsz, phdr->p_align);
		ft_printf(DEF);
	}

	//print_hex((u_char *)file, file_size, 2); exit(0);

	ft_printf(CO2);
	ft_printf("\nsection header: (%d entries)\n", file_header->e_shnum);
	ft_printf(CO3);
	ft_printf("name\ntype\t\t flags\t addr\t\t offset\t\t size\t\t link\t info\t align\t entsize\n");
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

		ft_printf("%-17s\n%-12s\t %.1p\t %.8p\t %.5p\t %.5p\t %d\t %#x\t %.1p\t %.2p\n",
				  name, type,
				  shdr->sh_flags, shdr->sh_addr,
				  shdr->sh_offset, shdr->sh_size, shdr->sh_link, shdr->sh_info,
				  shdr->sh_addralign, shdr->sh_entsize);
		/* if (ft_strcmp(name, ".text") == 0) */
		/* 	print_hex((u_char *)file_header + shdr->sh_offset, shdr->sh_size, 1); */
	}
	/* for (size_t i = 0; i < file_header->e_phnum; i++) { */
	/* 	Elf64_Phdr *p = program_header_table + i; */
	/* 	if (p->p_type == PT_LOAD && p->p_vaddr > 0x600000) { */
	/* 		print_hex((u_char *)file_header + p->p_offset, p->p_memsz, 1); */
	/* 	} */
	/* } */


/*	
	ft_printf(CO2);
	ft_printf("\nsymbols table:\n");
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*shdr = section_header_table + i;
		char		*name = (string_table) ? string_table + shdr->sh_name : NULL;

		if (shdr->sh_type == SHT_SYMTAB || shdr->sh_type == SHT_DYNSYM) {
			Elf64_Shdr	*symbol_assoc = section_header_table + shdr->sh_link;
			char		*symbol_table = (char *)file_header + symbol_assoc->sh_offset;
			size_t		symbol_addr = (size_t)file_header + shdr->sh_offset;
			Elf64_Sym	*symbol = (Elf64_Sym *)symbol_addr;

			ft_printf(CO4);
			ft_printf("%s: (%d entries of %#x length)\n", name, shdr->sh_size / shdr->sh_entsize, shdr->sh_entsize);
			ft_printf(CO3);
			ft_printf("bind\t type\t other\t   shndx value\t\t size\t name\n");
			ft_printf(DEF);
			for (size_t j = 0; j < shdr->sh_size / shdr->sh_entsize; j++) {
				char		*bind[] = { "LOCAL", "GLOBAL", "WEAK", "NUM",
										"", "", "", "", "",
										"LOOS", "", "HIOS", "LOPROC", "", "HIPROC" };
				char		*type[] = { "NOTYPE", "OBJECY", "FUNC", "SECTION", "FILE",
										"COMMON", "TLS", "NUM", "", "LOOS", "",
										"HIOS", "LOPROC", "", "HIPROC"};
				char		*visibility[] = { "DEFAULT", "INTERNAL", "HIDDEN", "PROTECTED" };
				char		*sname = symbol_table + symbol->st_name;

				ft_printf("%s\t %-7s %-9s %5d %#.08x\t %#x\t %s\n",
						  bind[ELF64_ST_BIND(symbol->st_info)],
						  type[ELF64_ST_TYPE(symbol->st_info)],
						  visibility[ELF64_ST_VISIBILITY(symbol->st_other)],
						  symbol->st_shndx,
						  symbol->st_value,
						  symbol->st_size,
						  sname);
				symbol_addr += shdr->sh_entsize;
				symbol = (Elf64_Sym *)symbol_addr;
			}
		}
	}

	ft_printf(CO2);
	ft_printf("dynamic section:\n");
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*dynamic_section = section_header_table + i;
		char		*name = string_table + dynamic_section->sh_name;

		if (dynamic_section->sh_type == SHT_DYNAMIC) {
			size_t		dynamic_addr = (size_t)file_header + dynamic_section->sh_offset;
			Elf64_Dyn	*dynamic = (Elf64_Dyn *)dynamic_addr;
			char		*tag[] = { "NULL", "NEEDED", "PLTRELSZ", "PLTGOT", "HASH", "STRTAB",
								   "SYMTAB", "RELA", "RELASZ", "RELAENT", "STRSZ", "SYMENT",
								   "INIT", "FINI", "SONAME", "RPATH", "SYMBOLIC", "REL",
								   "RELSZ", "RELENT", "PLTREL", "DEBUG", "TEXTREL", "JMPREL",
								   "BIND_NOW", "INIT_ARRAY", "FINI_ARRAY", "INIT_ARRAYSZ",
								   "FINI_ARRAYSZ", "RUNPATH", "FLAGS", "ENCODING",
								   "PREINIT_ARRAY", "PREINIT_ARRAYSZ", "NUM", "LOOS", "HIOS",
								   "LOPROC", "HIPROC", "PROCNUM", "VALRNGLO", "GNU_PRELINKED",
								   "GNU_CONFLICTSZ", "GNU_LIBLISTSZ", "CHECKSUM", "PLTPADSZ",
								   "MOVEENT", "MOVESZ", "FEATURE_1", "POSFLAG_1", "SYMINSZ",
								   "SYMINENT", "VALRNGHI", "ADDRRNGLO", "GNU_HASH",
								   "TLSDESC_PLT", "TLSDESC_GOT", "GNU_CONFLICT", "GNU_LIBLIST",
								   "CONFIG", "DEPAUDIT", "AUDIT", "PLTPAD", "MOVETAB",
								   "SYMINFO", "ADDRRNGHI", "VERSYM", "RELACOUNT", "RELCOUNT",
								   "FLAGS_1", "VERDEF", "VERDEFNUM", "VERNEED", "VERNEEDNUM",
								   "AUXILIARY", "FILTER", "" };
			Elf64_Sxword	val[] = { DT_NULL, DT_NEEDED, DT_PLTRELSZ, DT_PLTGOT, DT_HASH,
									  DT_STRTAB, DT_SYMTAB, DT_RELA, DT_RELASZ, DT_RELAENT,
									  DT_STRSZ, DT_SYMENT, DT_INIT, DT_FINI, DT_SONAME,
									  DT_RPATH, DT_SYMBOLIC, DT_REL, DT_RELSZ, DT_RELENT,
									  DT_PLTREL, DT_DEBUG, DT_TEXTREL, DT_JMPREL, DT_BIND_NOW,
									  DT_INIT_ARRAY, DT_FINI_ARRAY, DT_INIT_ARRAYSZ,
									  DT_FINI_ARRAYSZ, DT_RUNPATH, DT_FLAGS, DT_ENCODING,
									  DT_PREINIT_ARRAY, DT_PREINIT_ARRAYSZ, DT_NUM, DT_LOOS,
									  DT_HIOS, DT_LOPROC, DT_HIPROC, DT_PROCNUM, DT_VALRNGLO,
									  DT_GNU_PRELINKED, DT_GNU_CONFLICTSZ, DT_GNU_LIBLISTSZ,
									  DT_CHECKSUM, DT_PLTPADSZ, DT_MOVEENT, DT_MOVESZ,
									  DT_FEATURE_1, DT_POSFLAG_1, DT_SYMINSZ, DT_SYMINENT,
									  DT_VALRNGHI, DT_ADDRRNGLO, DT_GNU_HASH, DT_TLSDESC_PLT,
									  DT_TLSDESC_GOT, DT_GNU_CONFLICT, DT_GNU_LIBLIST,
									  DT_CONFIG, DT_DEPAUDIT, DT_AUDIT, DT_PLTPAD, DT_MOVETAB,
									  DT_SYMINFO, DT_ADDRRNGHI, DT_VERSYM, DT_RELACOUNT,
									  DT_RELCOUNT, DT_FLAGS_1, DT_VERDEF, DT_VERDEFNUM,
									  DT_VERNEED, DT_VERNEEDNUM, DT_AUXILIARY, DT_FILTER };

			ft_printf(CO4);
			ft_printf("%s : (%d entries of %#x length)\n",
					  name,
					  dynamic_section->sh_size / dynamic_section->sh_entsize,
					  dynamic_section->sh_entsize);
			ft_printf(CO3);
			ft_printf("tag\t\t val\t\t ptr\n");
			ft_printf(DEF);
			for (size_t j = 0; j < dynamic_section->sh_size / dynamic_section->sh_entsize; j++) {
				char	*dtag = NULL;
				for (size_t k = 0; k < sizeof(val); k++) {
					if (val[k] == dynamic->d_tag) {
						dtag = tag[k];
						break;
					}
				}
				if (dtag)
					ft_printf("%-16s %#09p\t %09p", dtag, dynamic->d_un.d_val, dynamic->d_un.d_ptr);
				else
					ft_printf("%-16d %#09p\t %09p", dynamic->d_tag, dynamic->d_un.d_val, dynamic->d_un.d_ptr);
				if (dynamic->d_tag == DT_NEEDED) {
					size_t		dyn_addr = (size_t)file_header + dynamic_section->sh_offset;
					Elf64_Dyn	*dyn = (Elf64_Dyn *)dynamic_addr;
					
					for (size_t l = 0; l < dynamic_section->sh_size / dynamic_section->sh_entsize; l++) {
						if (dyn->d_tag == DT_STRTAB)
							break;
						dyn_addr += dynamic_section->sh_entsize;
						dyn = (Elf64_Dyn *)dyn_addr;
					}
					if (dyn->d_tag == DT_STRTAB) {
						for (size_t l = 0; l < file_header->e_shnum; l++) {
							Elf64_Shdr	*ptr = (Elf64_Shdr *)section_header_table + l;
							if (ptr->sh_addr == dyn->d_un.d_ptr) {
								char	*strtab = (char *)file_header + ptr->sh_offset;
								ft_printf(" %s", strtab + dynamic->d_un.d_val);
								break;
							}
						}
					}
				}
				ft_printf("\n");
				dynamic_addr += dynamic_section->sh_entsize;
				dynamic = (Elf64_Dyn *)dynamic_addr;
			}
		}
	}
*/

	/* Prints ALL sections */
/*
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Shdr	*shdr = section_header_table + i;

//		if (ft_strcmp(string_table + shdr->sh_name,DT_.interp") == 0) {
			ft_printf(CO2);
			ft_printf("\n%s\n", (string_table) ? string_table + shdr->sh_name : NULL);
			ft_printf(DEF);
			print_hex((u_char *)file_header + shdr->sh_offset,
					  shdr->sh_size, 2);
//		}
	}
*/
	// print_hex((u_char *)file, file_size, 2);// exit(0);

}

void			file_info_32(void *file, int file_size)
{
	Elf32_Ehdr	*file_header;
	Elf32_Phdr	*program_header_table;
	Elf32_Shdr	*section_header_table;
	char		*string_table;

	file_header = (Elf32_Ehdr *)file;
	program_header_table = (Elf32_Phdr *)(file + file_header->e_phoff);
	section_header_table = (Elf32_Shdr *)(file + file_header->e_shoff);
	string_table = (file_header->e_shstrndx == SHN_UNDEF) ? NULL :
		(char *)file_header + (section_header_table + file_header->e_shstrndx)->sh_offset;

	ft_printf(CO2);
	ft_printf("file info:\n");
	ft_printf(CO3);
	ft_printf("addr\t\t size\t class\t encoding\t version OS/ABI\t\t ABIv\t padding\n");
	ft_printf(DEF);
	ft_printf("%p\t %#x\t %s\t %s\t %d\t %s\t %d\t %d\n", file, file_size,
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
	ft_printf("%.12p\t %#x\t %#x\t %#x\t %#x\t\t %#d\t %#x\t\t %#d\t %#x\n",
			  file_header->e_entry, file_header->e_phoff,
			  file_header->e_shoff, file_header->e_ehsize, file_header->e_phentsize,
			  file_header->e_phnum, file_header->e_shentsize, file_header->e_shnum,
			  file_header->e_shstrndx);

	ft_printf(CO2);
	ft_printf("\nprogram header: (%d entries)\n", file_header->e_phnum);
	ft_printf(CO3);
	ft_printf("type\t\t flags\t offset\t vaddr\t\t paddr\t\t filesz\t memsz\t align\n");
	ft_printf(DEF);
	char			*program_types[] = { "NULL", "LOAD", "DYNAMIC", "INTERP", "NOTE",
										 "SHLIB", "PHDR", "TLS", "NUM", "LOOS", "GNU_EH_FRAME",
										 "GNU_STACK", "GNU_RELRO", "LOSUNW", "SUNWBSS",
										 "SUNWSTACK", "HISUNW", "HIOS", "LOPROC", "HIPROC"};
	size_t			program_types_values[] = { PT_NULL, PT_LOAD, PT_DYNAMIC, PT_INTERP, PT_NOTE,
											   PT_SHLIB, PT_PHDR, PT_TLS, PT_NUM, PT_LOOS,
											   PT_GNU_EH_FRAME, PT_GNU_STACK, PT_GNU_RELRO,
											   PT_LOSUNW, PT_SUNWBSS, PT_SUNWSTACK, PT_HISUNW,
											   PT_HIOS, PT_LOPROC, PT_HIPROC };
											   
	for (size_t i = 0; i < file_header->e_phnum; i++) {
		Elf32_Phdr	*phdr = program_header_table + i;
		char		*type = NULL;
		char		flags[6];

		for (size_t i = 0; i < sizeof(program_types_values); i++) {
			if (phdr->p_type == program_types_values[i]) {
				type = program_types[i];
				break;
			}
		}
		flags[0] = (phdr->p_flags & PF_R) ? 'R' : ' ';
		flags[1] = (phdr->p_flags & PF_W) ? 'W' : ' ';
		flags[2] = (phdr->p_flags & PF_X) ? 'X' : ' ';
		flags[3] = (phdr->p_flags & PF_MASKOS) ? 'O' : ' ';
		flags[4] = (phdr->p_flags & PF_MASKPROC) ? 'P' : ' ';

		ft_printf("%-15s\t %#-5s\t %#x\t %.7p\t %.7p\t %#x\t %#x\t %#x\n",
				  type, flags, phdr->p_offset, phdr->p_vaddr,
				  phdr->p_paddr, phdr->p_filesz, phdr->p_memsz, phdr->p_align);
		ft_printf(DEF);
	}

//	print_hex((u_char *)file, file_size, 2); exit(0);

	ft_printf(CO2);
	ft_printf("\nsection header: (%d entries)\n", file_header->e_shnum);
	ft_printf(CO3);
	ft_printf("name\ntype\t\t flags\t addr\t\t offset\t size\t link\t info\t align\t entsize\n");
	ft_printf(DEF);
	char			*section_types[] = { "UNUSED", "PROGBITS", "SYMTAB", "STRTAB", "RELA", "HASH",
								 "DYNAMIC", "NOTE", "NOBITS", "REL", "SHLIB", "DYNSYM"};
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf32_Shdr	*shdr = section_header_table + i;
		char		*name = (string_table) ? string_table + shdr->sh_name : NULL;
		char		*type = (shdr->sh_type <= 11) ? section_types[shdr->sh_type] :
			(shdr->sh_type == 0x60000000) ? "LOOS" :
			(shdr->sh_type == 0x6fffffff) ? "HIOS" :
			(shdr->sh_type == 0x70000000) ? "LOPROC" :
			(shdr->sh_type == 0x7fffffff) ? "HIPROC" : NULL;

		ft_printf("%-17s\n%-12s\t %#x\t %#.8x\t %#x\t %#x\t %d\t %#x\t %#x\t %#x\n",
				  name, type,
				  shdr->sh_flags, shdr->sh_addr,
				  shdr->sh_offset, shdr->sh_size, shdr->sh_link, shdr->sh_info,
				  shdr->sh_addralign, shdr->sh_entsize);
		// if (ft_strcmp(name, ".text") == 0)
		// 	print_hex((u_char *)file_header + shdr->sh_offset, shdr->sh_size, 1);
	}
	// for (size_t i = 0; i < file_header->e_phnum; i++) {
	// 	Elf32_Phdr *p = program_header_table + i;
	// 	if (p->p_type == PT_LOAD && p->p_vaddr > 0x600000) {
	// 		print_hex((u_char *)file_header + p->p_offset, p->p_memsz, 1);
	// 	}
	// }

/*	
	ft_printf(CO2);
	ft_printf("\nsymbols table:\n");
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf32_Shdr	*shdr = section_header_table + i;
		char		*name = (string_table) ? string_table + shdr->sh_name : NULL;

		if (shdr->sh_type == SHT_SYMTAB || shdr->sh_type == SHT_DYNSYM) {
			Elf32_Shdr	*symbol_assoc = section_header_table + shdr->sh_link;
			char		*symbol_table = (char *)file_header + symbol_assoc->sh_offset;
			size_t		symbol_addr = (size_t)file_header + shdr->sh_offset;
			Elf32_Sym	*symbol = (Elf32_Sym *)symbol_addr;

			ft_printf(CO4);
			ft_printf("%s: (%d entries of %#x length)\n", name, shdr->sh_size / shdr->sh_entsize, shdr->sh_entsize);
			ft_printf(CO3);
			ft_printf("bind\t type\t other\t   shndx value\t\t size\t name\n");
			ft_printf(DEF);
			for (size_t j = 0; j < shdr->sh_size / shdr->sh_entsize; j++) {
				char		*bind[] = { "LOCAL", "GLOBAL", "WEAK", "NUM",
										"", "", "", "", "",
										"LOOS", "", "HIOS", "LOPROC", "", "HIPROC" };
				char		*type[] = { "NOTYPE", "OBJECY", "FUNC", "SECTION", "FILE",
										"COMMON", "TLS", "NUM", "", "LOOS", "",
										"HIOS", "LOPROC", "", "HIPROC"};
				char		*visibility[] = { "DEFAULT", "INTERNAL", "HIDDEN", "PROTECTED" };
				char		*sname = symbol_table + symbol->st_name;

				ft_printf("%s\t %-7s %-9s %5d %#.08x\t %#x\t %s\n",
						  bind[ELF32_ST_BIND(symbol->st_info)],
						  type[ELF32_ST_TYPE(symbol->st_info)],
						  visibility[ELF32_ST_VISIBILITY(symbol->st_other)],
						  symbol->st_shndx,
						  symbol->st_value, symbol->st_size,
						  sname);
				symbol_addr += shdr->sh_entsize;
				symbol = (Elf32_Sym *)symbol_addr;
			}
		}
	}

	ft_printf(CO2);
	ft_printf("dynamic section:\n");
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf32_Shdr	*dynamic_section = section_header_table + i;
		char		*name = string_table + dynamic_section->sh_name;

		if (dynamic_section->sh_type == SHT_DYNAMIC) {
			size_t		dynamic_addr = (size_t)file_header + dynamic_section->sh_offset;
			Elf32_Dyn	*dynamic = (Elf32_Dyn *)dynamic_addr;
			char		*tag[] = { "NULL", "NEEDED", "PLTRELSZ", "PLTGOT", "HASH", "STRTAB",
								   "SYMTAB", "RELA", "RELASZ", "RELAENT", "STRSZ", "SYMENT",
								   "INIT", "FINI", "SONAME", "RPATH", "SYMBOLIC", "REL",
								   "RELSZ", "RELENT", "PLTREL", "DEBUG", "TEXTREL", "JMPREL",
								   "BIND_NOW", "INIT_ARRAY", "FINI_ARRAY", "INIT_ARRAYSZ",
								   "FINI_ARRAYSZ", "RUNPATH", "FLAGS", "ENCODING",
								   "PREINIT_ARRAY", "PREINIT_ARRAYSZ", "NUM", "LOOS", "HIOS",
								   "LOPROC", "HIPROC", "PROCNUM", "VALRNGLO", "GNU_PRELINKED",
								   "GNU_CONFLICTSZ", "GNU_LIBLISTSZ", "CHECKSUM", "PLTPADSZ",
								   "MOVEENT", "MOVESZ", "FEATURE_1", "POSFLAG_1", "SYMINSZ",
								   "SYMINENT", "VALRNGHI", "ADDRRNGLO", "GNU_HASH",
								   "TLSDESC_PLT", "TLSDESC_GOT", "GNU_CONFLICT", "GNU_LIBLIST",
								   "CONFIG", "DEPAUDIT", "AUDIT", "PLTPAD", "MOVETAB",
								   "SYMINFO", "ADDRRNGHI", "VERSYM", "RELACOUNT", "RELCOUNT",
								   "FLAGS_1", "VERDEF", "VERDEFNUM", "VERNEED", "VERNEEDNUM",
								   "AUXILIARY", "FILTER", "" };
			Elf32_Sxword	val[] = { DT_NULL, DT_NEEDED, DT_PLTRELSZ, DT_PLTGOT, DT_HASH,
									  DT_STRTAB, DT_SYMTAB, DT_RELA, DT_RELASZ, DT_RELAENT,
									  DT_STRSZ, DT_SYMENT, DT_INIT, DT_FINI, DT_SONAME,
									  DT_RPATH, DT_SYMBOLIC, DT_REL, DT_RELSZ, DT_RELENT,
									  DT_PLTREL, DT_DEBUG, DT_TEXTREL, DT_JMPREL, DT_BIND_NOW,
									  DT_INIT_ARRAY, DT_FINI_ARRAY, DT_INIT_ARRAYSZ,
									  DT_FINI_ARRAYSZ, DT_RUNPATH, DT_FLAGS, DT_ENCODING,
									  DT_PREINIT_ARRAY, DT_PREINIT_ARRAYSZ, DT_NUM, DT_LOOS,
									  DT_HIOS, DT_LOPROC, DT_HIPROC, DT_PROCNUM, DT_VALRNGLO,
									  DT_GNU_PRELINKED, DT_GNU_CONFLICTSZ, DT_GNU_LIBLISTSZ,
									  DT_CHECKSUM, DT_PLTPADSZ, DT_MOVEENT, DT_MOVESZ,
									  DT_FEATURE_1, DT_POSFLAG_1, DT_SYMINSZ, DT_SYMINENT,
									  DT_VALRNGHI, DT_ADDRRNGLO, DT_GNU_HASH, DT_TLSDESC_PLT,
									  DT_TLSDESC_GOT, DT_GNU_CONFLICT, DT_GNU_LIBLIST,
									  DT_CONFIG, DT_DEPAUDIT, DT_AUDIT, DT_PLTPAD, DT_MOVETAB,
									  DT_SYMINFO, DT_ADDRRNGHI, DT_VERSYM, DT_RELACOUNT,
									  DT_RELCOUNT, DT_FLAGS_1, DT_VERDEF, DT_VERDEFNUM,
									  DT_VERNEED, DT_VERNEEDNUM, DT_AUXILIARY, DT_FILTER };

			ft_printf(CO4);
			ft_printf("%s : (%d entries of %#x length)\n",
					  name,
					  dynamic_section->sh_size / dynamic_section->sh_entsize,
					  dynamic_section->sh_entsize);
			ft_printf(CO3);
			ft_printf("tag\t\t val\t\t ptr\n");
			ft_printf(DEF);
			for (size_t j = 0; j < dynamic_section->sh_size / dynamic_section->sh_entsize; j++) {
				char	*dtag = NULL;
				for (size_t k = 0; k < sizeof(val); k++) {
					if (val[k] == dynamic->d_tag) {
						dtag = tag[k];
						break;
					}
				}
				if (dtag)
					ft_printf("%-16s %#09p\t %09p", dtag, dynamic->d_un.d_val, dynamic->d_un.d_ptr);
				else
					ft_printf("%-16d %#09p\t %09p", dynamic->d_tag, dynamic->d_un.d_val, dynamic->d_un.d_ptr);
				if (dynamic->d_tag == DT_NEEDED) {
					size_t		dyn_addr = (size_t)file_header + dynamic_section->sh_offset;
					Elf32_Dyn	*dyn = (Elf32_Dyn *)dynamic_addr;
					
					for (size_t l = 0; l < dynamic_section->sh_size / dynamic_section->sh_entsize; l++) {
						if (dyn->d_tag == DT_STRTAB)
							break;
						dyn_addr += dynamic_section->sh_entsize;
						dyn = (Elf32_Dyn *)dyn_addr;
					}
					if (dyn->d_tag == DT_STRTAB) {
						for (size_t l = 0; l < file_header->e_shnum; l++) {
							Elf32_Shdr	*ptr = (Elf32_Shdr *)section_header_table + l;
							if (ptr->sh_addr == dyn->d_un.d_ptr) {
								char	*strtab = (char *)file_header + ptr->sh_offset;
								ft_printf(" %s", strtab + dynamic->d_un.d_val);
								break;
							}
						}
					}
				}
				ft_printf("\n");
				dynamic_addr += dynamic_section->sh_entsize;
				dynamic = (Elf32_Dyn *)dynamic_addr;
			}
		}
	}
*/
	/* Prints ALL sections */
/*
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf32_Shdr	*shdr = section_header_table + i;

//		if (ft_strcmp(string_table + shdr->sh_name,DT_.interp") == 0) {
			ft_printf(CO2);
			ft_printf("\n%s\n", (string_table) ? string_table + shdr->sh_name : NULL);
			ft_printf(DEF);
			print_hex((u_char *)file_header + shdr->sh_offset,
					  shdr->sh_size, 2);
//		}
	}
*/
}

void			print_hex(u_char *file, size_t size, size_t endian)
{
	size_t i = 0;
	size_t j = 0;
	while (i < size) {
		if (i % 16 == 0)
			ft_printf("%#.012x", i);
		if (endian == MY_LITTLE_ENDIAN) {
			for (size_t k = 0; k < 4; k++) {
				for (size_t l = (i + 4 > size) ? size : i + 4; l > i; l--) {
					if (l == size || (l - i) % 4 == 0)
						ft_printf(" ");
					ft_printf("%02x", file[l - 1]);
				}
				i = (i + 4 > size) ? size : i + 4;
				if (i == size)
					break;
			}
		} else {
			for (size_t k = i + 16; i < size && i < k; i++) {
				if (i % 4 == 0)
					ft_printf(" ");
				ft_printf("%02x", file[i]);
			}
		}
		if (i == size || i % 16 == 0) {
			int space = 1;
			if (i % 16) {
				space += 32 - (i % 16) * 2;
				if ((i % 16) <= 8)
					space += 3;
			}
			write(1,"                                              ", space);

			if (endian == MY_LITTLE_ENDIAN) {
				for (size_t k = 0; k < 4; k++) {
					for (size_t l = (j + 4 >= i) ? i : j + 4; l > j; l--) {
						if (ft_isprint(file[l - 1]))
							ft_printf("%c", file[l - 1]);
						else
							ft_printf(".");
					}
					j += 4;
					if (j > i)
						break ;
				}
			} else {
				while (j < i) {
					if (ft_isprint(file[j]))
						ft_printf("%c", file[j]);
					else
						ft_printf(".");
					j++;
				}
			}
			ft_printf("\n");
		}
	}
}
