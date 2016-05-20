/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:29:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 11:34:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_arc		*ft_remove_duplicata(t_arc *arc)
{
	t_arc			*ret;
	t_arc			*tmp;

	ret = arc;
	while (arc)
	{
		if (arc->prev && arc->prev->off == arc->off)
		{
			tmp = arc->prev;
			arc->prev->next = arc->next;
			if (arc->next)
				arc->next->prev = arc->prev;
			ft_memset(arc, '\0', sizeof(*arc));
			free(arc);
			arc = tmp;
		}
		arc = arc->next;
	}
	return (ret);
}

t_arc				*ft_sort_arc(t_arc *arc)
{
	t_arc			*ret;

	ret = arc;
	while (arc)
	{
		while (arc->prev && arc->pos < arc->prev->pos)
		{
			if (arc->prev->prev)
				arc->prev->prev->next = arc;
			if (arc->next)
				arc->next->prev = arc->prev;
			arc->prev->next = arc->next;
			arc->next = arc->prev;
			arc->prev = arc->next->prev;
			arc->next->prev = arc;
		}
		if (arc->prev == NULL)
			ret = arc;
		arc = arc->next;
	}
	return (ft_remove_duplicata(ret));
}

void				ft_sort_elems(t_base *env)
{
	t_el			*elems;

	elems = env->sect.elems;
	while (elems)
	{
		while (elems->prev && (ft_strcmp(elems->prev->name, elems->name) > 0 ||
							(ft_strcmp(elems->prev->name, elems->name) == 0 &&
							elems->n_value < elems->prev->n_value)))
		{
			if (ft_swap_elems(elems) == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
	elems = env->sect.elems;
	while (env->options[opt_n] && elems)
	{
		while (elems->prev && (elems->prev->n_value > elems->n_value ||
							(elems->type == 'U' && elems->prev->type != 'U')))
		{
			if (ft_swap_elems(elems) == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
}
