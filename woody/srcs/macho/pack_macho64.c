/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_macho64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:43:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/06/06 03:49:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "main.h"

extern uint32_t		woody64_size;
extern uint32_t		woody64_arg_size;
void				woody64_encrypt(u_char *data, size_t len, const uint32_t *key);
void				woody64_func(void);
static void			change_file_headers(t_env *e, t_macho64 *macho);
static void			write_new_file(t_env *e, t_macho64 *macho);

void						pack_macho64(t_env *e)
{
	t_macho64				macho;
	struct load_command		*cmd;
	uint32_t				offset;

	macho.header = (struct mach_header_64 *)e->file;
	offset = sizeof(struct mach_header_64);
	for (size_t i = 0; i < macho.header->ncmds; i++)
	{
		cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_MAIN)
			macho.entry = (struct entry_point_command *)cmd; /* Get the program entry point */
		else if (cmd->cmd == LC_SEGMENT_64)
		{
			macho.segment = (struct segment_command_64 *)cmd;
			if (ft_strcmp(macho.segment->segname, SEG_TEXT) == 0)
			{
				macho.segtext = macho.segment; /* Get the __TEXT segment */
				macho.section = (struct section_64 *)(macho.segment + 1);
				for (size_t j = 0; j < macho.segment->nsects; j++)
				{
					if (ft_strcmp(macho.section[j].sectname, SECT_TEXT) == 0)
						macho.sectext = macho.section; /* Get the __text section */
				}
			}
		}
		offset += cmd->cmdsize;
	}
//	woody64_encrypt((u_char *)(e->file + macho.sectext->offset), macho.sectext->size, e->key);
	change_file_headers(e, &macho);
	write_new_file(e, &macho);
}

void				change_file_headers(t_env *e, t_macho64 *macho)
{
	e->woody_datalen = 0
		+ sizeof(e->key)
		+ sizeof(macho->text_entryoff)
		+ sizeof(macho->text_size)
		+ sizeof(macho->old_entryoff)
		+ sizeof(e->banner_len)
		+ ((e->banner_len > 1) ? e->banner_len : 0);
/* First we store the data we will use later */
	macho->old_entryoff = macho->entry->entryoff;
	macho->text_entryoff = macho->sectext->offset;
	macho->text_size = macho->sectext->size;
	macho->new_entryoff  = macho->section->offset + macho->section->size;
	macho->text_filesize = macho->segtext->filesize;
/* Modify the executable flags (disable ASLR) */
	macho->header->flags &= ~MH_PIE;
/* Modify the entry point */
	macho->entry->entryoff = macho->new_entryoff;
/* Modify the __TEXT segment permissions (make it writable) */
	if (!(macho->segtext->initprot & 0x2))
		macho->segtext->initprot |= 0x2;
/* Modify the __text size */
	macho->sectext->size += (woody64_size + e->woody_datalen);

/* Since its a fuckin NIGHTMARE to add code in the text section, modifying ALL the fuckin offset from TEXT to SYMBOLS etc. (i stopped here),
   we WILL add our code at the end of the file */
	size_t offset = sizeof(struct mach_header_64);
	size_t addrsize = 0;

	macho->section = (struct section_64 *)(macho->segtext + 1);
	while (macho->section[macho->segtext->nsects - 1].addr - macho->segtext->vmaddr + macho->section[macho->segtext->nsects - 1].size +woody64_size + e->woody_datalen > macho->segtext->vmsize + addrsize)
		addrsize += 0x1000;
	for (size_t i = 0; i < macho->header->ncmds; i++)
	{
		struct load_command *cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg = (struct segment_command_64 *)cmd;
			if (seg == macho->segtext)
			{
				seg->vmsize += addrsize;
				seg->filesize += addrsize;
				struct section_64 *sec = (struct section_64 *)(seg + 1);
				for (size_t j = 0; j < macho->segtext->nsects; j++)
				{
					if (&sec[j] > macho->sectext)
					{
						sec[j].addr += (woody64_size + e->woody_datalen);
						sec[j].offset += (woody64_size + e->woody_datalen);
					}
				}
				macho->lastsect_off = sec[seg->nsects - 1].addr - seg->vmaddr + sec[seg->nsects - 1].size;
			}
			else if (seg > macho->segtext)
			{
				seg->vmaddr += addrsize;
				seg->fileoff += addrsize;
				struct section_64 *sec = (struct section_64 *)(seg + 1);
				for (size_t j = 0; j < seg->nsects; j++)
				{
					sec[j].addr += addrsize;
					if (sec[j].offset)
						sec[j].offset += addrsize;
				}
			}
		}
		else if (cmd->cmd == LC_SYMTAB)
		{
			struct symtab_command *sym = (struct symtab_command *)cmd;
			sym->symoff += addrsize;
			sym->stroff += addrsize;
		}
		else if (cmd->cmd == LC_DYSYMTAB)
		{
			struct dysymtab_command *dsym = (struct dysymtab_command *)cmd;
			dsym->tocoff += dsym->tocoff ? addrsize : 0;
			dsym->modtaboff += dsym->modtaboff ? addrsize : 0;
			dsym->extrefsymoff += dsym->extrefsymoff ? addrsize : 0;
			dsym->indirectsymoff += dsym->indirectsymoff ? addrsize : 0;
		}
		offset += cmd->cmdsize;
	}
}

void				write_new_file(t_env *e, t_macho64 *macho)
{
	char				*ptr;
	size_t				off;
	size_t				off2;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	off = macho->text_entryoff + macho->text_size + 1;
	write(e->fd, e->file, off);

	write(e->fd, &woody64_func, woody64_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &macho->text_entryoff, sizeof(macho->text_entryoff));
	write(e->fd, &macho->text_size, sizeof(macho->text_size));
	write(e->fd, &macho->old_entryoff, sizeof(macho->old_entryoff));
	write(e->fd, &e->banner_len, sizeof(e->banner_len));
	if (e->banner_len > 1)
	{
		write(e->fd, e->banner, e->banner_len - 1);
		write(e->fd, "\n", 1);
	}
	off2 = macho->text_filesize - off;
	write(e->fd, e->file + off, off2);
	for (uint32_t i = macho->segtext->filesize - macho->lastsect_off + woody64_size + e->woody_datalen - 4; i > 0; i--)
		write(e->fd, "\0", 1);
	off = macho->text_filesize;
	write(e->fd, e->file + off, e->file_size - off - 1);
	close(e->fd);
	e->fd = 0;
}
