/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 04:01:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 07:30:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		do_this(char *reply, char *reply2, char *cmd, t_fd *cl)
{
	sv_cl_write(" ", cl);
	sv_cl_write(reply, cl);
	if (reply2)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(reply2, cl);
	}
	else if (reply == NULL)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(cmd, cl);
	}
}

static void		do_that(char *reply, char *cmd, char *cmd2, t_fd *cl)
{
	sv_cl_write(" ", cl);
	sv_cl_write(cmd, cl);
	if (reply)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(reply, cl);
		if (cmd2)
		{
			sv_cl_write(" ", cl);
			sv_cl_write(cmd2, cl);
		}
	}
	else if (cmd2)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(cmd2, cl);
	}
}

void			sv_err(char *err, char *cmd, char *cmd2, t_fd *cl)
{
	static char	*replies[][50] = { ERROR1, ERROR2, ERROR3, ERROR4, ERROR5,
									ERROR6, ERROR7, ERROR8, ERROR9, ERROR10,
									ERROR11 };
	long		pos;

	pos = ft_atoi(err) - 400;
	if (pos >= 0 && pos <= ERR_LEN)
	{
		sv_cl_write(":", cl);
		sv_cl_write(e.name, cl);
		sv_cl_write(" ", cl);
		sv_cl_write(err, cl);
		sv_cl_write(" ", cl);
		sv_cl_write(cl->inf->nick, cl);
		if (replies[pos][0])
			do_this(replies[pos][0], replies[pos][1], cmd, cl);
		else if (cmd)
			do_that(replies[pos][1], cmd, cmd2, cl);
		if (replies[pos][2])
		{
			sv_cl_write(" ", cl);
			sv_cl_write(replies[pos][2], cl);
		}
		sv_cl_write(END_CHECK, cl);
	}
}
