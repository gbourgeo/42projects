/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_shared_libraries.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 22:24:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/15 16:16:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void					ft_print_dylib(struct load_command *cmds)
{
	struct dylib_command	*dyl;

	dyl = (struct dylib_command *)cmds;
	ft_putchar('\t');
	ft_putstr((char *)cmds + dyl->dylib.name.offset);
	ft_putstr(" (compatibility version ");
	ft_putnbr(dyl->dylib.compatibility_version >> 16);
	ft_putchar('.');
	ft_putnbr((dyl->dylib.compatibility_version >> 8) & 0xff);
	ft_putchar('.');
	ft_putnbr(dyl->dylib.compatibility_version & 0xff);
	ft_putstr(", current version ");
	ft_putnbr(dyl->dylib.current_version >> 16);
	ft_putchar('.');
	ft_putnbr((dyl->dylib.current_version >> 8) & 0xff);
	ft_putchar('.');
	ft_putnbr(dyl->dylib.current_version & 0xff);
	ft_putstr(")\n");
}

static void					ft_print_tt(void *file)
{
	t_tt					sf;
	uint32_t				i;

	sf.hdr = (struct mach_header *)file;
	sf.cmds = file + sizeof(*sf.hdr);
	i = 0;
	while (i++ < sf.hdr->ncmds)
	{
		if (sf.cmds->cmd == LC_ID_DYLIB || sf.cmds->cmd == LC_REEXPORT_DYLIB ||
			sf.cmds->cmd == LC_LOAD_DYLIB ||
			sf.cmds->cmd == LC_LOAD_WEAK_DYLIB ||
			sf.cmds->cmd == LC_LOAD_UPWARD_DYLIB ||
			sf.cmds->cmd == LC_LAZY_LOAD_DYLIB)
			ft_print_dylib(sf.cmds);
		sf.cmds = (void *)sf.cmds + sf.cmds->cmdsize;
	}
}

static void					ft_print_sf(void *file)
{
	t_sf					sf;
	uint32_t				i;

	sf.hdr = (struct mach_header_64 *)file;
	sf.cmds = file + sizeof(*sf.hdr);
	i = 0;
	while (i++ < sf.hdr->ncmds)
	{
		if (sf.cmds->cmd == LC_ID_DYLIB || sf.cmds->cmd == LC_REEXPORT_DYLIB ||
			sf.cmds->cmd == LC_LOAD_DYLIB ||
			sf.cmds->cmd == LC_LOAD_WEAK_DYLIB ||
			sf.cmds->cmd == LC_LOAD_UPWARD_DYLIB ||
			sf.cmds->cmd == LC_LAZY_LOAD_DYLIB)
			ft_print_dylib(sf.cmds);
		sf.cmds = (void *)sf.cmds + sf.cmds->cmdsize;
	}
}

void						ft_print_shared_libraries(void *file, int filetype)
{
	if (filetype == FILE_MACH_32)
		ft_print_tt(file);
	else if (filetype == FILE_MACH_64)
		ft_print_sf(file);
}
