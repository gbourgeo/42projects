/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 22:01:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 13:32:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

ULL			ft_nb_players(t_uid *teams)
{
	ULL		ret;

	ret = 0;
	while (teams)
	{
		ret += teams->total;
		teams = teams->next;
	}
	return (ret);
}
