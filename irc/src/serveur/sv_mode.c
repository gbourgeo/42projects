/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 05:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:08:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			search_channel(char **cmds, t_fd *cl, t_env *e)
{
	t_chan			*ch;

	ch = e->chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, *cmds))
			return (sv_channel_mode(cmds + 1, ch, cl));
		ch = ch->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, *cmds, NULL, cl);
}

static void			search_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd			*us;

	us = e->fds;
	while (us)
	{
		if (!sv_strcmp(us->reg.nick, *cmds))
			return (sv_user_mode(cmds + 1, us, cl));
		us = us->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, *cmds, NULL, cl);
}

void				sv_mode(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[0] || !cmds[1])
		sv_err(ERR_NEEDMOREPARAMS, "MODE", NULL, cl);
	else if (cl->reg.umode & USR_RESTRICT)
		sv_err(ERR_RESTRICTED, NULL, NULL, cl);
	else if (ISCHAN(**cmds))
		search_channel(cmds, cl, e);
	else if (sv_strcmp(cl->reg.nick, *cmds))
		sv_err(ERR_USERSDONTMATCH, NULL, NULL, cl);
	else
		search_user(cmds, cl, e);
}
