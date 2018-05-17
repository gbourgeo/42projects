/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_elf64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:41:56 by root              #+#    #+#             */
/*   Updated: 2018/05/17 20:33:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

extern uint32_t woody64_size;
void			woody64_func(void);
void			woody64_encrypt(u_char *data, size_t len, const uint32_t *key);

static void		encrypt_text_section(t_env *e, t_elf64 *elf);
static void		change_file_headers(t_env *e, t_elf64 *elf);
static void		write_new_file(t_env *e, t_elf64 *elf);

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
		+ sizeof(elf.old_entry)
		+ sizeof(elf.text_crypted_size);
	encrypt_text_section(e, &elf);
	change_file_headers(e, &elf);
	write_new_file(e, &elf);
}

static void		encrypt_text_section(t_env *e, t_elf64 *elf)
{
	char		*string_table;
	char		*section_name;
	u_char		*text;

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
	elf->vaddr = 0;
	for (size_t i = 0, vsize = 0; i < elf->header->e_phnum; i++) {
		if (elf->program[i].p_type == PT_LOAD) {
			elf->vaddr = elf->program[i].p_vaddr;
			vsize = elf->program[i].p_vaddr + elf->program[i].p_memsz;
			if (elf->text_section->sh_addr >= elf->vaddr &&
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

static void		change_file_headers(t_env *e, t_elf64 *elf)
{
/* 1. Find the highest memory mapped PT_LOAD segment */
	elf->woody_program = NULL;
	for (size_t i = 0; i < elf->header->e_phnum; i++) {
		if (elf->program[i].p_type == PT_LOAD) {
			if (!elf->woody_program ||
				elf->program[i].p_vaddr > elf->woody_program->p_vaddr) {
				elf->woody_program = &elf->program[i];
			}
		}
	}
/* 2. Compute the virtual address of our code */
	elf->vaddr = elf->woody_program->p_vaddr + elf->woody_program->p_memsz;
/* Extra: Change the offset of sections higher than our code offset, for debug. */
	for (size_t i = 0; i < elf->header->e_shnum; i++) {
		if (elf->section[i].sh_offset >= elf->woody_program->p_offset + elf->woody_program->p_memsz) {
			elf->section[i].sh_offset += (woody64_size + e->woody_datalen);
		}
	}
/* 3. Change the elf header */
	elf->old_entry = elf->header->e_entry;
	elf->header->e_entry = elf->vaddr;
	elf->header->e_shoff += (woody64_size + e->woody_datalen);
/* 4. Change the program header */
	if ((elf->woody_program->p_flags & PF_X) == 0)
		elf->woody_program->p_flags |= PF_X;
	elf->woody_program->p_memsz += (woody64_size + e->woody_datalen);
	elf->woody_program->p_filesz = elf->woody_program->p_memsz;
	if ((elf->text_program->p_flags & PF_W) == 0)
		elf->text_program->p_flags |= PF_W;
}

static void		write_new_file(t_env *e, t_elf64 *elf)
{
	char		*ptr;
	size_t		off;
	size_t		banner_size;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
/* Get the offset in file to write our code */
	off = elf->woody_program->p_offset + elf->woody_program->p_memsz - woody64_size - e->woody_datalen;
	banner_size = (e->banner && *e->banner) ? ft_strlen(e->banner) + 1 : 0;

	write(e->fd, ptr, off);
	write(e->fd, &woody64_func, woody64_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &elf->old_entry, sizeof(elf->old_entry));
	write(e->fd, &elf->text_crypted_size, sizeof(elf->text_crypted_size));
	write(e->fd, &banner_size, sizeof(banner_size));
	if (e->banner && *e->banner)
	{
		write(e->fd, e->banner, banner_size - 1);
		write(e->fd, "\n", 1);
	}
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
