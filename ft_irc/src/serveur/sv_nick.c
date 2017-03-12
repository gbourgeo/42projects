/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:22:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

int			sv_check_name_valid(char **cmds)
{
	char		*tmp;

	if (!cmds[0])
		return (1);
	if (ft_isalpha(*cmds[0]) || ISSPECIAL(*cmds[0]))
	{
		tmp = cmds[0] + 1;
		while (*tmp && tmp - cmds[0] < NICK_LEN)
		{
			if (ft_isalpha(*tmp) || ft_isdigit(*tmp) || ISSPECIAL(*tmp) || *tmp == '-')
				tmp++;
			else
				return (2);
		}
		*tmp = '\0';
		return (0);
	}
	return (2);
}

static int		is_registered_nick(char *nick, t_env *e)
{
	t_file		*f;

	f = e->users;
	while (f)
	{
		if (!ft_strncmp(f->login, nick, NICK_LEN))
			return (1);
		f = f->next;
	}
	return (0);
}

void			sv_nick(char **cmds, t_env *e, t_fd *cl)
{
	int			err;
	t_user		*us;

	err = sv_check_name_valid(cmds + 1);
	if (err == 1)
		return (sv_err(cmds[0], ":No nickname given", cl->fd));
	if (err == 2)
		return (sv_err(cmds[1], ":Erroneus Nickname", cl->fd));
	if (is_registered_nick(cmds[1], e))
		return (sv_err(cmds[1], ":Nick already in use", cl->fd));
	if (cl->chan)
	{
		us = cl->chan->user;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd &&
				!ft_strncmp(cmds[1], ((t_fd *)us->is)->nick, NICK_LEN))
				return (sv_err(cmds[1], ":Nick already in use", cl->fd));
			us = us->next;
		}
	}
	if (++cl->wr.head == cl->wr.end)
		cl->wr.head = cl->wr.start;
	sv_sendto_chan(cl);
	ft_strncpy(cl->nick, cmds[1], NICK_LEN);
}
