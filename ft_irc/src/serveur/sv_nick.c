/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 19:40:54 by gbourgeo         ###   ########.fr       */
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

static void		send_to_chans(t_fd *cl)
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
					sv_cl_send_to(us->is, &cl->wr);
				us = us->next;
			}
		}
		ch = ch->next;
	}
}

static void		rpl_nick(char *nick, t_fd *cl)
{
	sv_cl_write(":", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write("!~", &cl->wr);
	sv_cl_write(cl->reg.username, &cl->wr);
	sv_cl_write("@", &cl->wr);
	sv_cl_write(cl->addr, &cl->wr);
	sv_cl_write(" NICK :", &cl->wr);
	sv_cl_write(nick, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
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
		rpl_nick(*cmds, cl);
		send_to_chans(cl);
		sv_cl_send_to(cl, &cl->wr);
		cl->wr.head = cl->wr.tail;
		ft_strncpy(cl->reg.nick, *cmds, NICK_LEN);
	}
}
