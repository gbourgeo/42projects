/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_macho64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:43:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/06/07 01:47:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
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
	macho.lastseg = macho.segment;
	woody64_encrypt((u_char *)(e->file + macho.sectext->offset), macho.sectext->size, e->key);
	change_file_headers(e, &macho);
	write_new_file(e, &macho);
}

void				change_file_headers(t_env *e, t_macho64 *macho)
{
	e->woody_datalen = 0
		+ sizeof(e->key)
		+ sizeof(macho->text_entryoff)
		+ sizeof(macho->sectext_size)
		+ sizeof(macho->old_entryoff)
		+ sizeof(e->banner_len)
		+ ((e->banner_len > 1) ? e->banner_len : 0);
/* First we store the data we will use later */
	macho->sectext_size = macho->sectext->size;
	macho->new_entryoff = macho->lastseg->fileoff + macho->lastseg->vmsize;
	macho->text_entryoff = macho->sectext->offset - macho->new_entryoff;
	macho->old_entryoff = macho->entry->entryoff - macho->new_entryoff;
	macho->segtext_size = macho->segtext->filesize;
/* Modify the executable flags (disable ASLR) */
	macho->header->flags &= ~MH_PIE;
/* Modify the entry point */
	macho->entry->entryoff = macho->new_entryoff;
/* Modify the __TEXT segment permissions (make it writable for decryption) */
	if (!(macho->segtext->initprot & 0x2))
		macho->segtext->initprot |= 0x2;
/* Modify the Mach-o Header */
	macho->header->ncmds += 1;
	macho->header->sizeofcmds += (sizeof(struct segment_command_64) + sizeof(struct section_64));
}

void				write_new_file(t_env *e, t_macho64 *macho)
{
	char				*ptr;
	size_t				off;
	size_t				off2;
	struct segment_command_64 newseg;
	struct section_64	newsect;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	off = ((size_t)macho->lastseg + sizeof(struct segment_command_64) + sizeof(struct section_64) * macho->lastseg->nsects) - (size_t)e->file;
	write(e->fd, e->file, off);

	newseg.cmd = LC_SEGMENT_64;
	newseg.cmdsize = sizeof(struct segment_command_64) + sizeof(struct section_64);
	ft_strncpy(newseg.segname, "__GBO", sizeof(newseg.segname));
	newseg.vmaddr = macho->lastseg->vmaddr + macho->lastseg->vmsize;
	newseg.vmsize = 0;
	while (newseg.vmsize < woody64_size + e->woody_datalen)
		newseg.vmsize += getpagesize();
	newseg.fileoff = macho->lastseg->fileoff + macho->lastseg->vmsize;
	newseg.filesize = woody64_size + e->woody_datalen;
	newseg.maxprot = (0x1 | 0x2 | 0x4);
	newseg.initprot = (0x1 | 0x2 | 0x4);
	newseg.nsects = 1;
	newseg.flags = 0;
	write(e->fd, &newseg, sizeof(newseg));
	ft_strncpy(newsect.sectname, "__gbo", sizeof(newsect.sectname));
	ft_strncpy(newsect.segname, "__GBO", sizeof(newsect.segname));
	newsect.addr = newseg.vmaddr;
	newsect.size = woody64_size + e->woody_datalen;
	newsect.offset = newseg.fileoff;
	newsect.align = macho->sectext->align;
	newsect.reloff = 0;
	newsect.nreloc = 0;
	newsect.flags = macho->sectext->flags;
	newsect.reserved1 = 0;
	newsect.reserved2 = 0;
	newsect.reserved3 = 0;
	write(e->fd, &newsect, sizeof(newsect));

	off2 = macho->sectext->offset - newseg.cmdsize;
	write(e->fd, e->file + off, off2 - off);
	off = macho->sectext->offset;
	write(e->fd, e->file + off, e->file_size - off - 1);
	for (uint32_t i = macho->lastseg->vmsize - macho->lastseg->filesize; i > 0; i--)
		write(e->fd, "\0", 1);

	write(e->fd, &woody64_func, woody64_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &macho->text_entryoff, sizeof(macho->text_entryoff));
	write(e->fd, &macho->sectext_size, sizeof(macho->sectext_size));
	write(e->fd, &macho->old_entryoff, sizeof(macho->old_entryoff));
	write(e->fd, &e->banner_len, sizeof(e->banner_len));
	if (e->banner_len > 1)
	{
		write(e->fd, e->banner, e->banner_len - 1);
		write(e->fd, "\n", 1);
	}
	close(e->fd);
	e->fd = 0;
}
