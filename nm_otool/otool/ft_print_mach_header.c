/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mach_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:24:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 05:39:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	ft_print_mach_header_sf(struct mach_header_64 *file)
{
	ft_putendl("Mach header");
	ft_putstr("      magic cputype cpusubtype  caps    filetype ncmds ");
	ft_putendl("sizeofcmds      flags");
	ft_puthex(file->magic, 8, 16, 0);
	ft_puthex(file->cputype, 10, 10, 0);
	ft_puthex((file->cpusubtype & ~CPU_SUBTYPE_MASK), 12, 10, 0);
	ft_putchar(' ');
	ft_puthex((file->cpusubtype & CPU_SUBTYPE_MASK) >> 24, 3, 16, 1);
	ft_puthex(file->filetype, 13, 10, 0);
	ft_puthex(file->ncmds, 7, 10, 0);
	ft_puthex(file->sizeofcmds, 12, 10, 0);
	ft_puthex(file->flags, 9, 16, 1);
	ft_putchar('\n');
}

static void	ft_print_mach_header_tt(struct mach_header *file)
{
	ft_putendl("Mach header");
	ft_putstr("      magic cputype cpusubtype  caps    filetype ncmds ");
	ft_putendl("sizeofcmds      flags");
	ft_puthex(file->magic, 8, 16, 0);
	ft_puthex(file->cputype, 9, 10, 0);
	ft_puthex((file->cpusubtype & ~CPU_SUBTYPE_MASK), 12, 10, 0);
	ft_putchar(' ');
	ft_puthex((file->cpusubtype & CPU_SUBTYPE_MASK) >> 24, 3, 16, 1);
	ft_puthex(file->filetype, 13, 10, 0);
	ft_puthex(file->ncmds, 7, 10, 0);
	ft_puthex(file->sizeofcmds, 12, 10, 0);
	ft_puthex(file->flags, 9, 16, 1);
	ft_putchar('\n');
}

void		ft_print_mach_header(void *file, int filetype)
{
	if (filetype == FILE_MACH_32)
		ft_print_mach_header_tt(file);
	else if (filetype == FILE_MACH_64)
		ft_print_mach_header_sf(file);
}
