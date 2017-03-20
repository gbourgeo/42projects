/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:01:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 04:09:36 by gbourgeo         ###   ########.fr       */
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
	send(to->fd, to->reg.nick, NICK_LEN, 0);
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

static void		sv_msg_client(char *nick, char **cmds, t_fd *cl, t_env *e)
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
	if ((targets = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: Server out of memory", e);
	i = 0;
	while (targets[i])
	{
		if (ISCHAN(*targets[i]))
			sv_msg_chan(targets[i], cmds, cl);
		else
			sv_msg_client(targets[i], cmds, cl, e);
		i++;
	}
	ft_free(&targets);
}
