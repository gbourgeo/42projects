/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/12 08:12:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"

#include "ft_printf.h"
#include "ft_fprintf.h"
#include "libft.h"

#include "main.h"

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

void print_hex(u_char *file, size_t size)
{
	for (size_t i = 0, j = 0; i < size; i++) {
		if (i % 16 == 0)
			ft_printf("%p ", file + i);
		ft_printf("%02x", file[i]);
		if ((i+1) % 8 == 0)
			ft_printf(" ");
		if ((i+1) % 16 == 0) {
			for (; j <= i; j++) {
				if (ft_isprint(file[j]))
					ft_printf("%c", file[j]);
				else
					ft_printf(".");
			}
			ft_printf("\n");
		}
		if (i + 1 == size && j < i) {
			ft_printf("%17s", " ");
			for (; j <= i; j++) {
				if (ft_isprint(file[j]))
					ft_printf("%c", file[j]);
				else
					ft_printf(".");
			}
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}

int				main(int ac, char **av)
{
	t_env		e;
	Elf64_Ehdr	*file_header;
	Elf64_Phdr	*program_header_table;
	Elf64_Shdr	*section_header_table;

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
		ft_fatal("File type not suported. ELF only.", &e);
	if (file_header->e_ident[EI_CLASS] != ELFCLASS64)
		ft_fatal("File architecture not supported. 64 Bits only.", &e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Invalid data encoding.", &e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Invalid file version.", &e);
	if (file_header->e_type != ET_EXEC)
		ft_fatal("File not an executable.", &e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Invalid file version.", &e);

	section_header_table = (Elf64_Shdr *)(e.file + file_header->e_shoff);

	program_header_table = (Elf64_Phdr *)(e.file + file_header->e_phoff);

	ft_printf("file info:\n");
	ft_printf("addr\t\t size\t entry\t\t phoff\t shoff\t ehsize\t phentsize\t phnum\t shentsize\t shnum\t shstrndx\n");
	ft_printf("%p\t %#x\t %p\t %p\t %p\t %#x\t %#x\t\t %d\t %#x\t\t %d\t %d\n\n",
			  file_header, e.file_size, file_header->e_entry, file_header->e_phoff,
			  file_header->e_shoff, file_header->e_ehsize, file_header->e_phentsize,
			  file_header->e_phnum, file_header->e_shentsize, file_header->e_shnum,
			  file_header->e_shstrndx);

	ft_printf("file header:\n");
	print_hex((u_char *)file_header, file_header->e_ehsize);

	ft_printf("program header:\n");
	print_hex((u_char *)program_header_table, file_header->e_phentsize);

	ft_printf("section header:\n");
	for (size_t i = 0; i < file_header->e_shnum; i++) {
		Elf64_Sym	*symbol = (Elf64_Sym *)(section_header_table + i);
		ft_printf("nb\t name\t info\t reserved\t shndx\t value\t size\n");
		ft_printf("%d\t %d\t %#x\t %d\t\t %hd\t %p\t %d\n", i,
				  symbol->st_name, symbol->st_info, symbol->st_other,
				  symbol->st_shndx, symbol->st_value, symbol->st_size);
		print_hex((u_char *)symbol, file_header->e_shentsize);
	}

	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}
