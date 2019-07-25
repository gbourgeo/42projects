/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 13:15:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:28:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			ft_check_paths(t_env *e)
{
	t_map	*tmp;
	int		count;

	tmp = e->rooms;
	count = 0;
	while (tmp)
	{
		if (tmp->special == START || tmp->special == END)
		{
			if (tmp->linknb == 0)
				return (0);
			count++;
		}
		tmp = tmp->next;
	}
	if (count != 2)
		return (0);
	return (1);
}
