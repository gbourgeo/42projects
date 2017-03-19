/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_change_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 05:43:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 05:49:41 by gbourgeo         ###   ########.fr       */
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

void				usermode_on(char m, char ***cmd, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;
	t_fd			*us;
	t_listin		*list;

	tmp = ft_strchr(CHAN_MODES, m);
	if (*(*cmd + 1) == NULL)
		return ;
	(*cmd)++;
	if ((us = did_user_exist(**cmd, &e)) == NULL)
		return (sv_err(ERR_NOSUCHNICK, **cmd, NULL, cl));
	if ((list = search_user(**cmd, ch)) == NULL)
		return (sv_err(ERR_USERSDONTMATCH, **cmd, ch->name, cl));
	list->mode |= chan_nbr[tmp - CHAN_MODES];
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, ch->name, CHAN_LEN, 0);
	send(cl->fd, " :+", 3, 0);
	send(cl->fd, &m, 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, ((t_fd *)list->is)->reg.nick, NICK_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

void				usermode_off(char m, char ***cmd, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;
	t_fd			*us;
	t_listin		*list;

	tmp = ft_strchr(CHAN_MODES, m);
	if (*(*cmd + 1) == NULL)
		return ;
	(*cmd)++;
	if ((us = did_user_exist(**cmd, &e)) == NULL)
		return (sv_err(ERR_NOSUCHNICK, **cmd, NULL, cl));
	if ((list = search_user(**cmd, ch)) == NULL)
		return (sv_err(ERR_USERSDONTMATCH, **cmd, ch->name, cl));
	list->mode &= ~(chan_nbr[tmp - CHAN_MODES]);
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, ch->name, CHAN_LEN, 0);
	send(cl->fd, " :-", 3, 0);
	send(cl->fd, &m, 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, ((t_fd *)list->is)->reg.nick, NICK_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}
