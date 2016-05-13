/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:29:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/08 18:40:11 by gbourgeo         ###   ########.fr       */
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

void				ft_remove_extra(t_base *env)
{
	t_el			*el;
	t_el			*tmp;

	el = env->sect.elems;
	while (el)
	{
		if (el->type == '-')
		{
			if (el->prev != NULL)
				el->prev->next = el->next;
			else
				env->sect.elems = el->next;
			if (el->next != NULL)
				el->next->prev = el->prev;
			tmp = el->next;
			ft_memset(el, '\0', sizeof(*el));
			free(el);
			el = tmp;
		}
		else
			el = el->next;
	}
}

static void			ft_swap_elems(t_el *elems)
{
	if (elems->prev->prev)
		elems->prev->prev->next = elems;
	if (elems->next)
		elems->next->prev = elems->prev;
	elems->prev->next = elems->next;
	elems->next = elems->prev;
	elems->prev = elems->next->prev;
	elems->next->prev = elems;
}

void				ft_sort_elems(t_base *env)
{
	t_el			*elems;

	elems = env->sect.elems;
	while (elems)
	{
		while (elems->prev && ft_strcmp(elems->prev->name, elems->name) > 0)
		{
			ft_swap_elems(elems);
			if (elems->prev == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
	elems = env->sect.elems;
	while (env->options[opt_n] && elems)
	{
		while (elems->prev && elems->prev->n_value > elems->n_value)
		{
			ft_swap_elems(elems);
			if (elems->prev == NULL)
				env->sect.elems = elems;
		}
		elems = elems->next;
	}
}
