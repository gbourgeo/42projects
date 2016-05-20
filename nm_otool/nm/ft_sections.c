/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:45:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/14 19:26:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void				ft_get_name64(t_sec *sect)
{
	unsigned int		tab[3];
	SEG_64				*seg;
	struct section_64	*sec;

	seg = (SEG_64 *)sect->cmd;
	tab[0] = 0;
	tab[1] = 0;
	while (tab[0]++ < sect->ncmds)
	{
		if (seg->cmd == LC_SEGMENT_64)
		{
			sec = (struct section_64 *)(seg + 1);
			tab[2] = 0;
			while (tab[2]++ < seg->nsects)
			{
				sect->sec[tab[1]++] = sec->sectname;
				sec = (void *)sec + sizeof(*sec);
			}
		}
		seg = (void *)seg + seg->cmdsize;
	}
}

static void				ft_get_name32(t_sec *sect)
{
	unsigned int		tab[3];
	SEG_32				*seg;
	struct section		*sec;

	seg = (SEG_32 *)sect->cmd;
	tab[0] = 0;
	tab[1] = 0;
	while (tab[0]++ < sect->ncmds)
	{
		if (seg->cmd == LC_SEGMENT)
		{
			sec = (struct section *)(seg + 1);
			tab[2] = 0;
			while (tab[2]++ < seg->nsects)
			{
				sect->sec[tab[1]++] = sec->sectname;
				sec = (void *)sec + sizeof(*sec);
			}
		}
		seg = (void *)seg + seg->cmdsize;
	}
}

static void				ft_get_size(t_sec *sect)
{
	struct load_command	*cmds;
	SEG_32				*seg;
	SEG_64				*segz;
	unsigned int		i;

	i = 0;
	cmds = sect->cmd;
	if (sect->type == IS_32)
		seg = (SEG_32 *)sect->cmd;
	else
		segz = (SEG_64 *)sect->cmd;
	while (i++ < sect->ncmds)
	{
		if (sect->type == IS_32 && cmds->cmd == LC_SEGMENT)
		{
			sect->size += seg->nsects;
			seg = (void *)seg + seg->cmdsize;
		}
		else if (sect->type == IS_64 && cmds->cmd == LC_SEGMENT_64)
		{
			sect->size += segz->nsects;
			segz = (void *)segz + segz->cmdsize;
		}
		cmds = (void *)cmds + cmds->cmdsize;
	}
}

void					ft_get_sections(t_sec *sect)
{
	ft_get_size(sect);
	if (sect->size == 0)
		return ;
	sect->sec = malloc(sizeof(char **) * sect->size);
	if (sect->sec == NULL)
	{
		sect->size = 0;
		return ;
	}
	if (sect->type == IS_32)
		ft_get_name32(sect);
	else
		ft_get_name64(sect);
}
