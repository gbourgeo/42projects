/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 20:59:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/05 09:09:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_clear_opt_files(t_file **file, int l)
{
	if (*file)
	{
		if ((*file)->next)
			ft_clear_opt_files(&(*file)->next, l);
		if ((*file)->name)
			free((*file)->name);
		(*file)->type = 0;
		(*file)->next = NULL;
		(*file)->prev = NULL;
		(*file)->time = 0;
		if (l)
		{
			ft_bzero((*file)->info.permit, 11);
			(*file)->info.link = 0;
			free((*file)->info.pw_name);
			free((*file)->info.gr_name);
			free((*file)->info.size);
			free((*file)->info.size2);
			ft_bzero((*file)->info.date, 14);
			if ((*file)->info.s_link)
				free((*file)->info.s_link);
		}
		free(*file);
		*file = NULL;
	}
}

void			ft_clear_dir_files(t_dir **dir, int l)
{
	if (*dir)
	{
		if ((*dir)->next)
			ft_clear_dir_files(&(*dir)->next, l);
		if ((*dir)->name)
			free((*dir)->name);
		ft_clear_opt_files(&(*dir)->file, l);
		ft_bzero((*dir)->opt, 6);
		(*dir)->d_size = 0;
		(*dir)->f_nbr = 0;
		(*dir)->f_maxlen = 0;
		(*dir)->next = NULL;
		(*dir)->prev = NULL;
		free(*dir);
		*dir = NULL;
	}
}
