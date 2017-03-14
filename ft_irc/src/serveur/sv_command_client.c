/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_command_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 03:38:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int		sv_isuser(char *name, t_fd *cl)
{
	t_listin	*list;
	t_chan		*chan;

	list = cl->chans;
	while (list)
	{
		chan = (t_chan *)list->is;
		if (!ft_strcmp(chan->name, name))
			return (1);
		list = list->next;
	}
	return (0);
}

static void		sv_whoinfo(t_listin *list, t_fd *cl, t_env *e)
{
	t_fd		*user;
	t_chan		*chan;

	user = (t_fd *)list->is;
	chan = (t_chan *)user->chans->is;
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 352 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " ~", 2, 0);
	send(cl->fd, user->reg.username, USERNAME_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->addr, 1025, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, user->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (user->reg.mode & USR_AWAY)
		send(cl->fd, "G", 1, 0);
	else
		send(cl->fd, "H", 1, 0);
	if (user->reg.mode & IRC_OPERATOR)
		send(cl->fd, "*", 1, 0);
	if (list->mode & USR_CHANOP)
		send(cl->fd, "@", 1, 0);
	if (list->mode & USR_VOICED)
		send(cl->fd, "+", 1, 0);
// Normalement ici on compte le nombre de noeuds entre le serveur et le client.
	send(cl->fd, " :0 ", 4, 0);
	send(cl->fd, *user->reg.realname, ft_strlen(*user->reg.realname), 0);
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
 ///////////////////////////// PAS SÛR POUR LE PIPE '|'
			if (sv_isuser(cmds[1], cl) || (chan->mode | CHFL_SECRET))
			{
				list = chan->users;
				while (list)
				{
					if (!cmds[2] ||
						(!ft_strcmp(cmds[2], "o") && list->mode & USR_CHANOP) ||
						ft_strcmp(cmds[2], "o"))
						sv_whoinfo(list, cl, e);
					list = list->next;
				}
			}
			return ;
		}
	}	
}

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, cmds[0], NULL, cl, e));
	if (ISCHAN(*cmds[1]))
		sv_who_chan(cmds, cl, e);
	send(cl->fd, "\n:End of /WHO list.\r\n", 21, 0);
}

static void		sv_send_chaninfo(t_chan *chan, t_fd *cl, t_env *e)
{
	char		*visible;

	visible = ft_itoa(chan->mode);
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 322 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, visible, ft_strlen(visible), 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, ft_strlen(chan->topic), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_list_specific_chan(char **cmds, t_fd *cl, t_env *e)
{
	char		**chans;
	t_chan		*tmp;
	int			i;

	if ((chans = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: SERVER: out of memory", e);
	i = 0;
	while (chans[i])
	{
		tmp = e->chans;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, chans[i]))
			{
				sv_send_chaninfo(tmp, cl, e);
				break;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			sv_err(ERR_NOSUCHSERVER, chans[i], NULL, cl, e);
		i++;
	}
	ft_free(&chans);
}

void			sv_list(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*chan;

	if (cmds[1])
		sv_list_specific_chan(cmds, cl, e);
	else
	{
		chan = e->chans;
		while (chan)
		{
			sv_send_chaninfo(chan, cl, e);
			chan = chan->next;
		}
	}
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 323 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :End of /LIST", 14, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

void			sv_connect(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1] || !cmds[2] || !*cmds[2])
		return (sv_err(ERR_NEEDMOREPARAMS, cmds[0], NULL, cl, e));
	if (cl->reg.mode & IRC_OPERATOR)
		return ; //This is not handled by my ft_irc ^^
	sv_err(ERR_NOPRIVILEGES, cmds[0], NULL, cl, e);
}
