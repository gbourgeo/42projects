/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 17:06:41 by root              #+#    #+#             */
/*   Updated: 2018/09/08 17:15:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemipc.h"

static t_player	*ft_new_player(t_ipc *ipc)
{
	t_player	*ret;

	if ((ret = malloc(sizeof(*ret))) == NULL)
	{
		ft_exit_client(1, "malloc", ipc);
		return (NULL);
	}
	ft_memset(ret, 0, sizeof(*ret));
	return (ret);
}

t_player		*ft_create_players_list(t_ipc *ipc)
{
	t_player	*ret;
	t_player	*ptr;
	ULL			i;

	ret = NULL;
	i = 0;
	while (i < ipc->board->players - 1)
	{
		if (!ret)
		{
			ret = ft_new_player(ipc);
			ptr = ret;
		}
		else
			ptr->next = ft_new_player(ipc);
		i++;
	}
	return (ret);
}
