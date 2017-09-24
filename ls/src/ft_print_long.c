/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 14:41:14 by gilles            #+#    #+#             */
/*   Updated: 2015/06/25 08:38:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_print_permits(t_file *file, t_dir *dir)
{
	int			nb;
	size_t		size;

	ft_putstr(file->info.permit);
	if (!file->info.permit[10])
		ft_putchar(' ');
	size = file->info.link;
	nb = 0;
	while ((size /= 10) > 0)
		nb++;
	while (nb++ < dir->opt[1])
		ft_putchar(' ');
	ft_putnbr(file->info.link);
	ft_putchar(' ');
}

static void		ft_print_other(char *txt, int len, int order)
{
	int				nb;

	if (txt)
	{
		if (order == 0)
		{
			ft_putstr(txt);
			ft_putchar(' ');
		}
		nb = ft_strlen(txt);
		while (nb++ < len)
			ft_putchar(' ');
		if (order == 1)
		{
			ft_putchar(' ');
			ft_putstr(txt);
		}
	}
}

static void		ft_print_size(t_inf info, t_dir *dir)
{
	int				nb;

	if (dir->opt[5] == 0)
		ft_print_other(info.size, dir->opt[4], 1);
	else if (info.size2)
	{
		ft_putchar(' ');
		nb = ft_strlen(info.size);
		while (nb++ <= dir->opt[4])
			ft_putchar(' ');
		ft_putstr(info.size);
		ft_putchar(',');
		nb = ft_strlen(info.size2);
		while (nb++ <= dir->opt[5])
			ft_putchar(' ');
		ft_putstr(info.size2);
	}
	else
		ft_print_other(info.size, dir->opt[4] + dir->opt[5] + 2, 1);
}

static void		ft_print_names(t_file *file, t_dir *dir)
{
	ft_print_other(file->info.pw_name, dir->opt[2], 0);
	if ((file->info.pw_name && file->info.gr_name) ||
		(!file->info.pw_name && !file->info.gr_name))
		ft_putchar(' ');
	ft_print_other(file->info.gr_name, dir->opt[3], 0);
}

void			ft_print_long_listing(t_dir *dir, t_opt *options)
{
	t_file			*file;

	file = dir->file;
	while (!options->r && file && file->next)
		file = file->next;
	while (file)
	{
		ft_print_permits(file, dir);
		ft_print_names(file, dir);
		ft_print_size(file->info, dir);
		ft_print_other(file->info.date, ft_strlen(file->info.date), 0);
		ft_putstr(file->name);
		if ((options->p || options->big_f) && S_ISDIR(file->inf.st_mode))
			ft_putchar('/');
		else if (!options->p && options->big_f)
			ft_print_big_f(file);
		if (*file->info.permit == 'l')
		{
			write(1, " -> ", 4);
			ft_putstr(file->info.s_link);
		}
		ft_putchar('\n');
		file = !options->r ? file->prev : file->next;
	}
}
