/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:27:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/16 09:52:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"
#include "main.h"

extern uint32_t	woody64_size;
extern uint32_t	woody64_arg_size;
void			woody64_encrypt(u_char *data, size_t len, const uint32_t *key);
void			woody64_func(void);
void			woody64_decrypt(u_char *data, size_t len, const uint32_t *key);
void			print_hex(u_char *data, uint32_t size);
void			print_macho64(t_env *e);

static int		is_macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

static int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

/* static int		is_swap(uint32_t magic) */
/* { */
/* 	return (magic == MH_MAGIC || magic == MH_MAGIC_64); */
/* } */

void			get_macho_info(t_env *e)
{
	struct mach_header	*header;
	uint32_t			magic;

	header = (struct mach_header *)e->file;
	magic = header->magic;
	if (!is_macho(magic))
		ft_fatal("Invalid MACHO file type", e);
	if (header->filetype != MH_EXECUTE)
		ft_fatal("Unsupported MACHO file type", e);

	generate_new_key(e->key);
	is_64(magic) ? pack_macho64(e) : pack_macho32(e);
}

void			pack_macho32(t_env *e)
{
	struct mach_header_64		*header;
	uint32_t					offset;

	header = (struct mach_header_64 *)e->file;
	offset = sizeof(*header);

	struct load_command			*cmd;
	char						maxprot[]  = "(   )";
	char						initprot[] = "(   )";
	ft_printf("\ncmd\t\t cmdsize\t segname\t vmaddr\t\t vmsize\t fileoff\t filesize\t maxprot\t initprot\t nsects\t flags\n");
	for (size_t i = 0; i < header->ncmds; i++)
	{
		cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_SEGMENT)
		{
			struct segment_command *segment = (struct segment_command *)cmd;
			ft_printf("%-11d\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %d %s\t %d %s\t %-5d\t %#x\n",
					  segment->cmd, segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot, maxprot,
					  segment->initprot, initprot, segment->nsects, segment->flags);
		}
		else
			ft_printf("%-11d\t %#.5x\n", cmd->cmd, cmd->cmdsize);
		offset += cmd->cmdsize;
	}
}

void			pack_macho64(t_env *e)
{
	t_macho64					macho;
	struct load_command			*cmd;
	uint32_t					offset;

	macho.header = (struct mach_header_64 *)e->file;
	offset = sizeof(*macho.header);
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
			macho.lastsect = (struct section_64 *)(macho.lastseg + 1);
			for (size_t j = 0; j < macho.lastseg->nsects; j++)
			{
				if (ft_strcmp(macho.lastsect[j].sectname, SECT_TEXT) == 0)
					macho.sectext = macho.lastsect; /* Get the __text section */
			}
		}
		offset += cmd->cmdsize;
	}

	uint32_t		filesz;

	filesz = (e->banner_len > 1) ? woody64_size + e->banner_len : woody64_size;

/* Modify the program flags */
	macho.header->flags &= ~MH_PIE;

/* Modify the entry point */
	macho.old_entryoff = macho.entry->entryoff;
	macho.new_entryoff  = macho.lastseg->fileoff + macho.lastseg->filesize;
	macho.entry->entryoff = macho.new_entryoff;

/* Modify last LOAD_COMMAND */
	macho.lastseg->filesize += filesz;
	if (!(macho.lastseg->initprot & 0x4))
		macho.lastseg->initprot += 0x4;

/* 	print_hex((u_char *)(e->file + sectext->offset), sectext->size); */
	woody64_encrypt((u_char *)(e->file + macho.sectext->offset), macho.sectext->size, e->key);
/* 	print_hex((u_char *)(e->file + sectext->offset), sectext->size); */
/* 	woody64_decrypt((u_char *)(e->file + sectext->offset), sectext->size, e->key); */
/* 	print_hex((u_char *)(e->file + sectext->offset), sectext->size); */
	macho.text_crypted_size = macho.sectext->size - (macho.sectext->size % 8);

	char		*ptr;

	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	write(e->fd, e->file, e->file_size - 1);
	write(e->fd, &woody64_func, woody64_size - woody64_arg_size);
	write(e->fd, e->key, sizeof(e->key));
	write(e->fd, &macho.sectext->addr, sizeof(macho.sectext->addr));
	write(e->fd, &macho.text_crypted_size, sizeof(macho.text_crypted_size));
	write(e->fd, &e->banner_len, sizeof(e->banner_len));
	if (e->banner_len > 1)
	{
		write(e->fd, e->banner, e->banner_len - 1);
		write(e->fd, "\n", 1);
	}
	close(e->fd);
	e->fd = 0;
}
