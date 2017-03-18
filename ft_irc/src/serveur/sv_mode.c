/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 05:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 00:22:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			change_chan_mode(char c, char mode, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;

	tmp = ft_strchr(CHAN_MODES, mode);
	if (c)
		ch->cmode |= chan_nbr[tmp - CHAN_MODES];
	else
		ch->cmode &= ~(chan_nbr[tmp - CHAN_MODES]);
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, ch->name, CHAN_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, (c) ? "+" : "-", 1, 0);
	send(cl->fd, &mode, 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void			check_channel_mode(char **cmds, t_chan *ch, t_fd *cl)
{
	char			*ptr;
	char			c;

	c = 1;
	while (*cmds)
	{
		ptr = *cmds;
		while (*ptr)
		{
			if (*ptr == '+')
				c = 1;
			else if (*ptr == '-')
				c = 0;
			else if (!ft_strchr(CHAN_MODES, *ptr))
				return (sv_err(ERR_UNKNOWNMODE, ptr, ch->name, cl));
			else
				change_chan_mode(c, *ptr, ch, cl);
			ptr++;
		}
		cmds++;
	}	
}

static void			channel_mode(char **cmds, t_chan *ch, t_fd *cl)
{
	t_listin		*list;

	if (*ch->name == '+')
		return (sv_err(ERR_NOCHANMODES, ch->name, NULL, cl));
	list = ch->users;
	while (list)
	{
		if (((t_fd *)list->is)->fd == cl->fd)
			break ;
		list = list->next;
	}
	if (list == NULL)
		return (sv_err(ERR_USERNOTINCHANNEL, cl->reg.nick, ch->name, cl));
	if (!(list->mode & CHFL_CREATOR) && !(list->mode & CHFL_CHANOP))
		return (sv_err(ERR_CHANOPRIVSNEEDED, ch->name, NULL, cl));
	check_channel_mode(cmds, ch, cl);
}

static void			change_user_mode(char c, char mode, t_fd *us, t_fd *cl)
{
	static int		user_nbr[] = { US_MODS1, US_MODS2 };
	char			*tmp;

	tmp = ft_strchr(USER_MODES, mode);
	if (c && (mode == 'O' || mode == 'o'))
		return ;
	if (!c && mode == 'r')
		return ;
	if (c)
		us->reg.umode |= user_nbr[tmp - USER_MODES];
	else
		us->reg.umode &= ~(user_nbr[tmp - USER_MODES]);
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, us->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, (c) ? "+" : "-", 1, 0);
	send(cl->fd, &mode, 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void			user_mode(char **cmds, t_fd *us, t_fd *cl)
{
	char			*ptr;
	char			c;

	c = 1;
	if (us->fd != cl->fd)
		return (sv_err(ERR_USERSDONTMATCH, NULL, NULL, cl));
	while (*cmds)
	{
		ptr = *cmds;
		while (*ptr)
		{
			if (*ptr == '+')
				c = 1;
			else if (*ptr == '-')
				c = 0;
			else if (!ft_strchr(USER_MODES, *ptr))
				return (sv_err(ERR_UMODEUNKNOWNFLAG, NULL, NULL, cl));
			else
				change_user_mode(c, *ptr, us, cl);
			ptr++;
		}
		cmds++;
	}
}

void				sv_mode(char **cmds, t_env *e, t_fd *cl)
{
	t_chan			*ch;
	t_fd			*us;

	(void)e;
	if (!cmds[1] || !cmds[2])
		return (sv_err(ERR_NEEDMOREPARAMS, "MODE", NULL, cl));
	ch = e->chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, cmds[1]))
			return (channel_mode(cmds + 2, ch, cl));
		ch = ch->next;
	}
	us = e->fds;
	while (us)
	{
		if (!sv_strcmp(us->reg.nick, cmds[1]))
			return (user_mode(cmds + 2, us, cl));
		us = us->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, cmds[1], NULL, cl);
}
