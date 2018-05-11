/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pac_macho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:05:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 14:27:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			macho32(t_env *e)
{
	(void)e;
}

static void			macho64(t_env *e)
{
// TODO remove MH_PIE bit from header->flags;
}


void				pack_macho(t_env *e)
{
	mach_header		*header;
	uint32_t		magic;

	header = ((mach_header *)e->file);
	magic = header->magic;
	if (magic != MH_MAGIC && magic != MH_CIGAM &&
		magic != MH_MAGIC_64 || magic != MH_CIGAM_64)
		ft_fatal("Invalid MACHO file type", e);
	if (header->filetype != MH_EXECUTE)
		ft_fatal("Unsupported MACHO file type", e);
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		macho32(e);
	else
		macho64(e);
}
