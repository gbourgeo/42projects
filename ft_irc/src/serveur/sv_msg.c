/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:01:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/17 05:17:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_sendtoclient(t_fd *to, char **cmds, t_fd *cl)
{
	int			i;

	i = 2;
	send(to->fd, ":", 1, 0);
	send(to->fd, cl->reg.nick, NICK_LEN, 0);
	send(to->fd, "!~", 2, 0);
	send(to->fd, cl->reg.username, USERNAME_LEN, 0);
	send(to->fd, "@", 1, 0);
	send(to->fd, cl->addr, ADDR_LEN, 0);
	send(to->fd, " MSG ", 5, 0);
	send(to->fd, cmds[1], ft_strlen(cmds[1]), 0);
	send(to->fd, " :", 2, 0);
	while (cmds[i])
	{
		if (i > 2)
			send(to->fd, " ", 1, 0);
		send(to->fd, cmds[i], ft_strlen(cmds[i]), 0);
		i++;
	}
	send(to->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_sendtochan(char **cmds, t_chan *chan, t_fd *cl)
{
	t_listin	*us;
	t_fd		*to;

	us = chan->users;
	while (us)
	{
		to = (t_fd *)us->is;
		if (to->fd != cl->fd)
			sv_sendtoclient(to, cmds, cl);
		us = us->next;
	}
}

/*
** Dans sv_search_chan(...) { while(chan)... }
** Checker si l'user n'est pas sur le channel et que le chan a le mode +n.
** Checker si l'user est sur le chan mais que le chan n'est pas en mode +m et
** qu'il n'est pas chan op.
** Checker si l'user n'est pas ban du chan.
*/

static void		sv_search_chan(char *chan_name, char **cmds, t_fd *cl)
{
	t_listin	*chans;

	chans = cl->chans;
	while (chans)
	{
		if (!sv_strcmp(chan_name, ((t_chan *)chans->is)->name))
		{
			if (1)
				return (sv_sendtochan(cmds, chans->is, cl));
		}
		chans = chans->next;
	}
	sv_err(ERR_CANNOTSENDTOCHAN, chan_name, NULL, cl);
}

static void		sv_search_client(char *nick, char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*fd;

	fd = e->fds;
	while (fd)
	{
		if (!sv_strcmp(nick, fd->reg.nick))
		{
			sv_sendtoclient(fd, cmds, cl);
			if (fd->reg.umode &= USR_AWAY)
			{
				send(cl->fd, e->name, SERVER_LEN, 0);
				send(cl->fd, " 301 ", 5, 0);
				send(cl->fd, cl->reg.nick, NICK_LEN, 0);
				send(cl->fd, " ", 1, 0);
				send(cl->fd, fd->reg.nick, NICK_LEN, 0);
				send(cl->fd, " :", 2, 0);
				send(cl->fd, fd->away, ft_strlen(fd->away), 0);
				send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
			}
			return ;
		}
		fd = fd->next;
	}
	sv_err(ERR_NOSUCHNICK, nick, NULL, cl);
}

void			sv_msg(char **cmds, t_env *e, t_fd *cl)
{
	char		**targets;
	int			i;

	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NORECIPIENT, "MSG", NULL, cl));
	if (!cmds[2] || !*cmds[2])
		return (sv_err(ERR_NOTEXTTOSEND, "MSG", NULL, cl));
	ft_strtolower(cmds[1]);
	if ((targets = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: Server out of memory", e);
	i = 0;
	while (targets[i])
	{
		if (ISCHAN(*targets[i]))
			sv_search_chan(targets[i], cmds, cl);
		else
			sv_search_client(targets[i], cmds, cl, e);
		i++;
	}
	ft_free(&targets);
}
