/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_channel_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:20:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:21:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			sv_send_channel(t_grp *grp, int limit)
{
	t_listin		*list;

	list = grp->on->users;
	while (list)
	{
		grp->to = (t_fd *)list->is;
		rpl_cmode(grp, (limit) ? ft_itoa(grp->on->limit) : NULL);
		list = list->next;
	}
}

static void			sv_change_more(t_grp *grp, char ***cmd)
{
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
				return (sv_send_channel(grp, 1));
		}
		else if (*grp->ptr == 'k')
			ft_strncpy(grp->on->key, **cmd, CHANKEY_LEN);
	}
	sv_send_channel(grp, 0);
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
	sv_send_channel(grp, 0);
}

static void			sv_get_mode(t_grp *grp, char **cmd)
{
	grp->c = 1;
	grp->ptr = *cmd;
	grp->mdr[1] = 0;
	while (*grp->ptr)
	{
		grp->mdr[0] = *grp->ptr;
		if (*grp->ptr == '+')
			grp->c = 1;
		else if (*grp->ptr == '-')
			grp->c = 0;
		else if (!ft_strchr(CHAN_MODES, *grp->ptr))
			sv_err(ERR_UNKNOWNMODE, grp->mdr, grp->on->name, grp->from);
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
		if (((t_fd *)grp.list->is)->i.fd == cl->i.fd)
			break ;
		grp.list = grp.list->next;
	}
	if (grp.list == NULL)
		return (sv_err(ERR_USERNOTINCHANNEL, cl->inf->nick, ch->name, cl));
	if (!(grp.list->mode & CHFL_CREATOR) && !(grp.list->mode & CHFL_CHANOP))
		return (sv_err(ERR_CHANOPRIVSNEEDED, ch->name, NULL, cl));
	grp.from = cl;
	grp.on = ch;
	grp.to = NULL;
	sv_get_mode(&grp, cmds);
}
