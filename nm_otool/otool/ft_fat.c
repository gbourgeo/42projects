/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 02:19:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 05:52:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void				ft_print_fat_arch(int i, struct fat_arch *arch)
{
	if (arch == NULL)
		return ;
	ft_putstr("\narchitecture ");
	ft_putnbr(i);
	ft_putstr("\n    cputype ");
	ft_putnbr(arch->cputype);
	ft_putstr("\n    cpusubtype ");
	ft_putnbr(arch->cpusubtype & ~CPU_SUBTYPE_MASK);
	ft_putstr("\n    capabilities");
	ft_puthex((arch->cpusubtype & CPU_SUBTYPE_MASK) >> 24, 2, 16, 1);
	ft_putstr("\n    offset ");
	ft_putnbr(arch->offset);
	ft_putstr("\n    size ");
	ft_putnbr(arch->size);
	ft_putstr("\n    align 2^");
	ft_putnbr(arch->align);
	ft_putstr(" (");
	ft_putnbr(ft_power(2, arch->align));
	ft_putstr(")");
	free(arch);
}

static struct fat_arch	*ft_swap_arch(struct fat_arch *arch)
{
	struct fat_arch		*dup;

	dup = malloc(sizeof(*dup));
	if (dup == NULL)
		return (NULL);
	dup->cputype = ft_swap_bytes(arch->cputype);
	dup->cpusubtype = ft_swap_bytes(arch->cpusubtype);
	dup->offset = ft_swap_bytes(arch->offset);
	dup->size = ft_swap_bytes(arch->size);
	dup->align = ft_swap_bytes(arch->align);
	return (dup);
}

static void				ft_print_fat_header(int size, struct fat_header *fat,
											struct fat_arch *arch)
{
	int					i;

	ft_putendl("Fat headers");
	ft_putstr("fat_magic ");
	if (fat->magic == FAT_MAGIC)
		ft_putendl("0xbebafeca");
	else
		ft_putendl("0xcafebabe");
	ft_putstr("nfat_arch ");
	ft_putnbr(size);
	i = 0;
	while (i < size)
	{
		if (fat->magic == FAT_MAGIC)
			ft_print_fat_arch(i, &arch[i]);
		else
			ft_print_fat_arch(i, ft_swap_arch(&arch[i]));
		i++;
	}
	ft_putchar('\n');
}

void					*ft_fat(void *file, t_env *env)
{
	int					nb_arch;
	int					i;
	uint32_t			cputype;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	env->file_type = (env->file_type == NONE) ? FILE_FAT : env->file_type;
	fat = (struct fat_header *)file;
	arch = (struct fat_arch *)(file + sizeof(*fat));
	nb_arch = (fat->magic == FAT_MAGIC) ? fat->nfat_arch : SWAP(fat->nfat_arch);
	if (env->options[opt_f])
		ft_print_fat_header(nb_arch, fat, arch);
	i = -1;
	while (++i < nb_arch)
	{
		cputype = (fat->magic == FAT_MAGIC) ?
			arch[i].cputype : SWAP(arch[i].cputype);
		if (cputype == CPU_TYPE_X86_64)
		{
			file += (fat->magic == FAT_MAGIC) ? arch[i].offset :
					ft_swap_bytes(arch[i].offset);
			return (file);
		}
	}
	return (0);
}
