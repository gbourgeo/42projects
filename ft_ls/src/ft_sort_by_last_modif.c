/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 09:37:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/14 09:46:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_sort_file(t_file **file)
{
	t_file			*tmp;

	tmp = *file;
	while (tmp)
	{
		while (tmp->prev && tmp->inf.st_mtime < tmp->prev->inf.st_mtime)
		{
			if (tmp->prev->prev)
				tmp->prev->prev->next = tmp;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			tmp->next = tmp->prev;
			tmp->prev = tmp->next->prev;
			tmp->next->prev = tmp;
			if (tmp->prev == NULL)
				*file = tmp;
		}
		tmp = tmp->next;
	}
}

static void		ft_sort_dir(t_dir **dir)
{
	t_dir		*tmp;

	tmp = *dir;
	while (tmp)
	{
		while (tmp->prev && tmp->inf.st_mtime < tmp->prev->inf.st_mtime)
		{
			if (tmp->prev->prev)
				tmp->prev->prev->next = tmp;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			tmp->next = tmp->prev;
			tmp->prev = tmp->next->prev;
			tmp->next->prev = tmp;
			if (tmp->prev == NULL)
				*dir = tmp;
		}
		tmp = tmp->next;
	}
}

void			ft_sort_by_last_modif(t_opt *opt)
{
	t_dir		*dir2;

	if (opt->files.file)
		ft_sort_file(&opt->files.file);
	if (opt->dir)
	{
		ft_sort_dir(&opt->dir);
		dir2 = opt->dir;
		while (dir2)
		{
			ft_sort_file(&dir2->file);
			dir2 = dir2->next;
		}
	}
}
