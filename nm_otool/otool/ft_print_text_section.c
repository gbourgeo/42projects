/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text_section.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 21:08:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/22 01:15:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			ft_print_text_section_sf(void *file)
{
	t_sf			sf;
	uint32_t		i;
	uint32_t		j;

	sf.hdr = (struct mach_header_64 *)(file);
	sf.cmds = file + sizeof(*sf.hdr);
	sf.seg = (struct segment_command_64 *)sf.cmds;
	i = 0;
	while (i < sf.hdr->ncmds)
	{
		if (sf.seg[i].cmd == LC_SEGMENT_64)
		{
			j = 0;
			sf.sec = (struct section_64 *)(&sf.seg[i] + 1);
			while (j < sf.seg[i].nsects)
			{
				if (!ft_strcmp(sf.sec[j].segname, "__TEXT") &&
					!ft_strcmp(sf.sec[j].sectname, "__text"))
					return (ft_aff_sf(&sf.sec[j], file + sf.sec[j].offset, TS));
				j++;
			}
		}
		i++;
	}
}

static void			ft_print_text_section_tt(void *file)
{
	t_tt			sf;
	uint32_t		i;
	uint32_t		j;

	sf.hdr = (struct mach_header *)(file);
	sf.cmds = file + sizeof(*sf.hdr);
	sf.seg = (struct segment_command *)sf.cmds;
	i = 0;
	while (i < sf.hdr->ncmds)
	{
		if (sf.seg[i].cmd == LC_SEGMENT)
		{
			j = 0;
			sf.sec = (struct section *)(&sf.seg[i] + 1);
			while (j < sf.seg[i].nsects)
			{
				if (!ft_strcmp(sf.sec[j].segname, "__TEXT") &&
					!ft_strcmp(sf.sec[j].sectname, "__text"))
					return (ft_aff_tt(&sf.sec[j], file + sf.sec[j].offset, TS));
				j++;
			}
		}
		i++;
	}
}

void				ft_print_text_section(void *file, int filetype)
{
	if (filetype == FILE_MACH_32)
		ft_print_text_section_tt(file);
	else if (filetype == FILE_MACH_64)
		ft_print_text_section_sf(file);
}
