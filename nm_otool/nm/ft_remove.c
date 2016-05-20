/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 02:01:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 02:53:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void				ft_remove(t_base *env)
{
	t_el			*el;
	t_el			*tmp;

	el = env->sect.elems;
	while (el)
	{
		if ((!env->options[opt_a] && el->type == '-') ||
			(env->options[opt_g] && (el->type < 'A' || el->type > 'Z')) ||
			(env->options[opt_u] && (el->type != 'u' && el->type != 'U')) ||
			(env->options[opt_U] && (el->type == 'u' || el->type == 'U')))
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
