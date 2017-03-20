/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:54:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 10:40:11 by gbourgeo         ###   ########.fr       */
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

static void		sv_info_next(t_fd *user, t_listin *info, t_fd *cl)
{
	char		**tmp;

	if (user->reg.umode & USR_OP || user->reg.umode & USR_LOCALOP)
		send(cl->fd, "*", 1, 0);
	if (info && info->mode & CHFL_CHANOP)
		send(cl->fd, "@", 1, 0);
	if (info && info->mode & CHFL_VOICE)
		send(cl->fd, "+", 1, 0);
	send(cl->fd, " :0", 3, 0);
	tmp = user->reg.realname;
	while (tmp && *tmp)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, *tmp, ft_strlen(*tmp), 0);
		tmp++;
	}
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_who_info(t_fd *user, t_listin *info, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 352 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (user->chans)
		send(cl->fd, ((t_chan *)user->chans->is)->name, CHANNAME_LEN, 0);
	else
		send(cl->fd, "*", 1, 0);
	send(cl->fd, " ~", 2, 0);
	send(cl->fd, user->reg.username, USERNAME_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->addr, ADDR_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (user->reg.umode & USR_AWAY)
		send(cl->fd, "G", 1, 0);
	else
		send(cl->fd, "H", 1, 0);
	sv_info_next(user, info, cl);
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

static void		sv_who_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*user;

	user = e->fds;
	while (user)
	{
		if (!ft_strcmp(cmds[1], "0"))
		{
			if (user->fd != cl->fd && !(user->reg.umode & USR_INVISIBL) &&
				!have_common_channel(user, cl))
				sv_who_info(user, user->chans, cl, e);
		}
		else if (!sv_strcmp(user->addr, cmds[1]) ||
				!sv_tabcmp(user->reg.realname, &cmds[1]) ||
				!sv_strcmp(user->reg.nick, cmds[1]))
			sv_who_info(user, user->chans, cl, e);
		user = user->next;
	}
	sv_who_end(*cmds, cl, e);
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
					sv_who_info(list->is, ((t_fd *)list->is)->chans, cl, e);
				list = list->next;
			}
		}
		chan = chan->next;
	}
	sv_who_end(*cmds, cl, e);
}

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, "WHO", NULL, cl));
	if (ISCHAN(*cmds[1]))
		sv_who_chan(cmds + 1, cl, e);
	else
		sv_who_user(cmds + 1, cl, e);
}
