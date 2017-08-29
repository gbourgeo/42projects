/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 22:01:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/28 00:40:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int			ft_nb_players(int *players)
{
	int		ret;
	int		*ptr;

	ret = 0;
	ptr = players;
	while (ptr - players < MIN_TEAMS)
		ret += *ptr++;
	return (ret);
}
