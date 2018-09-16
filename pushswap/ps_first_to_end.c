/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_first_to_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 21:48:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/29 01:31:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ps_first_to_end(t_lib **a, char **ret, char *c)
{
	t_lib	*b;
	t_lib	*tmp;

	b = NULL;
	tmp = NULL;
	if (*a)
	{
		if ((*a)->next)
		{
			b = *a;
			*a = (*a)->next;
			b->next = NULL;
			tmp = *a;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = b;
			*ret = ft_strjoin(*ret, c);
		}
	}
}
