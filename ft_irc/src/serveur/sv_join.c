/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:26:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 19:59:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static t_chan	*sv_new_chan(char *name, t_env *e, t_fd *cl)
{
	t_chan		*new;
	t_chan		*tmp;

	if ((new = (t_chan*)malloc(sizeof(*new))) == NULL)
		return (NULL);
	ft_memset(new, 0, sizeof(*new));
	ft_strncpy(new->name, name, CHAN_SIZE);
	new->nbusers = 1;
	new->user = cl->user;
	tmp = e->chan;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (new);
}

static t_chan	*sv_join_chan(char *name, t_env *e, t_fd *cl)
{
	t_chan		*tmp;

	tmp = e->chan;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, CHAN_SIZE))
		{
			tmp->nbusers++;
			tmp->user = sv_add_chan_user(tmp, cl->user);
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = sv_new_chan(name, e, cl);
	if (tmp != NULL)
		cl->flags |= CHFL_CHANOP;
	return (tmp);
}

void			sv_join(char **cmds, t_env *e, t_fd *cl)
{
	char		*s;

	s = cmds[1];
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(cmds[0], ":Not enough parameters", cl->fd));
	while (*s)
	{
		if (*s == 7 || *s == 10 || *s == 13 || *s == ',' || *s == ':')
			*s = '\0';
		else
			s++;
	}
	if (!ISCHAN(*cmds[1]))
		return (sv_err(cmds[1], ":No such channel", cl->fd));
	if (cl->chan && !ft_strncmp(cmds[1], cl->chan->name, CHAN_SIZE))
		return ;
	if (cl->chan)
	{
		sv_sendto_chan_msg(" :leaved the channel.", cl);
		sv_leave_chan(e, cl);
	}
	if ((cl->chan = sv_join_chan(cmds[1], e, cl)) == NULL)
		return (sv_err("SERVER", ":Out of memory.", cl->fd));
	if (cl->chan->nbusers > 1)
		sv_sendto_chan_msg(" :joined the channel.", cl);
	sv_sendto_chan_new(cl);
}
