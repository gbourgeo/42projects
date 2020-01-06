/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_narg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:56:53 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 18:02:30 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "cw_hexdump.h"

static void	print_errarg(t_env *e, int narg)
{
	if (narg > 2)
		ft_dprintf(2, "Error : too many arguments\n");
	else
		ft_dprintf(2, "Error : not enough argument\n");
	if (e->flag & FLAG_S && e->flag & FLAG_F)
	{
		ft_dprintf(2, "Usage : asm -s [name] [file.s]\n");
		ft_dprintf(2, "\tasm -f [path] [file.s]\n");
	}
	else if (e->flag & FLAG_S)
		ft_dprintf(2, "Usage : asm -s [name] [file.s]\n");
	else if (e->flag & FLAG_F)
		ft_dprintf(2, "Usage : asm -f [path] [file.s]\n");
	exit(1);
}

static void	unset_sf(t_env *e, int n_arg)
{
	if (n_arg != 2)
		print_errarg(e, n_arg);
	if (e->flag & FLAG_P)
		e->flag &= ~FLAG_P;
	if (e->flag & FLAG_GP)
		e->flag &= ~FLAG_GP;
}

static void	unset_d(t_env *e)
{
	if (e->flag & FLAG_N)
		e->flag &= ~FLAG_N;
	if (e->flag & FLAG_S)
		e->flag &= ~FLAG_S;
	if (e->flag & FLAG_F)
		e->flag &= ~FLAG_F;
}

void		parse_narg(t_env *e, int ac, int i)
{
	int n_arg;

	n_arg = ac - i;
	if (e->flag & ATLST_ONE && n_arg < 1)
	{
		ft_dprintf(2, "Error : Not enough argument\n");
		ft_dprintf(2, "Usage : asm [-Pdfnops] [file, ...]\n");
		exit(1);
	}
	if (e->flag & FLAG_S && e->flag & FLAG_F)
	{
		ft_dprintf(2, "Incompatible flags : -s, -f ; sees -h, --help\n");
		exit(1);
	}
	if (e->flag & FLAG_S || e->flag & FLAG_F)
		unset_sf(e, n_arg);
	if (e->flag & FLAG_D)
		unset_d(e);
}
