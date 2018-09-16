/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_end_to_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 21:49:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/29 01:41:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ps_end_to_first(t_lib **a, char **ret, char *c)
{
	t_lib	*b;

	b = NULL;
	if (*a)
	{
		if ((*a)->next)
		{
			b = *a;
			while (b->next->next)
				b = b->next;
			b->next->next = *a;
			*a = b->next;
			b->next = NULL;
			*ret = ft_strjoin(*ret, c);
		}
	}
}
