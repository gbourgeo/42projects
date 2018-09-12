/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 17:06:41 by root              #+#    #+#             */
/*   Updated: 2018/09/12 15:47:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemipc.h"

static t_player	*ft_new_player(void)
{
	t_player	*ret;

	if ((ret = malloc(sizeof(*ret))) == NULL)
	{
		ft_exit(1, "malloc");
		return (NULL);
	}
	ft_memset(ret, 0, sizeof(*ret));
	return (ret);
}

t_player		*ft_create_players_list(void)
{
	t_player	*ret;
	t_player	*ptr;
	ULL			i;

	ret = NULL;
	i = 0;
	while (i < e.game.board->nb_players - 1)
	{
		if (!ret)
		{
			ret = ft_new_player();
			ptr = ret;
		}
		else
			ptr->next = ft_new_player();
		i++;
	}
	return (ret);
}
