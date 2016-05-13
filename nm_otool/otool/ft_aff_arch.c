/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:38:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/13 12:58:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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
