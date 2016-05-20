/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_magic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:28:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 11:33:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void					ft_mach(void *file, int type, t_base *env, size_t i)
{
	if (env->file_type == NONE)
		env->file_type = FILE_MACH_O;
	env->sect.type = type;
	if (type == IS_32)
	{
		env->sect.hdr = (struct mach_header *)file;
		env->sect.cmd = (struct load_command *)(file + sizeof(*env->sect.hdr));
		env->sect.ncmds = env->sect.hdr->ncmds;
	}
	else
	{
		env->sect.hdrz = (struct mach_header_64 *)file;
		env->sect.cmd = (struct load_command *)(file + sizeof(*env->sect.hdrz));
		env->sect.ncmds = env->sect.hdrz->ncmds;
	}
	env->sect.size = 0;
	ft_get_sections(&env->sect);
	while (i < env->sect.ncmds)
	{
		if (env->sect.cmd->cmd == LC_SYMTAB)
			ft_get_symb(file, env);
		env->sect.cmd = (void *)env->sect.cmd + env->sect.cmd->cmdsize;
		i++;
	}
}

static uint32_t				ft_fat(void *file, t_base *env)
{
	int						nb_arch;
	int						i;
	unsigned int			cputype;
	struct fat_header		*hdr;
	struct fat_arch			*arc;

	if (env->file_type == NONE)
		env->file_type = FILE_FAT;
	hdr = (struct fat_header *)file;
	arc = (struct fat_arch *)(file + sizeof(struct fat_header));
	nb_arch = (hdr->magic == FAT_MAGIC) ? hdr->nfat_arch : SWAP(hdr->nfat_arch);
	i = -1;
	while (++i < nb_arch)
	{
		cputype = (hdr->magic == FAT_MAGIC) ? arc[i].cputype :
			ft_swap_bytes(arc[i].cputype);
		if (cputype == CPU_TYPE_X86_64)
			return ((hdr->magic == FAT_MAGIC) ? arc[i].offset :
					ft_swap_bytes(arc[i].offset));
	}
	return (0);
}

void						ft_magic(void *file, t_base *env)
{
	uint32_t				magic;

	magic = *(uint32_t *)file;
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		file += ft_fat(file, env);
		magic = *(uint32_t *)file;
	}
	if (ft_strncmp(file, ARMAG, SARMAG) == 0)
		ft_archive(file, env);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		ft_mach(file, IS_32, env, 0);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		ft_mach(file, IS_64, env, 0);
}
