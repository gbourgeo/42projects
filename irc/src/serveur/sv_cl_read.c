/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 05:18:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:22:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void			rpl_quit_msg(t_chan *ch, t_fd *to, t_fd *cl)
{
	if (ch->cmode & CHFL_ANON)
	{
		sv_cl_write(":anonymous!~anonymous@anonymous LEAVE ", to);
		sv_cl_write(ch->name, to);
		sv_cl_write(END_CHECK, to);
		return ;
	}
	sv_cl_write(":", to);
	sv_cl_write(cl->inf->nick, to);
	sv_cl_write("!~", to);
	sv_cl_write(cl->inf->username, to);
	sv_cl_write("@", to);
	sv_cl_write((*cl->i.host) ? cl->i.host : cl->i.addr, to);
	sv_cl_write(" QUIT :Remote host closed the connection", to);
	sv_cl_write(END_CHECK, to);
}

static void			sv_cl_quit(t_fd *cl)
{
	t_listin		*chan;
	t_listin		*to;

	chan = cl->chans;
	while (chan)
	{
		to = ((t_chan *)chan->is)->users;
		while (to)
		{
			if (((t_fd *)to->is)->i.fd != cl->i.fd)
				rpl_quit_msg(chan->is, to->is, cl);
			to = to->next;
		}
		chan = chan->next;
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
	if (*cmds && **cmds)
	{
		while (com[nb].name && sv_strcmp(com[nb].name, cmds[0]))
			nb++;
		if (com[nb].name)
		{
			if (cl->inf->registered > 0 || (nb >= 8 && nb <= 12))
				com[nb].fct(cmds + 1, e, cl);
			else if (cl->inf->registered == 0)
			{
				sv_err(ERR_NOTREGISTERED, NULL, NULL, cl);
				cl->inf->registered = -1;
			}
		}
		else if (cl->inf->registered > 0)
			sv_err(ERR_UNKNOWNCOMMAND, cmds[0], NULL, cl);
	}
	ft_free(&cmds);
}

void				sv_cl_read(t_env *e, t_fd *cl)
{
	int				ret;

	ret = recv(cl->i.fd, cl->rd.tail, cl->rd.len, 0);
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
