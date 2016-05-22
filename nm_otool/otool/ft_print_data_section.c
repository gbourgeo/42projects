/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_data_section.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:30:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 17:46:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			ft_print_data_sf(void *file)
{
	t_sf			sf;
	uint32_t		i;
	uint32_t		j;

	sf.hdr = (struct mach_header_64 *)file;
	sf.cmds = (struct load_command *)(file + sizeof(struct mach_header_64));
	sf.seg = (struct segment_command_64 *)(sf.cmds);
	i = 0;
	while (i++ < sf.hdr->ncmds)
	{
		if (sf.seg->cmd == LC_SEGMENT_64)
		{
			j = 0;
			sf.sec = (struct section_64 *)(sf.seg + 1);
			while (j++ < sf.seg->nsects)
			{
				if (!ft_strcmp(sf.sec->segname, "__DATA") &&
					!ft_strcmp(sf.sec->sectname, "__data"))
					return (ft_aff_sf(sf.sec, file + sf.sec->offset, DATA_SEC));
				sf.sec = (void *)sf.sec + sizeof(struct section_64);
			}
		}
		sf.seg = (void *)sf.seg + sf.seg->cmdsize;
	}
}

static void			ft_print_data_tt(void *file)
{
	t_tt			sf;
	uint32_t		i;
	uint32_t		j;

	sf.hdr = (struct mach_header *)(file);
	sf.cmds = (struct load_command *)(file + sizeof(*sf.hdr));
	sf.seg = (struct segment_command *)sf.cmds;
	i = 0;
	while (i++ < sf.hdr->ncmds)
	{
		if (sf.seg->cmd == LC_SEGMENT)
		{
			j = 0;
			sf.sec = (struct section *)(sf.seg + 1);
			while (j++ < sf.seg->nsects)
			{
				if (!ft_strcmp(sf.sec->segname, "__DATA") &&
					!ft_strcmp(sf.sec->sectname, "__data"))
					return (ft_aff_tt(sf.sec, file + sf.sec->offset, DATA_SEC));
				sf.sec = (void *)sf.sec + sizeof(struct section);
			}
		}
		sf.seg = (void *)sf.seg + sf.seg->cmdsize;
	}
}

void				ft_print_data_section(void *file, int filetype)
{
	if (filetype == FILE_MACH_32)
		ft_print_data_tt(file);
	else if (filetype == FILE_MACH_64)
		ft_print_data_sf(file);
}
