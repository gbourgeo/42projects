/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:26:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/26 18:42:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		add_chan(char *name, t_env *e)
{
	t_chan		*new;
	t_chan		*tmp;

	if ((new = (t_chan*)malloc(sizeof(*new))) == NULL)
		return ;
	ft_strncpy(new->name, name, CHAN_SIZE);
	new->users = 1;
	new->next = NULL;
	tmp = e->chan;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void		sv_join_chan(char *name, t_env *e)
{
	t_chan		*tmp;

	tmp = e->chan;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp->users++;
			return ;
		}
		tmp = tmp->next;
	}
	add_chan(name, e);
}

void			sv_join(char **cmds, t_env *e, size_t i)
{
	if (!cmds[1])
		send(e->fds[i].fd, "\e[31mNot enought argument\n\e[0m", 31, 0);
	else
	{
		sv_leave_chan(e, i);
		sv_join_chan(cmds[1], e);
		ft_strncpy(e->fds[i].chan, cmds[1], CHAN_SIZE);
		send(e->fds[i].fd, "\e[33mYou joined [\e[0m", 21, 0);
		send(e->fds[i].fd, e->fds[i].chan, CHAN_SIZE, 0);
		send(e->fds[i].fd, "\e[33m]\e[0m\n", 11, 0);
	}
}
