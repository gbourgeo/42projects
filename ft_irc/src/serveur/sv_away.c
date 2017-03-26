/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_away.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/26 01:03:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			rpl_away(t_fd *to, t_fd *cl, t_env *e)
{
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 301 ", &e->wr);
	sv_cl_write(to->reg.nick, &e->wr);
	sv_cl_write(" ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" :", &e->wr);
	sv_cl_write(cl->away, &e->wr);
	sv_cl_write(END_CHECK, &e->wr);
}

static void		sv_away_msg(char *num, char *msg, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(num, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(msg, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
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
	cl->reg.umode &= ~USR_AWAY;
	if (cl->away)
	{
		free(cl->away);
		cl->away = NULL;
	}
	if (!cmds[0] || !*cmds[0])
		sv_away_msg("305", ":You are no longer marked as being away", cl, e);
	else
	{
		cl->reg.umode |= USR_AWAY;
		sv_away_msg("306", ":You have been marked as being away", cl, e);
		sv_dupmsg(cl);
	}
}
