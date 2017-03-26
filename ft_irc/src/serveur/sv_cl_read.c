/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 05:18:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/25 23:17:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void			rpl_quit_msg(t_chan *ch, t_fd *cl)
{
	if (ch->cmode & CHFL_ANON)
	{
		sv_cl_write(":anonymous!~anonymous@anonymous LEAVE ", &cl->wr);
		sv_cl_write(ch->name, &cl->wr);
		sv_cl_write(END_CHECK, &cl->wr);
		return ;
	}
	sv_cl_write(":", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write("!~", &cl->wr);
	sv_cl_write(cl->reg.username, &cl->wr);
	sv_cl_write("@", &cl->wr);
	sv_cl_write(cl->addr, &cl->wr);
	sv_cl_write(" QUIT :Remote host closed the connection", &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
}

static void			sv_cl_quit(t_fd *cl)
{
	t_listin		*ch;
	t_listin		*us;

	ch = cl->chans;
	while (ch)
	{
		rpl_quit_msg(ch->is, cl);
		us = ((t_chan *)ch->is)->users;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd)
				sv_cl_send_to(us->is, &cl->wr);
			us = us->next;
		}
		ch = ch->next;
	}
	cl->leaved = 1;
	cl->reason = "Remote host closed the connection";
}

static void			sv_cmd_client(t_env *e, t_fd *cl)
{
	static t_com	com[] = { SV_COMMANDS1, SV_COMMANDS2 };
	char			**cmds;
	int				nb;

	nb = 0;
	if ((cmds = sv_split(&cl->rd)) == NULL)
		return (sv_error("Server: split failed.", e));
	while (com[nb].name && sv_strcmp(com[nb].name, cmds[0]))
		nb++;
	if (com[nb].name)
	{
		if (cl->reg.registered > 0 || (nb >= 8 && nb <= 11))
			com[nb].fct(cmds + 1, e, cl);
		else if (cl->reg.registered == 0)
		{
			sv_err(ERR_NOTREGISTERED, NULL, NULL, cl);
			cl->reg.registered = -1;
		}
	}
	else if (cl->reg.registered > 0)
		sv_err(ERR_UNKNOWNCOMMAND, cmds[0], NULL, cl);
	ft_free(&cmds);
}

void				sv_cl_read(t_env *e, t_fd *cl)
{
	int				ret;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, 0);
	if (ret <= 0)
		return (sv_cl_quit(cl));
	while (ret--)
	{
		if (*cl->rd.tail == '\n')
		{
			sv_cmd_client(e, cl);
			if ((cl->rd.head = cl->rd.tail + 1) == cl->rd.end)
				cl->rd.head = cl->rd.start;
		}
		if (++cl->rd.tail == cl->rd.end)
			cl->rd.tail = cl->rd.start;
		if (--cl->rd.len == 0)
			cl->rd.len = BUFF;
	}
}
