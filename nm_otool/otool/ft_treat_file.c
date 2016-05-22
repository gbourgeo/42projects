/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 06:37:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/22 10:04:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int					ft_mach(void *file, t_env *env, int filetype)
{
	if (OPT_THDL)
		ft_putchar('\n');
	if (env->file_type == NONE)
		env->file_type = filetype;
	if (env->options[opt_h])
		ft_print_mach_header(file, filetype);
	if (env->options[opt_L])
		ft_print_shared_libraries(file, filetype);
	if (env->options[opt_t])
		ft_print_text_section(file, filetype);
	if (env->options[opt_d])
		ft_print_data_section(file, filetype);
	return (0);
}

int							ft_treat_file(void *file, t_env *env)
{
	uint32_t				magic;

	magic = *((uint32_t *)(file));
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (ft_treat_file(ft_fat(file, env), env));
	if (!ft_strncmp(file, ARMAG, SARMAG))
	{
		ft_putstr("Archive : ");
		ft_putendl(env->file_name);
		return (ft_archive(file, env));
	}
	if (env->file_type != FILE_ARCH && (OPT_THDL))
	{
		ft_putstr(env->file_name);
		ft_putchar(':');
	}
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (ft_mach(file, env, FILE_MACH_32));
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (ft_mach(file, env, FILE_MACH_64));
	if (env->file_type != FILE_ARCH &&
		((!OPT_A || (OPT_A && OPT_T)) && (!OPT_F || (OPT_F && OPT_T) || OPT_H)))
		ft_putendl(" is not an object file");
	return (1);
}
