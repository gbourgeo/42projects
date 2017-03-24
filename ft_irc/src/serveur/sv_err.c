/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 04:01:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 21:05:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		do_this(char *reply, char *reply2, char *cmd, t_fd *cl)
{
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(reply, &cl->wr);
	if (reply2)
	{
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(reply2, &cl->wr);
	}
	else if (reply == NULL)
	{
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(cmd, &cl->wr);
	}
}

static void		do_that(char *reply, char *cmd, char *cmd2, t_fd *cl)
{
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(cmd, &cl->wr);
	if (reply)
	{
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(reply, &cl->wr);
		if (cmd2)
		{
			sv_cl_write(" ", &cl->wr);
			sv_cl_write(cmd2, &cl->wr);
		}
	}
	else if (cmd2)
	{
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(cmd2, &cl->wr);
	}
}

void			sv_err(char *err, char *cmd, char *cmd2, t_fd *cl)
{
	static char	*replies[][50] = { ERROR1, ERROR2, ERROR3, ERROR4, ERROR5,
									ERROR6, ERROR7, ERROR8, ERROR9, ERROR10 };
	long		pos;

	pos = ft_atoi(err) - 401;
	if (pos >= 0 && pos < 102)
	{
		sv_cl_write(e.name, &cl->wr);
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(err, &cl->wr);
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(cl->reg.nick, &cl->wr);
		if (replies[pos][0])
			do_this(replies[pos][0], replies[pos][1], cmd, cl);
		else if (cmd)
			do_that(replies[pos][1], cmd, cmd2, cl);
		if (replies[pos][2])
		{
			sv_cl_write(" ", &cl->wr);
			sv_cl_write(replies[pos][2], &cl->wr);
		}
		sv_cl_write(END_CHECK, &cl->wr);
		sv_cl_send_to(cl, &cl->wr);
		cl->wr.head = cl->wr.tail;
	}
}
