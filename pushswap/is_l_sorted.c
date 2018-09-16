/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_l_sorted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 01:11:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/29 01:12:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			is_l_a_sorted(t_lib *l_a)
{
	if (l_a)
	{
		while (l_a->next && l_a->nb < l_a->next->nb)
		{
			if (l_a->nb < l_a->next->nb)
				l_a = l_a->next;
		}
		if (l_a->next == NULL)
			return (0);
	}
	return (1);
}
