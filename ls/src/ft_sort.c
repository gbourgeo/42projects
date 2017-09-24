/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 11:18:17 by gilles            #+#    #+#             */
/*   Updated: 2015/06/25 07:11:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_sort_by_name(t_file **file)
{
	t_file			*tmp;

	tmp = *file;
	while (tmp)
	{
		while (tmp->prev && ft_strcmp(tmp->name, tmp->prev->name) > 0)
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

void				ft_sort(t_opt *opt)
{
	if (!opt->big_s)
		ft_sort_by_name(&opt->files.file);
	if (opt->t)
	{
		if (opt->big_s)
			ft_sort_by_file_size(opt);
		else if (opt->date == 3)
			ft_sort_by_file_creation(opt);
		else if (opt->date == 2)
			ft_sort_by_last_change(opt);
		else if (opt->date == 0)
			ft_sort_by_last_access(opt);
		else
			ft_sort_by_last_modif(opt);
	}
	else if (opt->big_s)
		ft_sort_by_file_size(opt);
}
