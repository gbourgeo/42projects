/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 12:41:51 by gilles            #+#    #+#             */
/*   Updated: 2016/12/31 23:15:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			multiple_print(t_dir *dir, t_opt *opt)
{
	if (!opt)
	{
		ft_putstr(dir->name);
		ft_putendl(":");
	}
	else
	{
		ft_putstr("total ");
		ft_putnbr((int)dir->d_size);
		ft_putchar('\n');
		ft_print_long_listing(dir, opt);
	}
}

static void			ft_print_line(t_file *file, int row, t_dir *dir, t_opt *opt)
{
	t_file			*tmp;
	int				col;
	int				file_per_col;

	tmp = file;
	col = opt->sz.ws_col / dir->f_maxlen;
	while (col-- && tmp)
	{
		ft_putstr(tmp->name);
		tmp->len = ft_strlen(tmp->name) + 1;
		if ((opt->p || opt->big_f) && tmp->type == DT_DIR)
			ft_putchar('/');
		else if (!opt->p && opt->big_f)
			ft_print_big_f(tmp);
		else
			tmp->len--;
		if (col)
			write(1, BLANCS, dir->f_maxlen - tmp->len);
		file_per_col = row;
		while (file_per_col-- && tmp)
			tmp = (!opt->r) ? tmp->prev : tmp->next;
	}
}

static void			ft_print_column(t_file *file, t_opt *opt)
{
	while (file)
	{
		ft_putstr(file->name);
		if ((opt->p || opt->big_f) && file->type == DT_DIR)
			ft_putchar('/');
		else if (!opt->p && opt->big_f)
			ft_print_big_f(file);
		ft_putchar('\n');
		file = (!opt->r) ? file->prev : file->next;
	}
}

void				ft_print_files(t_dir *dir, t_opt *opt)
{
	t_file			*tmp;
	int				row;
	int				loop;

	if (!dir->file)
		return ;
	dir->f_maxlen++;
	if (opt->l || opt->g || opt->o)
		return (ft_print_long_listing(dir, opt));
	tmp = dir->file;
	while ((!opt->r) && tmp->next)
		tmp = tmp->next;
	if (opt->one)
		return (ft_print_column(tmp, opt));
	row = (dir->f_nbr * dir->f_maxlen) / opt->sz.ws_col + 1;
	loop = row;
	while (loop--)
	{
		ft_print_line(tmp, row, dir, opt);
		ft_putchar('\n');
		tmp = (!opt->r) ? tmp->prev : tmp->next;
	}
}

void				ft_print_dir(int ac, t_opt *opt)
{
	t_dir			*dir;

	dir = opt->dir;
	while ((!opt->r || opt->big_s) && dir->next)
		dir = dir->next;
	if (opt->files.file)
		ft_putchar('\n');
	while (dir)
	{
		if (opt->files.file || ac++ > 1)
			multiple_print(dir, NULL);
		if (dir->error != -1)
			ft_perror(dir->name, dir);
		else if ((opt->l || opt->g || opt->o) && dir->file)
			multiple_print(dir, opt);
		else
			ft_print_files(dir, opt);
		dir = (!opt->r || opt->big_s) ? dir->prev : dir->next;
		if (dir)
			ft_putchar('\n');
	}
}
