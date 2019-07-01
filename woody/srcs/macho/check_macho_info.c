/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:27:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/17 20:34:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"
#include "main.h"

static int				is_macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

static int				is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

static int				is_executable(uint32_t filetype)
{
	return (filetype == MH_EXECUTE);
}

void					check_macho_info(t_env *e)
{
	struct mach_header	*header;
	uint32_t			magic;

	header = (struct mach_header *)e->file;
	magic = header->magic;
	if (!is_macho(magic))
		ft_fatal("Invalid MACHO file", e);
	if (!is_64(magic))
		ft_fatal("Invalid MACHO file architecture", e);
	if (!is_executable(header->filetype))
		ft_fatal("Unsupported MACHO file type", e);
}
