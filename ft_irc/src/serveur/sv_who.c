/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:54:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:35:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_who_end(char *cmd, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 315 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cmd, ft_strlen(cmd), 0);
	send(cl->fd, " :End of /WHO list.", 19, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static int		have_common_channel(t_fd *to, t_fd *cl)
{
	t_listin	*lo;
	t_listin	*lc;

	if (to->chans == NULL || cl->chans == NULL)
		return (0);
	lc = cl->chans;
	while (lc)
	{
		lo = to->chans;
		while (lo)
		{
			if (!sv_strcmp(((t_chan *)lo->is)->name, ((t_chan *)lc->is)->name))
				return (1);
			lo = lo->next;
		}
		lc = lc->next;
	}
	return (0);
}

void			sv_who_chan(char **cmds, t_fd *cl, t_env *e)
{
	t_chan		*chan;
	t_listin	*list;

	chan = e->chans;
	while (chan)
	{
		if (!sv_strcmp(chan->name, cmds[0]))
		{
			if (chan->cmode & CHFL_SECRET)
				return ;
			list = chan->users;
			while (list)
			{
				if (chan->cmode & CHFL_ANON && ((t_fd *)list->is)->fd != cl->fd)
					continue ;
				if (!cmds[1] || ft_strcmp(cmds[2], "o") ||
					list->mode & CHFL_CHANOP)
					return (sv_who_info(list->is, ((t_fd *)list->is)->chans, cl, e));
				list = list->next;
			}
		}
		chan = chan->next;
	}
}

static void		sv_who_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*user;

	user = e->fds;
	while (user)
	{
		if (!ft_strcmp(cmds[0], "0"))
		{
			if (user->fd != cl->fd && !(user->reg.umode & USR_INVISIBL) &&
				!have_common_channel(user, cl))
				sv_who_info(user, user->chans, cl, e);
		}
		else if (!sv_strncmp(user->addr, cmds[0], ADDR_LEN) ||
				!sv_tabcmp(user->reg.realname, &cmds[0]) ||
				 !sv_strncmp(user->reg.nick, cmds[0], NICK_LEN))
			return (sv_who_info(user, user->chans, cl, e));
		user = user->next;
	}
}

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "WHO", NULL, cl));
	if (ISCHAN(*cmds[0]))
		sv_who_chan(cmds, cl, e);
	else
		sv_who_user(cmds, cl, e);
	sv_who_end(*cmds, cl, e);
}
