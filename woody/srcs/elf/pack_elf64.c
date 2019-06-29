/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_elf64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:41:56 by root              #+#    #+#             */
/*   Updated: 2018/06/30 21:46:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "main.h"

extern uint32_t woody64_size;
void			woody64_func(void);
void			woody64_encrypt(u_char *data, size_t len, const uint32_t *key);

static void		encrypt_text_section(t_env *e, t_elf64 *elf);
static void		write_new_file(t_env *e, t_elf64 *elf);
static void		write_in_padding(t_env *e, t_elf64 *elf);
static void		write_add_padding(t_env *e, t_elf64 *elf);

void			pack_elf64(t_env *e)
{
	t_elf64		elf;
	
	ft_memset(&elf, 0, sizeof(elf));
	elf.header = (Elf64_Ehdr *)e->file;
	elf.section = (Elf64_Shdr *)(e->file + elf.header->e_shoff);
	elf.program = (Elf64_Phdr *)(e->file + elf.header->e_phoff);
	e->woody_datalen = ((e->banner && *e->banner) ? ft_strlen(e->banner) + 1 : 0)
		+ sizeof(size_t)
		+ sizeof(e->key)
		+ sizeof(elf.text_entry)
		+ sizeof(elf.text_crypted_size)
		+ sizeof(elf.old_entry);
	encrypt_text_section(e, &elf);
	write_new_file(e, &elf);
}

static void		encrypt_text_section(t_env *e, t_elf64 *elf)
{
	char		*string_table;
	char		*section_name;
	u_char		*text;
	Elf64_Addr	vaddr;

	if (elf->header->e_shstrndx == SHN_UNDEF)
		ft_fatal("String table not set. Section \".text\" unreachable.", e);
/* Find the .text section */
	string_table = (char *)(e->file + elf->section[elf->header->e_shstrndx].sh_offset);
	elf->text_section = NULL;
	for (size_t i = 0; i < elf->header->e_shnum; i++) {
		section_name = string_table + elf->section[i].sh_name;
		if (ft_strcmp(section_name, ".text") == 0) {
			elf->text_section = &elf->section[i];
			break ;
		}
	}
	if (elf->text_section == NULL)
		ft_fatal("Section \".text\" not found.", e);
	elf->text_crypted_size = elf->text_section->sh_size;
/* Find the .text segment */
	elf->text_program = NULL;
	vaddr = 0;
	for (size_t i = 0, vsize = 0; i < elf->header->e_phnum; i++) {
		if (elf->program[i].p_type == PT_LOAD) {
			vaddr = elf->program[i].p_vaddr;
			vsize = elf->program[i].p_vaddr + elf->program[i].p_filesz;
			if (elf->text_section->sh_addr >= vaddr &&
				elf->text_section->sh_addr < vsize) {
				elf->text_program = &elf->program[i];
				break ;
			}
		}
	}
	if (elf->text_program == NULL)
		ft_fatal("Program header containing section \".text\" not found.", e);
/* Encrypt the .text section */
	text = (u_char *)(e->file + elf->text_section->sh_offset);
	woody64_encrypt(text, elf->text_section->sh_size, e->key);
}

static void		write_new_file(t_env *e, t_elf64 *elf)
{
	e->fd = open(OUTPUT_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	e->off = elf->text_program->p_offset + elf->text_program->p_filesz;
	elf->old_entry = (elf->text_program->p_vaddr + elf->text_program->p_memsz - elf->header->e_entry) * (-1);
	elf->text_entry = (elf->text_program->p_vaddr + elf->text_program->p_memsz - elf->text_section->sh_addr) * (-1);
	elf->header->e_entry = elf->text_program->p_vaddr + elf->text_program->p_memsz;

/* Check if we have space to write our code between the 2 PT_LOAD segment */
	Elf64_Phdr *next = elf->text_program + 1;
	if (next->p_offset - (elf->text_program->p_offset + elf->text_program->p_filesz) > woody64_size + e->woody_datalen)
		write_in_padding(e, elf);
	else
		write_add_padding(e, elf);

	close(e->fd);
	e->fd = 0;
}

static void		write_in_padding(t_env *e, t_elf64 *elf)
{
	char		*ptr;
	size_t		banner_size;

	ptr = (char *)e->file;
	banner_size = (e->banner && *e->banner) ? ft_strlen(e->banner) + 1 : 0;

	elf->text_program->p_memsz += (woody64_size + e->woody_datalen);
	elf->text_program->p_filesz += (woody64_size + e->woody_datalen);
	elf->text_program->p_flags = PF_R | PF_W | PF_X;

/* Had this line if you want to disassemble the infection with debuggers */
	// elf->text_section->sh_size += woody64_size;
	write(e->fd, ptr, e->off);
	write(e->fd, &woody64_func, woody64_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &elf->text_entry, sizeof(elf->text_entry));
	write(e->fd, &elf->text_crypted_size, sizeof(elf->text_crypted_size));
	write(e->fd, &elf->old_entry, sizeof(elf->old_entry));
	write(e->fd, &banner_size, sizeof(banner_size));
	if (e->banner && *e->banner)
	{
		write(e->fd, e->banner, banner_size - 1);
		write(e->fd, "\n", 1);
	}
	e->off += (woody64_size + e->woody_datalen);
	write(e->fd, ptr + e->off, e->file_size - e->off - 1);
}

static void		write_add_padding(t_env *e, t_elf64 *elf)
{
	char		*ptr;
	size_t		banner_size;
	size_t		padding;

	ptr = (char *)e->file;
	banner_size	= (e->banner && *e->banner) ? ft_strlen(e->banner) + 1 : 0;
	padding = 0;
	while (padding < woody64_size + e->woody_datalen)
		padding += getpagesize();
	/* Change Program Header offest */
	for (size_t i = 0; i < elf->header->e_phnum; i++) {
		if (elf->program[i].p_offset >= elf->text_program->p_offset + elf->text_program->p_filesz) {
			if (elf->text_program->p_vaddr + elf->text_program->p_memsz >= elf->program[i].p_vaddr)
				ft_fatal("new Segment size too large. Risk of rewriting other Segment(s). Abort.", e);
			elf->program[i].p_offset += padding;
		}
	}
	/* Change Section Header offest */
	for (size_t i = 0; i < elf->header->e_shnum; i++) {
		if (elf->section[i].sh_offset >= elf->text_program->p_offset + elf->text_program->p_filesz) {
			elf->section[i].sh_offset += padding;
		}
	}
	elf->header->e_shoff += padding;
	elf->text_program->p_memsz += (woody64_size + e->woody_datalen);
	elf->text_program->p_filesz += (woody64_size + e->woody_datalen);
	elf->text_program->p_flags = PF_R | PF_W | PF_X;

	write(e->fd, ptr, e->off);
	write(e->fd, &woody64_func, woody64_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &elf->text_entry, sizeof(elf->text_entry));
	write(e->fd, &elf->text_crypted_size, sizeof(elf->text_crypted_size));
	write(e->fd, &elf->old_entry, sizeof(elf->old_entry));
	write(e->fd, &banner_size, sizeof(banner_size));
	if (e->banner && *e->banner)
	{
		write(e->fd, e->banner, banner_size - 1);
		write(e->fd, "\n", 1);
	}
	while (padding-- > woody64_size + e->woody_datalen)
		write(e->fd, "\0", 1);
	write(e->fd, ptr + e->off, e->file_size - e->off - 1);
}
