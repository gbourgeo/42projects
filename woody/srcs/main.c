/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/24 02:54:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include "libft.h"
#include "main.h"
#include <stdio.h>

extern uint32_t woody_size;
void			woody_func(void);

void			file_info(t_env *e);
void			write_to_file(t_env *e);

static int		ft_fatal(char *str, t_env *e)
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

int				main(int ac, char **av)
{
	t_env		e;
	Elf64_Ehdr	*file_header;

	if (ac == 1) {
		ft_fprintf(stderr, "usage: %s [program]\n", av[0]);
		return (1);
	}
	ft_memset(&e, 0, sizeof(e));
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname == NULL) ? av[0] : e.progname + 1;
	if ((e.fd = open(av[1], O_RDWR)) == -1)
		ft_fatal(NULL, &e);
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		ft_fatal(NULL, &e);
	e.file = mmap(NULL, e.file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, e.fd, 0);
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

	file_info(&e);

	write_to_file(&e);
	
	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}

void			write_to_file(t_env *e)
{
	int			woody;
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*elf_program_header;
	Elf64_Shdr	*elf_section_header;
	Elf64_Shdr	new_section;
	Elf64_Addr	vaddr;

	woody = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (woody == -1)
		ft_fatal(NULL, e);
	elf_header = (Elf64_Ehdr *)e->file;
	elf_program_header = (Elf64_Phdr *)(e->file + elf_header->e_phoff);
	elf_section_header = (Elf64_Shdr *)(e->file + elf_header->e_shoff);

	/* Copy the elf header */
	/* 1. Compute the virtual address of our code based on
	   the virtual address of the last PT_LOAD segment +
	   the offset of the segment in the file. */
	vaddr = 0;
	align = 0;
	load_nb = 0;
	for (size_t i = 0; i < elf_header->e_phnum; i++) {
		if (elf_program_header[i].p_type == PT_LOAD) {
			if (vaddr < elf_program_header[i].p_vaddr)
				vaddr = elf_program_header[i].p_vaddr;
		}
	}
	vaddr = vaddr + elf_header->e_shoff;
	printf("new vaddr: %#lx\n", vaddr);
	/* 2. Change the program entry point + sections number */
	elf_header->e_entry = vaddr;
	elf_header->e_shnum += 1;
	write(woody, (char *)elf_header, sizeof(*elf_header));
	/* Copy the program header */
	for (size_t i = 0; i < elf_header->e_phnum; i++) {
		if (elf_program_header[i].p_type == PT_LOAD)
			elf_program_header[i].p_flags = PF_R | PF_W | PF_X;
	}
	write(woody, (char *)elf_program_header, elf_header->e_phentsize * elf_header->e_phnum);
	/* Add a PT_LOAD segment */
	new_segment.p_type = PT_LOAD;
	new_segment.p_flags = PF_R | PF_X;
	new_segment.p_offset = elf_header->e_shoff + sizeof(new_segment);
	new_segment.p_vaddr = vaddr;
	new_segment.p_paddr = vaddr;
	new_segment.p_filesz = woody_size;
	new_segment.p_memsz = woody_size;
	new_segment.p_align = align; // ???
	write(woody, (char *)&new_segment, elf_header->e_phentsize);
	/* Copy all the segment */
	size_t	len = elf_header->e_shoff - (elf_header->e_phoff + elf_header->e_phentsize * elf_header->e_phnum);
	write(woody, (char *)(elf_program_header + elf_header->e_phnum), len);
	/* Add our new segment */
	write(woody, &woody_func, woody_size);
	/* Copy all sections */
	write(woody, (char *)elf_section_header, elf_header->e_shentsize * elf_header->e_shnum);
	/* Add our new section */
	new_section.sh_name = 0;
	new_section.sh_type = SHT_PROGBITS;
	new_section.sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	new_section.sh_addr = vaddr;
	new_section.sh_offset = new_segment.p_offset;
	new_section.sh_size = woody_size;
	new_section.sh_link = SHN_UNDEF;
	new_section.sh_info = 0;
	new_section.sh_addralign = 16;
	new_section.sh_entsize = 0;
	write(woody, (char *)&new_section, sizeof(new_section));

	close(woody);
}
