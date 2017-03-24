/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:54:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 20:24:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_who_end(char *cmd, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, &cl->wr);
	sv_cl_write(" 315 ", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(cmd, &cl->wr);
	sv_cl_write(" :End of /WHO list.", &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
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
	t_fd		*fd;

	chan = e->chans;
	while (chan)
	{
		if (!sv_strcmp(chan->name, cmds[0]))
		{
			list = chan->users;
			while (list && !(chan->cmode & CHFL_SECRET))
			{
				fd = (t_fd *)list->is;
				if (chan->cmode & CHFL_ANON && fd->fd != cl->fd)
					continue ;
				if ((!cmds[1] &&
					(!(fd->reg.umode & USR_INVISIBL) || is_modo(chan, cl))) ||
					ft_strcmp(cmds[1], "o") || list->mode & CHFL_CHANOP)
					sv_who_info(fd, cl, e);
				list = list->next;
			}
			return ;
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
				sv_who_info(user, cl, e);
		}
		else if (!sv_strncmp(user->addr, cmds[0], ADDR_LEN) ||
				!sv_tabcmp(user->reg.realname, &cmds[0]) ||
				!sv_strncmp(user->reg.nick, cmds[0], NICK_LEN))
			return (sv_who_info(user, cl, e));
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
	rpl_who_end(*cmds, cl, e);
}
