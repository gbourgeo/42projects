/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_macho64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:43:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/17 20:29:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			macho.lastseg = (struct segment_command_64 *)cmd;
			if (ft_strcmp(macho.lastseg->segname, SEG_TEXT) == 0)
			{
				macho.segtext = macho.lastseg; /* Get the __TEXT segment */
				macho.lastsect = (struct section_64 *)(macho.lastseg + 1);
				for (size_t j = 0; j < macho.lastseg->nsects; j++)
				{
					if (ft_strcmp(macho.lastsect[j].sectname, SECT_TEXT) == 0)
						macho.sectext = macho.lastsect; /* Get the __text section */
				}
			}
		}
		offset += cmd->cmdsize;
	}
	woody64_encrypt((u_char *)(e->file + macho.sectext->offset), macho.sectext->size, e->key);
	macho.text_crypted_size = macho.sectext->size;
	change_file_headers(e, &macho);
	write_new_file(e, &macho);
}

void				change_file_headers(t_env *e, t_macho64 *macho)
{
	uint32_t		filesz;

	filesz = (e->banner_len > 1) ? woody64_size + e->banner_len : woody64_size;
/* Modify the program flags (disable ASLR) */
	macho->header->flags &= ~MH_PIE;
/* Modify the entry point */
	macho->old_entryoff = macho->entry->entryoff;
	macho->new_entryoff  = macho->lastseg->fileoff + macho->lastseg->filesize;
	macho->entry->entryoff = macho->new_entryoff;
/* Modify the __TEXT segment permissions (make it writable) */
	if (!(macho->segtext->initprot & 0x2))
		macho->segtext->initprot |= 0x2;
/* Modify last LOAD_COMMAND size and permissions (make it readable and executable) */
	macho->lastseg->filesize += filesz;
	if (!(macho->lastseg->initprot & 0x1))
		macho->lastseg->initprot |= 0x1;
	if (!(macho->lastseg->initprot & 0x4))
		macho->lastseg->initprot |= 0x4;
}

void				write_new_file(t_env *e, t_macho64 *macho)
{
	char		*ptr;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	write(e->fd, e->file, e->file_size - 1);
	write(e->fd, &woody64_func, woody64_size - woody64_arg_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &macho->sectext->addr, sizeof(macho->sectext->addr));
	write(e->fd, &macho->text_crypted_size, sizeof(macho->text_crypted_size));
	write(e->fd, &e->banner_len, sizeof(e->banner_len));
	if (e->banner_len > 1)
	{
		write(e->fd, e->banner, e->banner_len - 1);
		write(e->fd, "\n", 1);
	}
	close(e->fd);
	e->fd = 0;
}
