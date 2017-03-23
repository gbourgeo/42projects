/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_channel_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:20:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 19:29:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			sv_send_channel(t_grp *grp, char *ptr, t_listin *list)
{
	t_fd			*us;

	list = grp->on->users;
	while (list)
	{
		us = (t_fd *)list->is;
		send(us->fd, ":", 1, 0);
		send(us->fd, grp->from->reg.nick, NICK_LEN, 0);
		send(us->fd, "!~", 1, 0);
		send(us->fd, grp->from->reg.username, USERNAME_LEN, 0);
		send(us->fd, "@", 1, 0);
		send(us->fd, grp->from->addr, ADDR_LEN, 0);
		send(us->fd, " MODE ", 6, 0);
		send(us->fd, grp->on->name, CHANNAME_LEN, 0);
		send(us->fd, (grp->c) ? " +" : " -", 2, 0);
		send(us->fd, grp->ptr, 1, 0);
		if ((*grp->ptr == 'l' || *grp->ptr == 'k') && grp->c)
		{
			send(us->fd, " ", 1, 0);
			send(us->fd, (*grp->ptr == 'l') ? ptr : grp->on->key,
				(*grp->ptr == 'l') ? ft_strlen(ptr) : CHANKEY_LEN, 0);
		}
		send(us->fd, END_CHECK, END_CHECK_LEN, 0);
		list = list->next;
	}
}

static void			sv_change_more(t_grp *grp, char ***cmd)
{
	char			*ptr;

	if (grp->c && *(*cmd + 1) == NULL)
		return ;
	if (!grp->c)
		grp->on->cmode &= (*grp->ptr == 'l') ? ~(CHFL_LIMIT) : ~(CHFL_KEY);
	else
	{
		grp->on->cmode |= (*grp->ptr == 'l') ? CHFL_LIMIT : CHFL_KEY;
		(*cmd)++;
		if (*grp->ptr == 'l')
		{
			if ((grp->on->limit = ft_atoi(**cmd)) > 0)
			{
				ptr = ft_itoa(grp->on->limit);
				sv_send_channel(grp, ptr, NULL);
				free(ptr);
				return ;
			}
		}
		else if (*grp->ptr == 'k')
			ft_strncpy(grp->on->key, **cmd, CHANKEY_LEN);
	}
	sv_send_channel(grp, NULL, NULL);
}

static void			sv_change_mode(t_grp *grp)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;

	tmp = ft_strchr(CHAN_MODES, *grp->ptr);
	if ((grp->c && grp->on->cmode & chan_nbr[tmp - CHAN_MODES]) ||
		(!grp->c && !(grp->on->cmode & chan_nbr[tmp - CHAN_MODES])) ||
		(grp->c && (*grp->ptr == 'p' && grp->on->cmode & CHFL_SECRET)) ||
		(grp->c && (*grp->ptr == 's' && grp->on->cmode & CHFL_PRIV)))
		return ;
	if (grp->c)
		grp->on->cmode |= chan_nbr[tmp - CHAN_MODES];
	else
		grp->on->cmode &= ~(chan_nbr[tmp - CHAN_MODES]);
	sv_send_channel(grp, NULL, NULL);
}

static void			sv_get_mode(t_grp *grp, char **cmd)
{
	char			c[2];

	grp->c = 1;
	grp->ptr = *cmd;
	c[1] = 0;
	while (*grp->ptr)
	{
		c[0] = *grp->ptr;
		if (*grp->ptr == '+')
			grp->c = 1;
		else if (*grp->ptr == '-')
			grp->c = 0;
		else if (!ft_strchr(CHAN_MODES, *grp->ptr))
			sv_err(ERR_UNKNOWNMODE, c, grp->on->name, grp->from);
		else if (*grp->ptr == 'o' || *grp->ptr == 'v')
			sv_chan_user_mode(grp, &cmd);
		else if (*grp->ptr == 'l' || *grp->ptr == 'k')
			sv_change_more(grp, &cmd);
		else if (*grp->ptr != 'O' &&
				(*grp->ptr != 'a' || *grp->on->name == '&' ||
				(*grp->on->name == '!' && grp->list->mode & CHFL_CREATOR)))
			sv_change_mode(grp);
		grp->ptr++;
	}
}

void				sv_channel_mode(char **cmds, t_chan *ch, t_fd *cl)
{
	t_grp			grp;

	if (*ch->name == '+')
		return (sv_err(ERR_NOCHANMODES, ch->name, NULL, cl));
	grp.list = ch->users;
	while (grp.list)
	{
		if (((t_fd *)grp.list->is)->fd == cl->fd)
			break ;
		grp.list = grp.list->next;
	}
	if (grp.list == NULL)
		return (sv_err(ERR_USERNOTINCHANNEL, cl->reg.nick, ch->name, cl));
	if (!(grp.list->mode & CHFL_CREATOR) && !(grp.list->mode & CHFL_CHANOP))
		return (sv_err(ERR_CHANOPRIVSNEEDED, ch->name, NULL, cl));
	grp.from = cl;
	grp.on = ch;
	grp.to = NULL;
	sv_get_mode(&grp, cmds);
}
