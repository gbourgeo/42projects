/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_swap_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 21:46:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/28 21:47:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ps_swap_list(t_lib **a, t_lib **b, char **ret, char *c)
{
	t_lib	*tmp;

	tmp = NULL;
	if (*b)
	{
		tmp = (*b)->next;
		(*b)->next = *a;
		*a = *b;
		*b = tmp;
		*ret = ft_strjoin(*ret, c);
	}
}
