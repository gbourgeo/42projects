/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 16:01:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

int			sv_check_name_valid(char **cmds)
{
	char		*tmp;

	if (!cmds[0] || !*cmds[0])
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
		return (0);
	}
	return (2);
}

static int		is_registered_nick(char *nick, t_fd *cl, t_env *e)
{
	t_file		*f;
	t_fd		*fds;

	f = e->users;
	while (f)
	{
		if (!ft_strncmp(f->nick, nick, NICK_LEN))
			return (1);
		f = f->next;
	}
	fds = e->fds;
	while (fds)
	{
		if (fds->fd != cl->fd && !ft_strncmp(nick, fds->reg.nick, NICK_LEN))
			return (1);
		fds = fds->next;
	}
	return (0);
}

void			sv_nick(char **cmds, t_env *e, t_fd *cl)
{
	int			err;

	err = sv_check_name_valid(cmds + 1);
	if (err == 1)
		return (sv_err(" ", cmds[0], ":No nickname given", cl, e));
	if (err == 2)
		return (sv_err(" ", cmds[1], ":Erroneus Nickname", cl, e));
	if (is_registered_nick(cmds[1], cl, e))
		return (sv_err(" ", cmds[1], ":Nick already in use", cl, e));
/* 	if (++cl->wr.head == cl->wr.end) */
/* 		cl->wr.head = cl->wr.start; */
/* 	sv_sendto_chan(cl); */
	ft_strncpy(cl->reg.nick, cmds[1], NICK_LEN);
	if (cl->reg.registered == 0 && *cl->reg.username && cl->reg.realname)
		sv_welcome(e, cl);
}
