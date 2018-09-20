/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 17:06:41 by root              #+#    #+#             */
/*   Updated: 2018/09/20 02:05:30 by gbourgeo         ###   ########.fr       */
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
		ft_exit(1, "malloc");
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
