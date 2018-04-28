/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/28 17:07:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_fprintf.h"
#include "libft.h"
#include "main.h"

extern uint32_t woody_size;
extern uint32_t woody_offset;
void			woody_func(void);

void			write_to_file(t_env *e);
void			write_woody(t_env *e);

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

	write_to_file(&e);
	
	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}

void			write_woody(t_env *e)
{
	int			woody;
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*elf_program;
	Elf64_Shdr	*elf_section;
	Elf64_Phdr	*pt_load;
	Elf64_Xword	align;
	Elf64_Shdr	*section;
	Elf64_Addr	vaddr;
	Elf64_Addr	old_entry;

	woody = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (woody == -1)
		ft_fatal(NULL, e);
	elf_header = (Elf64_Ehdr *)e->file;
	elf_program = (Elf64_Phdr *)(e->file + elf_header->e_phoff);
	elf_section = (Elf64_Shdr *)(e->file + elf_header->e_shoff);

	pt_load = NULL;
	for (size_t i = 0; i < elf_header->e_phnum; i++) {
		if (elf_program[i].p_type == PT_LOAD) {
				pt_load = &elf_program[i];
				break ;
		}
	}
	align = pt_load->p_memsz - pt_load->p_filesz;

	section = NULL;
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		size_t section_addr = elf_section[i].sh_addr + elf_section[i].sh_size;
		size_t segment_addr = pt_load->p_vaddr + pt_load->p_memsz;
		if (section_addr == segment_addr) {
			section = &elf_section[i];
		}
	}
	vaddr = section->sh_addr + section->sh_size + woody_offset;
	old_entry = elf_header->e_entry;
	elf_header->e_entry = vaddr;
	(void)vaddr;

	pt_load->p_filesz += (woody_size + align);
	pt_load->p_memsz += (woody_size + align);

	char	*ptr = (char *)e->file;
	size_t	size = section->sh_offset + section->sh_size;
	write(woody, ptr, size);
	write(woody, &woody_func, woody_size - 4);
	uint32_t jump = ((pt_load->p_vaddr + pt_load->p_filesz) - old_entry) * -1;
	write(woody, &jump, 4);
	for (size_t i = 0; i < align; i++) {
		write(woody, "\0", 1);
	}
	size = size + woody_size + align;
	ptr = ptr + size;
	write(woody, ptr, e->file_size - size - 1);
	close(woody);
}

void			write_to_file(t_env *e)
{
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*elf_program;
	Elf64_Shdr	*elf_section;
	Elf64_Phdr	*pt_load;
	Elf64_Shdr	*section;
	Elf64_Addr	vaddr;
	Elf64_Addr	old_entry;

	elf_header = (Elf64_Ehdr *)e->file;
	elf_program = (Elf64_Phdr *)(e->file + elf_header->e_phoff);
	elf_section = (Elf64_Shdr *)(e->file + elf_header->e_shoff);

/* 1. Find the highest memory mapped PT_LOAD segment */
	pt_load = NULL;
	for (size_t i = 0; i < elf_header->e_phnum; i++) {
		if (elf_program[i].p_type == PT_LOAD) {
			if (!pt_load || elf_program[i].p_vaddr > pt_load->p_vaddr) {
				pt_load = &elf_program[i];
			}
		}
	}

/* 2. Find the last section of the segment */
	section = NULL;
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		size_t section_addr = elf_section[i].sh_addr + elf_section[i].sh_size;
		size_t segment_addr = pt_load->p_vaddr + pt_load->p_memsz;
		if (section_addr >= segment_addr) {
			section = &elf_section[i];
		}
	}

/* 3. Compute the virtual address of our code */
	vaddr = pt_load->p_vaddr + pt_load->p_memsz;

/* 4. Change the elf header */
	old_entry = elf_header->e_entry;
	elf_header->e_entry = vaddr;
	elf_header->e_shoff += woody_size;

/* 5. Change the program header */
	if ((pt_load->p_flags & PF_X) == 0)
		pt_load->p_flags |= PF_X;
	pt_load->p_memsz += woody_size;
	pt_load->p_filesz = pt_load->p_memsz;

/* Extra: Change the offset of sections higher than our code offset, for debug info only. */
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (elf_section[i].sh_offset >= section->sh_offset &&
			&elf_section[i] != section) {
			elf_section[i].sh_offset += woody_size;
			if (elf_section[i].sh_type == SHT_SYMTAB) {
				elf_section[i].sh_link += 0;
			}
		}
	}

/* 6. Write our new file */
	int			woody;
	char		*ptr;
	size_t		size;
	uint32_t	jump_addr;

	woody = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (woody == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	size = section->sh_offset + section->sh_size;
	write(woody, ptr, size);
	ptr += size;

	write(woody, &woody_func, woody_size - sizeof(jump_addr));
	jump_addr = ((pt_load->p_vaddr + pt_load->p_filesz) - old_entry) * -1;
	write(woody, &jump_addr, sizeof(jump_addr));

	write(woody, ptr, e->file_size - size);
	close(woody);
}

/*
  Ideas for compression:
	- Check the size between each sections offset + section size, see if there is no extra unused bytes.
	  ( > 4 bytes, for example).
	- Check google which section(s) can be removed (debugging, info, etc.)
*/
