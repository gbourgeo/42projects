/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 04:23:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

int				sv_check_name_valid(char **cmds)
{
	char		*tmp;

	if (!cmds[1] || !*cmds[1])
		return (1);
	if (!sv_strcmp(cmds[1], "anonymous"))
		return (2);
	if (ft_isalpha(*cmds[1]) || ISSPECIAL(*cmds[1]))
	{
		tmp = cmds[1] + 1;
		while (*tmp && tmp - cmds[1] < NICK_LEN)
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

static int		is_registered_nick(char *nick, t_fd *cl, t_env *e)
{
	t_file		*f;
	t_fd		*fds;

	f = e->users;
	while (f)
	{
		if (!sv_strncmp(f->nick, nick, NICK_LEN))
			return (1);
		f = f->next;
	}
	fds = e->fds;
	while (fds)
	{
		if (fds->fd != cl->fd && !sv_strncmp(nick, fds->reg.nick, NICK_LEN))
			return (1);
		fds = fds->next;
	}
	return (0);
}

static void		send_newnick(char *newnick, t_fd *cl, t_env *e)
{
	t_fd		*other;
	int			len;

	other = e->fds;
	len = ft_strlen(newnick);
	while (other)
	{
		send(cl->fd, ":", 1, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		send(cl->fd, "!~", 2, 0);
		send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
		send(cl->fd, "@", 1, 0);
		send(cl->fd, cl->addr, ADDR_LEN, 0);
		send(cl->fd, " NICK :", 7, 0);
		if (len > NICK_LEN)
			send(cl->fd, newnick, NICK_LEN, 0);
		else
			send(cl->fd, newnick, len, 0);
		send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	}
	ft_strncpy(cl->reg.nick, newnick, NICK_LEN);
}

void			sv_nick(char **cmds, t_env *e, t_fd *cl)
{
	int			err;

	err = sv_check_name_valid(cmds);
	if (err == 1)
		return (sv_err(ERR_NONICKNAMEGIVEN, "NICK", NULL, cl, e));
	if (err == 2)
		return (sv_err(ERR_ERRONEUSNICKNAME, cmds[1], NULL, cl, e));
	if (is_registered_nick(cmds[1], cl, e))
		return (sv_err(ERR_NICKNAMEINUSE, cmds[1], NULL, cl, e));
	if (cl->reg.umode & USR_RESTRICT)
		return (sv_err(ERR_RESTRICTED, NULL, NULL, cl, e));
	if (cl->reg.registered == 0 && cl->reg.realname && *cl->reg.realname)
	{
		ft_strncpy(cl->reg.nick, cmds[1], NICK_LEN);
		sv_welcome(e, cl);
	}
	else if (sv_strcmp(cl->reg.nick, cmds[1]))
		send_newnick(cmds[1], cl, e);
}
