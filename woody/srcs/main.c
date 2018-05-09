/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/09 16:10:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include "ft_printf.h"
#include "libft.h"
#include "main.h"

extern uint32_t woody_size;
extern uint32_t woody_keys[4];
void			woody_func(void);
void			woody_encrypt(u_char *data, size_t len, const uint32_t *key);

void			encrypt_text_section(t_env *e);
void			change_file_headers(t_env *e);
void			write_new_file(t_env *e);

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

	encrypt_text_section(&e);
	change_file_headers(&e);
	write_new_file(&e);
	
	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}

void			encrypt_text_section(t_env *e)
{
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*elf_program;
	Elf64_Phdr	*text_program;
	Elf64_Shdr	*elf_section;
	Elf64_Shdr	*text_section;
	char		*string_table;
	char		*section_name;

	elf_header = (Elf64_Ehdr *)e->file;
	if (elf_header->e_shstrndx == SHN_UNDEF)
		ft_fatal("String table not set. Section \".text\" unreachable.", e);

	elf_section = (Elf64_Shdr *)(e->file + elf_header->e_shoff);
	string_table = (char *)(e->file + elf_section[elf_header->e_shstrndx].sh_offset);
	text_section = NULL;
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		section_name = string_table + elf_section[i].sh_name;
		if (ft_strcmp(section_name, ".text") == 0) {
			text_section = &elf_section[i];
			break ;
		}
	}
	if (!text_section)
		ft_fatal("Section \".text\" not found.", e);

	elf_program = (Elf64_Phdr *)(e->file + elf_header->e_phoff);
	text_program = NULL;
	for (size_t i = 0, vaddr = 0, vsize = 0; i < elf_header->e_phnum; i++) {
		if (elf_program[i].p_type == PT_LOAD) {
			vaddr = elf_program[i].p_vaddr;
			vsize = elf_program[i].p_vaddr + elf_program[i].p_memsz;
			if (text_section->sh_addr >= vaddr && text_section->sh_addr < vsize) {
				text_program = &elf_program[i];
				break ;
			}
		}
	}
	if (text_program == NULL)
		ft_fatal("Program header containing section \".text\" not found.", e);

	u_char		*section;
	section = (u_char *)(e->file + text_section->sh_offset);
	woody_encrypt(section, text_section->sh_size, woody_keys);
	(void)section;
	ft_printf("key_value: %lX%lX%lX%lX\n",
			  woody_keys[0], woody_keys[1], woody_keys[2], woody_keys[3]);
	e->text_program = text_program;
	e->text_crypted_size = text_section->sh_size - (text_section->sh_size % 8);

//	woody_decrypt(section, text_section->sh_size, woody_keys);
	/* ft_printf(".text\n"); */
	/* for (size_t i = 0; i < text_section->sh_size; i++) { */
	/* 	if ((i + 1) % 16 == 0) */
	/* 		ft_printf("\n"); */
	/* 	else if ((i + 1) % 8 == 0) */
	/* 		ft_printf(" "); */
	/* 	ft_printf("%02x", section[i]); */
	/* } */
	/* ft_printf("\n"); */

}

void			change_file_headers(t_env *e)
{
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*elf_program;
	Elf64_Shdr	*elf_section;
	Elf64_Addr	vaddr;

	elf_header = (Elf64_Ehdr *)e->file;
	elf_program = (Elf64_Phdr *)(e->file + elf_header->e_phoff);
	elf_section = (Elf64_Shdr *)(e->file + elf_header->e_shoff);

/* 1. Find the highest memory mapped PT_LOAD segment */
	e->woody_program = NULL;
	for (size_t i = 0; i < elf_header->e_phnum; i++) {
		if (elf_program[i].p_type == PT_LOAD) {
			if (!e->woody_program ||
				elf_program[i].p_vaddr > e->woody_program->p_vaddr) {
				e->woody_program = &elf_program[i];
			}
		}
	}

/* 3. Compute the virtual address of our code */
	vaddr = e->woody_program->p_vaddr + e->woody_program->p_memsz;

/* Extra: Change the offset of sections higher than our code offset, for debug. */
	for (size_t i = 0; i < elf_header->e_shnum; i++) {
		if (elf_section[i].sh_offset >= e->woody_program->p_offset + e->woody_program->p_memsz) {
			elf_section[i].sh_offset += woody_size;
		}
	}

/* 4. Change the elf header */
	e->old_entry = elf_header->e_entry;
	elf_header->e_entry = vaddr;
	elf_header->e_shoff += woody_size;

/* 5. Change the program header */
	if ((e->woody_program->p_flags & PF_X) == 0)
		e->woody_program->p_flags |= PF_X;
	e->woody_program->p_memsz += woody_size;
	e->woody_program->p_filesz = e->woody_program->p_memsz;
	if ((e->text_program->p_flags & PF_W) == 0)
		e->text_program->p_flags |= PF_W;
}

void			write_new_file(t_env *e)
{
	char		*ptr;
	size_t		off;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	off = e->woody_program->p_offset + e->woody_program->p_memsz - woody_size;

	write(e->fd, ptr, off);
	write(e->fd, &woody_func, woody_size - 16);
	write(e->fd, &e->old_entry, 8);
	write(e->fd, &e->text_crypted_size, 8);
	write(e->fd, ptr + off, e->file_size - off);
	close(e->fd);
	e->fd = 0;
}

/*
  Ideas for compression:
	- Check the size between each sections offset + section size, see if there is no extra unused bytes.
	  ( > 4 bytes, for example).
	- Check google which section(s) can be removed (debugging, info, etc.)
*/
