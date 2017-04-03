/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_away.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/03 20:58:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			rpl_away(t_fd *to, t_fd *cl, t_env *e)
{
	sv_cl_write(":", to);
	sv_cl_write(e->name, to);
	sv_cl_write(" 301 ", to);
	sv_cl_write(to->inf->nick, to);
	sv_cl_write(" ", to);
	sv_cl_write(cl->inf->nick, to);
	sv_cl_write(" :", to);
	sv_cl_write(cl->away, to);
	sv_cl_write(END_CHECK, to);
}

static void		sv_away_msg(char *num, char *msg, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(num, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(msg, cl);
	sv_cl_write(END_CHECK, cl);
}

static char		*sv_find_msg(t_fd *cl)
{
	char		*ptr;

	ptr = cl->rd.head;
	while (ptr != cl->rd.tail && *ptr == ' ')
	{
		ptr++;
		if (ptr == cl->rd.end)
			ptr = cl->rd.start;
	}
	while (ptr != cl->rd.tail && *ptr != ' ')
	{
		ptr++;
		if (ptr == cl->rd.end)
			ptr = cl->rd.start;
	}
	while (ptr != cl->rd.tail && *ptr == ' ')
	{
		ptr++;
		if (ptr == cl->rd.end)
			ptr = cl->rd.start;
	}
	return (ptr);
}

static void		sv_dupmsg(t_fd *cl)
{
	char		*ptr;
	int			len;

	ptr = sv_find_msg(cl);
	len = 0;
	while (ptr != cl->rd.tail)
	{
		ptr++;
		len++;
		if (ptr == cl->rd.end)
			ptr = cl->rd.start;
	}
	if (len == 0 || (cl->away = ft_strnew(len + 1)) == NULL)
		return ;
	ptr = sv_find_msg(cl);
	len = 0;
	while (ptr != cl->rd.tail)
	{
		cl->away[len++] = *ptr++;
		if (ptr == cl->rd.end)
			ptr = cl->rd.start;
	}
}

void			sv_away(char **cmds, t_env *e, t_fd *cl)
{
	cl->inf->umode &= ~USR_AWAY;
	if (cl->away)
	{
		free(cl->away);
		cl->away = NULL;
	}
	if (!cmds[0] || !*cmds[0])
		sv_away_msg("305", ":You are no longer marked as being away", cl, e);
	else
	{
		cl->inf->umode |= USR_AWAY;
		sv_away_msg("306", ":You have been marked as being away", cl, e);
		sv_dupmsg(cl);
	}
}
