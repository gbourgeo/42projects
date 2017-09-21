/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 22:01:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 00:36:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int			ft_nb_players(int *players)
{
	int		ret;
	int		*ptr;

	ret = 0;
	ptr = players;
	while (ptr - players < MAX_TEAMS)
		ret += *ptr++;
	return (ret);
}
