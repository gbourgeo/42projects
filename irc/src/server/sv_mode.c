/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 05:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 02:47:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			rpl_cmodeis(t_chan *ch, t_fd *cl, t_env *e)
{
	static int		cvalues[] = { CH_MODS1, CH_MODS2, CH_MODS3 };
	char			*cmodes;
	char			ptr[2];
	size_t			i;

	cmodes = CHAN_MODES;
	ptr[1] = 0;
	i = 0;
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 221 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :+", cl);
	while (i < ft_strlen(cmodes))
	{
		ptr[0] = cmodes[i];
		if (ch->cmode & cvalues[i])
			sv_cl_write(ptr, cl);
		i++;
	}
	sv_cl_write(END_CHECK, cl);
}

static void			search_channel(char **cmds, t_fd *cl, t_env *e)
{
	t_chan			*ch;

	ch = e->chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, *cmds))
		{
			if (!cmds[1])
				return (rpl_cmodeis(ch, cl, e));
			return (sv_channel_mode(cmds + 1, ch, cl));
		}
		ch = ch->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, *cmds, NULL, cl);
}

static void			rpl_umodeis(t_fd *cl, t_env *e)
{
	static int		uvalues[] = { US_MODS1, US_MODS2 };
	char			*umodes;
	char			ptr[2];
	size_t			i;

	umodes = USER_MODES;
	ptr[1] = 0;
	i = 0;
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 221 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :+", cl);
	while (i < ft_strlen(umodes))
	{
		ptr[0] = umodes[i];
		if (cl->inf->umode & uvalues[i])
			sv_cl_write(ptr, cl);
		i++;
	}
	sv_cl_write(END_CHECK, cl);
}

void				sv_mode(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[0])
		sv_err(ERR_NEEDMOREPARAMS, "MODE", NULL, cl);
	else if (cl->inf->umode & USR_RESTRICT)
		sv_err(ERR_RESTRICTED, NULL, NULL, cl);
	else if (ISCHAN(**cmds))
		search_channel(cmds, cl, e);
	else if (sv_strcmp(cl->inf->nick, *cmds))
		sv_err((cmds[1]) ? ERR_USERSDONTMATCH : ERR_USERSMODE, NULL, NULL, cl);
	else if (!cmds[1])
		rpl_umodeis(cl, e);
	else
		sv_user_mode(cmds + 1, cl);
}
