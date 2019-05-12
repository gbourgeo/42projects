/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 04:11:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/12 20:35:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemipc.h"

static t_player	*ft_new_player(t_player *next)
{
	t_player	*ret;

	if ((ret = malloc(sizeof(*ret))) == NULL)
	{
		ft_exit(1, "malloc", 0);
		return (NULL);
	}
	ft_memset(ret, 0, sizeof(*ret));
	ret->next = next;
	return (ret);
}

t_player		*ft_create_players_list(void)
{
	t_player	*ret;
	ULL			i;

	ret = NULL;
	i = 1;
	while (i++ < e.game.board->nb_players)
		ret = ft_new_player(ret);
	return (ret);
}
