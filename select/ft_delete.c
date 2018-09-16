/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 07:03:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 13:20:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_del_elem(t_args *elem, t_info *info)
{
	if (elem)
	{
		if (elem->current == 1)
			elem->next->current = 1;
		if (elem == info->elems)
			info->elems = elem->next;
		elem->c = NULL;
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
		elem->prev = NULL;
		elem->next = NULL;
		free(elem);
	}
}

void	ft_del_list(t_info *info)
{
	t_args	*tmp;

	tmp = info->elems;
	while ((info->elems = info->elems->next) != tmp)
		ft_del_elem(tmp, info);
	free(tmp);
}
