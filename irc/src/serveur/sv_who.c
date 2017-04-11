/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:54:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:38:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		have_common_chan(t_fd *to, t_fd *cl)
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

static void		sv_who_all(t_fd *cl, t_env *e)
{
	t_fd		*all;

	all = e->fds;
	while (all)
	{
		if (!(all->inf->umode & USR_INVISIBL) || all->i.fd == cl->i.fd ||
			have_common_chan(all, cl))
			sv_who_info(all, cl, e);
		all = all->next;
	}
}

void			sv_who_chan(char **cmds, t_fd *cl, t_env *e)
{
	t_chan		*chan;
	t_listin	*list;
	t_fd		*fd;

	if (!(chan = find_chan(cmds[0], e->chans)) ||
		((chan->cmode & CHFL_SECRET || chan->cmode & CHFL_PRIV) &&
		!is_chan_member(chan, cl)))
		return ;
	list = chan->users;
	while (list)
	{
		fd = (t_fd *)list->is;
		if ((!(chan->cmode & CHFL_ANON) || fd->i.fd == cl->i.fd) &&
			(!(fd->inf->umode & USR_INVISIBL) || have_common_chan(fd, cl)) &&
			(!cmds[1] || ft_strcmp(cmds[1], "o") || list->mode & CHFL_CHANOP))
			sv_who_info(fd, cl, e);
		list = list->next;
	}
}

static void		sv_who_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*all;

	all = e->fds;
	while (all)
	{
		if ((!ft_strcmp(cmds[0], "0") ||
			!sv_strncmp(all->i.addr, cmds[0], ADDR_LEN) ||
			!sv_tabcmp(all->inf->realname, cmds) ||
			!sv_strncmp(all->inf->nick, cmds[0], NICK_LEN)) &&
			(!(all->inf->umode & USR_INVISIBL) ||
			have_common_chan(all, cl)) &&
			(!cmds[1] || ft_strcmp(cmds[1], "o") ||
			all->inf->umode & USR_OP || all->inf->umode & USR_LOCALOP))
			sv_who_info(all, cl, e);
		all = all->next;
	}
}

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[0] || !*cmds[0])
		sv_who_all(cl, e);
	else if (ISCHAN(*cmds[0]))
		sv_who_chan(cmds, cl, e);
	else
		sv_who_user(cmds, cl, e);
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 315 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	if (*cmds)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(*cmds, cl);
	}
	sv_cl_write(" :End of /WHO list.", cl);
	sv_cl_write(END_CHECK, cl);
}
