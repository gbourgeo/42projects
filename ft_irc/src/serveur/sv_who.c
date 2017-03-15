/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:54:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 02:36:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_who_info(t_fd *user, t_listin *info, t_fd *cl, t_env *e)
{
	char		**tmp;
	
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 352 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (user->chans)
		send(cl->fd, ((t_chan *)user->chans->is)->name, CHAN_LEN, 0);
	else
		send(cl->fd, "*", 1, 0);
	send(cl->fd, " ~", 2, 0);
	send(cl->fd, user->reg.username, USERNAME_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->addr, ADDR_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (user->reg.umode & USR_AWAY)
		send(cl->fd, "G", 1, 0);
	else
		send(cl->fd, "H", 1, 0);
	if (user->reg.umode & IRC_OPERATOR)
		send(cl->fd, "*", 1, 0);
	if (info && info->mode & USR_CHANOP)
		send(cl->fd, "@", 1, 0);
	if (info && info->mode & USR_VOICED)
		send(cl->fd, "+", 1, 0);
// Normalement ici on compte le nombre de noeuds entre le serveur et le client,
// mais bon comme on gere pas les connexions entre serveurs on affiche direct 0.
	send(cl->fd, " :0", 3, 0);
	tmp = user->reg.realname;
	while (tmp && *tmp)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, *tmp, ft_strlen(*tmp), 0);
		tmp++;
	}
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_who_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*user;

	user = e->fds;
	while (user)
	{
		if (!ft_strcmp(user->reg.nick, cmds[1]))
			sv_who_info(user, user->chans, cl, e);
		user = user->next;
	}
}

static void		sv_who_chan(char **cmds, t_fd *cl, t_env *e)
{
	t_chan		*chan;
	t_listin	*list;

	chan = e->chans;
	while (chan)
	{
		if (!ft_strcmp(chan->name, cmds[1]))
		{
			if (!(chan->cmode & CHFL_SECRET))
			{
				list = chan->users;
				while (list)
				{
					if (!cmds[2] || ft_strcmp(cmds[2], "o") || list->mode & USR_CHANOP)
						sv_who_info(list->is, ((t_fd *)list->is)->chans, cl, e);
					list = list->next;
				}
			}
			return ;
		}
		chan = chan->next;
	}	
}

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, "WHO", NULL, cl, e));
	if (ISCHAN(*cmds[1]))
		sv_who_chan(cmds, cl, e);
	else
		sv_who_user(cmds, cl, e);	
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 315 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cmds[1], ft_strlen(cmds[1]), 0);
	send(cl->fd, " :End of /WHO list.", 19, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}
