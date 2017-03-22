/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:19:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

int				sv_check_name_valid(char *name)
{
	char		*tmp;

	if (!name || !*name)
		return (1);
	if (!sv_strcmp(name, "anonymous"))
		return (2);
	if (ft_isalpha(*name) || ISSPECIAL(*name))
	{
		tmp = name + 1;
		while (*tmp && tmp - name < NICK_LEN)
		{
			if (ft_isalpha(*tmp) || ft_isdigit(*tmp) || ISSPECIAL(*tmp) ||
				*tmp == '-')
				tmp++;
			else
				return (2);
		}
		return (0);
	}
	return (2);
}

static int		is_connected_nick(char *nick, t_fd *cl, t_env *e)
{
	t_file		*us;
	t_fd		*fds;

	fds = e->fds;
	while (fds)
	{
		if (fds->fd != cl->fd && !sv_strncmp(nick, fds->reg.nick, NICK_LEN))
			return (1);
		fds = fds->next;
	}
	us = e->users;
	while (cl->reg.registered > 0 && us)
	{
		if (!sv_strncmp(nick, us->nick, NICK_LEN))
			return (1);
		us = us->next;
	}
	return (0);
}

static void		send_to(char *nick, int len, t_fd *to, t_fd *cl)
{
	send(to->fd, ":", 1, 0);
	send(to->fd, cl->reg.nick, NICK_LEN, 0);
	send(to->fd, "!~", 2, 0);
	send(to->fd, cl->reg.username, USERNAME_LEN, 0);
	send(to->fd, "@", 1, 0);
	send(to->fd, cl->addr, ADDR_LEN, 0);
	send(to->fd, " NICK :", 7, 0);
	send(to->fd, nick, (len > NICK_LEN) ? NICK_LEN : len, 0);
	send(to->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		send_newnick(char *nick, int len, t_fd *cl)
{
	t_listin	*ch;
	t_listin	*us;

	ch = cl->chans;
	while (ch)
	{
		if (!(((t_chan *)ch->is)->cmode & CHFL_QUIET))
		{
			us = ((t_chan *)ch->is)->users;
			while (us)
			{
				if (((t_fd *)us->is)->fd != cl->fd)
					send_to(nick, len, us->is, cl);
				us = us->next;
			}
		}
		ch = ch->next;
	}
}

void			sv_nick(char **cmds, t_env *e, t_fd *cl)
{
	int			err;

	err = sv_check_name_valid(*cmds);
	if (err == 1)
		return (sv_err(ERR_NONICKNAMEGIVEN, "NICK", NULL, cl));
	if (err == 2)
		return (sv_err(ERR_ERRONEUSNICKNAME, *cmds, NULL, cl));
	if (is_connected_nick(*cmds, cl, e))
		return (sv_err(ERR_NICKNAMEINUSE, *cmds, NULL, cl));
	if (cl->reg.umode & USR_RESTRICT)
		return (sv_err(ERR_RESTRICTED, NULL, NULL, cl));
	if (cl->reg.registered <= 0)
		ft_strncpy(cl->reg.nick, *cmds, NICK_LEN);
	else if (sv_strcmp(cl->reg.nick, *cmds))
	{
		err = ft_strlen(*cmds);
		send_to(*cmds, err, cl, cl);
		send_newnick(*cmds, err, cl);
		ft_strncpy(cl->reg.nick, *cmds, NICK_LEN);
	}
}
