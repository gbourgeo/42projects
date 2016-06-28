/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 15:37:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_leave_chan(t_env *e, size_t i)
{
	t_chan		*tmp;

	tmp = e->chan;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, e->fds[i].chan))
		{
			tmp->users--;
			if (tmp->users == 0)
				return (sv_remove_chan(tmp->name, e));
			sv_send_msg(" \e[33mleaved the channel.\e[0m\n", e, i);
			return ;
		}
		tmp = tmp->next;
	}
}

void			sv_remove_chan(char *name, t_env *e)
{
	t_chan		*tmp;
	t_chan		*stock;

	tmp = e->chan;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->name, name))
		{
			stock = tmp->next->next;
			ft_memset(tmp->next, 0, sizeof(*tmp));
			free(tmp->next);
			tmp->next = stock;
			return ;
		}
		tmp = tmp->next;
	}
}
