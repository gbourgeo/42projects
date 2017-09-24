/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:22:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/31 18:33:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_clear_opt(t_opt *opts)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(LS_OPTIONS))
	{
		*((char*)opts + i) = 0;
		i++;
	}
	opts->date = 1;
	ft_clear_dir(&opts->files);
	opts->dir = NULL;
	opts->nb_dir = 0;
	opts->ret = 0;
}

void		ft_clear_dir(t_dir *dir)
{
	int		i;

	i = 0;
	if (dir == NULL)
		return ;
	dir->name = NULL;
	dir->file = NULL;
	while (i < 6)
		dir->opt[i++] = 0;
	dir->d_size = 0;
	dir->f_nbr = 0;
	dir->f_maxlen = 0;
	dir->error = -1;
	dir->next = NULL;
	dir->prev = NULL;
}

void		ft_clear_file(t_file *file)
{
	int		i;

	i = 0;
	if (file == NULL)
		return ;
	file->name = NULL;
	file->type = 1;
	file->next = NULL;
	file->prev = NULL;
	file->time = 0;
	while (i < 12)
		file->info.permit[i++] = 0;
	file->info.link = 0;
	file->info.pw_name = NULL;
	file->info.gr_name = NULL;
	file->info.size = NULL;
	file->info.size2 = NULL;
	i = 0;
	while (i < 20)
		file->info.date[i++] = 0;
	file->info.s_link = NULL;
}
