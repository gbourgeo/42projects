/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_change_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 05:43:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 07:36:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.H"

static t_fd			*did_user_exist(char *nick, t_env *e)
{
	t_fd			*fd;

	fd = e->fds;
	while (fd)
	{
		if (!sv_strcmp(fd->reg.nick, nick))
			break ;
		fd = fd->next;
	}
	return (fd);
}

static t_listin		*search_user(char *nick, t_chan *chan)
{
	t_listin		*list;

	list = chan->users;
	while (list)
	{
		if (!sv_strcmp(((t_fd *)list->is)->reg.nick, nick))
			break ;
		list = list->next;
	}
	return (list);
}

static void			sv_sendtochan(char m, t_grp *grp, t_chan *ch, t_fd *cl)
{
	t_listin		*users;

	users = ch->users;
	while (users)
	{
		send(cl->fd, ":", 1, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		send(cl->fd, "!~", 2, 0);
		send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
		send(cl->fd, "@", 1, 0);
		send(cl->fd, cl->addr, ADDR_LEN, 0);
		send(cl->fd, " MODE ", 6, 0);
		send(cl->fd, ch->name, CHAN_LEN, 0);
		send(cl->fd, (grp->c) ? " :+" : " :-", 3, 0);
		send(cl->fd, &m, 1, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, ((t_fd *)grp->list->is)->reg.nick, NICK_LEN, 0);
		send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
		users = users->next;
	}
}

void				usermode_on(char m, char ***cmd, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;
	t_fd			*us;
	t_grp			grp;

	tmp = ft_strchr(CHAN_MODES, m);
	if (*(*cmd + 1) == NULL)
		return ;
	(*cmd)++;
	if ((us = did_user_exist(**cmd, &e)) == NULL)
		return (sv_err(ERR_NOSUCHNICK, **cmd, NULL, cl));
	if ((grp.list = search_user(**cmd, ch)) == NULL)
		return (sv_err(ERR_USERSDONTMATCH, **cmd, ch->name, cl));
	grp.list->mode |= chan_nbr[tmp - CHAN_MODES];
	grp.c = 1;
	sv_sendtochan(m, &grp, ch, cl);
}

void				usermode_off(char m, char ***cmd, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;
	t_fd			*us;
	t_grp			grp;

	tmp = ft_strchr(CHAN_MODES, m);
	if (*(*cmd + 1) == NULL)
		return ;
	(*cmd)++;
	if ((us = did_user_exist(**cmd, &e)) == NULL)
		return (sv_err(ERR_NOSUCHNICK, **cmd, NULL, cl));
	if ((grp.list = search_user(**cmd, ch)) == NULL)
		return (sv_err(ERR_USERSDONTMATCH, **cmd, ch->name, cl));
	grp.list->mode &= ~(chan_nbr[tmp - CHAN_MODES]);
	grp.c = 0;
	sv_sendtochan(m, &grp, ch, cl);
}
