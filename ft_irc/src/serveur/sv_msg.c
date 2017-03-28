/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:01:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:46:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		rpl_msg(char **cmds, t_fd *to, t_fd *cl)
{
	sv_write(":", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write("!~", &cl->wr);
	sv_write(cl->reg.username, &cl->wr);
	sv_write("@", &cl->wr);
	sv_write(cl->addr, &cl->wr);
	sv_write(" MSG ", &cl->wr);
	sv_write(to->reg.nick, &cl->wr);
	sv_write(" :", &cl->wr);
	sv_write(*cmds, &cl->wr);
	while (*++cmds)
	{
		sv_write(" ", &cl->wr);
		sv_write(*cmds, &cl->wr);
	}
	sv_write(END_CHECK, &cl->wr);
}

static void		sv_msg_client(char *nick, char **cmds, t_fd *cl, t_env *e)
{
	t_fd		*fd;

	fd = e->fds;
	while (fd)
	{
		if (!sv_strcmp(nick, fd->reg.nick))
		{
			rpl_msg(cmds, fd, cl);
			sv_cl_send_to(fd, &cl->wr);
			if (fd->reg.umode &= USR_AWAY)
			{
				rpl_away(cl, fd, e);
				sv_cl_send_to(cl, &e->wr);
			}
			cl->wr.head = cl->wr.tail;
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

	if (!cmds[0] || *cmds[0] == '\0')
		return (sv_err(ERR_NORECIPIENT, "MSG", NULL, cl));
	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NOTEXTTOSEND, "MSG", NULL, cl));
	if ((targets = ft_strsplit(cmds[0], ',')) == NULL)
		sv_error("ERROR: Server out of memory", e);
	i = 0;
	while (targets[i])
	{
		if (ISCHAN(*targets[i]))
			sv_msg_chan(targets[i], cmds + 1, cl);
		else
			sv_msg_client(targets[i], cmds + 1, cl, e);
		i++;
	}
	ft_free(&targets);
}
