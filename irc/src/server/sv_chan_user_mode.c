/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan_user_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 05:43:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/05 00:15:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static t_fd			*did_user_exist(char *nick, t_env *e)
{
	t_fd			*fd;

	fd = e->fds;
	while (fd)
	{
		if (!sv_strcmp(fd->inf->nick, nick))
			break ;
		fd = fd->next;
	}
	return (fd);
}

static t_listin		*search_user(t_fd *us, t_chan *chan)
{
	t_listin		*list;

	list = chan->users;
	while (list)
	{
		if (((t_fd *)list->is)->i.fd == us->i.fd)
			break ;
		list = list->next;
	}
	return (list);
}

static t_listin		*search_channel(t_fd *us, t_chan *ch)
{
	t_listin		*list;

	list = us->chans;
	while (list)
	{
		if (!sv_strcmp(((t_chan *)list->is)->name, ch->name))
			break ;
		list = list->next;
	}
	return (list);
}

static void			sv_sendtochan(t_grp *grp, t_chan *chan, t_fd *cl)
{
	t_listin		*users;
	t_fd			*to;

	users = chan->users;
	while (users)
	{
		to = (t_fd *)users->is;
		rpl_umode(grp, chan, to, cl);
		users = users->next;
	}
}

void				sv_chan_user_mode(t_grp *grp, char ***cmd)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	t_listin		*ch;
	char			*tmp;

	if (*(*cmd + 1) == NULL)
		return ;
	tmp = ft_strchr(CHAN_MODES, *grp->ptr);
	(*cmd)++;
	if ((grp->to = did_user_exist(**cmd, &e)) == NULL)
		return (sv_err(ERR_NOSUCHNICK, **cmd, NULL, grp->from));
	if ((grp->list = search_user(grp->to, grp->on)) == NULL)
		return (sv_err(ERR_USERSDONTMATCH, **cmd, grp->on->name, grp->from));
	ch = search_channel(grp->list->is, grp->on);
	if (grp->c)
	{
		grp->list->mode |= chan_nbr[tmp - CHAN_MODES];
		ch->mode |= chan_nbr[tmp - CHAN_MODES];
	}
	else
	{
		grp->list->mode &= ~(chan_nbr[tmp - CHAN_MODES]);
		ch->mode &= ~(chan_nbr[tmp - CHAN_MODES]);
	}
	sv_sendtochan(grp, grp->on, grp->from);
}
