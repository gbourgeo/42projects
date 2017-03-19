/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_channel_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:20:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 07:36:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			change_chan_mode(char c, char mode, t_chan *ch, t_fd *cl)
{
	static int		chan_nbr[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*tmp;

	tmp = ft_strchr(CHAN_MODES, mode);
	if ((c && ch->cmode & chan_nbr[tmp - CHAN_MODES]) ||
		(!c && !(ch->cmode & chan_nbr[tmp - CHAN_MODES])))
		return ;
	if (c)
		ch->cmode |= chan_nbr[tmp - CHAN_MODES];
	else
		ch->cmode &= ~(chan_nbr[tmp - CHAN_MODES]);
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, ch->name, CHAN_LEN, 0);
	send(cl->fd, (c) ? " +" : " -", 2, 0);
	send(cl->fd, &mode, 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void			check_channel_mode(char **cmds, t_chan *ch, t_fd *cl)
{
	char			*ptr;
	char			c;

	c = 1;
	ptr = *cmds;
	while (*ptr)
	{
		if (*ptr == '+')
			c = 1;
		else if (*ptr == '-')
			c = 0;
		else if (!ft_strchr(CHAN_MODES, *ptr))
			return (sv_err(ERR_UNKNOWNMODE, ptr, ch->name, cl));
		else if (*ptr == 'o' || *ptr == 'v')
		{
			if (c)
				usermode_on(*ptr, &cmds, ch, cl);
			else
				usermode_off(*ptr, &cmds, ch, cl);
		}
		else if (*ptr != 'O')
			change_chan_mode(c, *ptr, ch, cl);
		ptr++;
	}
}

void				sv_channel_mode(char **cmds, t_chan *ch, t_fd *cl)
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
