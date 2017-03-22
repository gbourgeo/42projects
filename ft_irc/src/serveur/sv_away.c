/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_away.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 19:54:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_away_msg(char *num, char *msg, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, num, 3, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, msg, ft_strlen(msg), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static char		*sv_find_msg(t_fd *cl)
{
	char		*ptr;

	ptr = cl->wr.head;
	while (ptr != cl->wr.tail && *ptr == ' ')
	{
		ptr++;
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
	}
	while (ptr != cl->wr.tail && *ptr != ' ')
	{
		ptr++;
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
	}
	while (ptr != cl->wr.tail && *ptr == ' ')
	{
		ptr++;
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
	}
	return (ptr);
}

static void		sv_dupmsg(t_fd *cl)
{
	char		*ptr;
	int			len;

	ptr = sv_find_msg(cl);
	len = 0;
	while (ptr != cl->wr.tail)
	{
		ptr++;
		len++;
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
	}
	if (len == 0 || (cl->away = ft_strnew(len + 1)) == NULL)
		return ;
	ptr = sv_find_msg(cl);
	len = 0;
	while (ptr != cl->wr.tail)
	{
		cl->away[len++] = *ptr++;
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
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
