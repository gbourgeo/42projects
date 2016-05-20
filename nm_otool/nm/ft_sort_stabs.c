/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_stabs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 00:10:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 01:47:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			ft_sort_stabs(t_base *env)
{
	t_el		*elems;

	elems = env->sect.elems;
	while (elems && elems->type == '-' && !*elems->name)
	{
		while (elems->prev && elems->prev->n_value > elems->n_value)
		{
			if (ft_swap_elems(elems) == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
	elems = env->sect.elems;
	while (elems)
	{
		if (elems->prev && elems->prev->n_value == elems->n_value &&
			elems->prev->type == '-' && elems->type != '-')
		{
			if (ft_swap_elems(elems) == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
}
