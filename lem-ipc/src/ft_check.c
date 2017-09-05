/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 17:34:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/05 21:54:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int				ft_check_minimum_players(int *table)
{
	size_t		need;
	int			*ptr;

	need = 0;
	ptr = table;
	while (ptr - table < MAX_TEAMS)
	{
		if (*ptr != 0 && *ptr < 2)
			need += *ptr;
		ptr++;
	}
	return (need);
}

int				ft_check_even_teams(int *table)
{
	int			max;
	int			*ptr;

	max = 0;
	ptr = table;
	while (ptr - table < MAX_TEAMS)
	{
		if (*ptr > 0)
		{
			if (max == 0)
				max = *ptr;
			else if (max != *ptr)
				return (1);
		}
		ptr++;
	}
	return (0);
}
