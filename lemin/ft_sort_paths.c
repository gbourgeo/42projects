/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 14:17:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:29:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_sort_paths_by_len(t_path *paths);

void		ft_sort_paths(t_path *paths)
{
	ft_sort_paths_by_len(paths->next);
}

static void	ft_sort_paths_by_len(t_path *paths)
{
	t_path	swap;
	t_path	*tmp1;
	t_path	*tmp2;

	tmp1 = paths;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (tmp2->len < tmp1->len)
			{
				swap.name = tmp1->name;
				swap.len = tmp1->len;
				tmp1->name = tmp2->name;
				tmp1->len = tmp2->len;
				tmp2->name = swap.name;
				tmp2->len = swap.len;
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}
