/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 05:18:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 08:48:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_leave_msg(t_chan *ch, t_fd *us)
{
	send(us->fd, ":anonymous!~anonymous@anonymous LEAVE ", 1, 0);
	send(us->fd, ch->name, CHANNAME_LEN, 0);
	send(us->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_quit_msg(t_chan *ch, t_fd *cl, t_fd *us)
{
	if (ch->cmode & CHFL_ANON)
		return (sv_leave_msg(ch, us));
	send(us->fd, ":", 1, 0);
	send(us->fd, cl->reg.nick, NICK_LEN, 0);
	send(us->fd, "!~", 2, 0);
	send(us->fd, cl->reg.username, USERNAME_LEN, 0);
	send(us->fd, "@", 1, 0);
	send(us->fd, cl->addr, ADDR_LEN, 0);
	send(us->fd, " QUIT :Remote host closed the connection", 40, 0);
	send(us->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_cl_quit(t_fd *cl)
{
	t_listin	*ch;
	t_listin	*us;

	ch = cl->chans;
	while (ch)
	{
		us = ((t_chan *)ch->is)->users;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd)
				sv_quit_msg(ch->is, cl, us->is);
			us = us->next;
		}
		ch = ch->next;
	}
	cl->leaved = 1;
	cl->reason = "Remote host closed the connection";
}

static void		sv_aff_rd(t_fd *cl)
{
	write(1, "Client ", 7);
	write(1, cl->addr, ft_strlen(cl->addr));
	write(1, " ", 1);
	write(1, cl->port, ft_strlen(cl->port));
	write(1, " rd: ", 5);
	write(1, cl->rd.start, BUFF);
}

void			sv_cl_read(t_env *e, t_fd *cl)
{
	int			ret;

	ret = recv(cl->fd, cl->rd.tail, 1, 0);
	if (ret <= 0)
		return (sv_cl_quit(cl));
	*cl->wr.tail = *cl->rd.tail;
	if (e->verb && *cl->rd.tail == '\n')
		sv_aff_rd(cl);
	if (*cl->rd.tail != '\n')
	{
		cl->wr.tail++;
		cl->rd.tail++;
	}
	else
		*cl->rd.tail = '\0';
	if (cl->rd.tail >= cl->rd.end)
		cl->rd.tail = cl->rd.start;
	if (cl->wr.tail >= cl->wr.end)
		cl->wr.tail = cl->wr.start;
}
