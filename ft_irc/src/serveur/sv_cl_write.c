/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:15:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/11/17 02:35:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void			sv_aff_wr(t_fd *cl)
{
	write(1, "\nClient ", 8);
	write(1, cl->addr, ft_strlen(cl->addr));
	write(1, " ", 1);
	write(1, cl->port, ft_strlen(cl->port));
	write(1, " wr: ", 5);
	write(1, cl->wr.start, BUFF);
}

static void			sv_null(char **cmds, t_env *e, t_fd *cl)
{
	(void)e;
	send(cl->fd, cmds[0], ft_strlen(cmds[0]), 0);
	send(cl->fd, " :Unknown command.", 18, 0);
	send(cl->fd, "\r\n", 2, 0);
}

static void			sv_cmd_client(t_env *e, t_fd *cl)
{
	char			**cmds;
	int				nb;
	static t_com	com[] = { { "/away", sv_away }, {"/connect", sv_connect },
							{ "/help", sv_help }, { "/join", sv_join },
							{ "/leave", sv_leave }, { "/list", sv_list },
							{ "/msg", sv_msg }, { "/nick", sv_nick },
							{ "/quit", sv_cl_end }, { "/topic", sv_topic },
							{ "/who", sv_who }, { NULL, sv_null } };

	nb = 0;
	if ((cmds = sv_split(&cl->wr)) == NULL)
		return (sv_error("Server: split failed.\r\n", e));
	while (com[nb].name && ft_strcmp(com[nb].name, cmds[0]))
		nb++;
	com[nb].fct(cmds, e, cl);
	ft_free(&cmds);
}

static void			sv_clean_buf(t_buf *wr)
{
	while (wr->head && *wr->head == ' ')
	{
		wr->head++;
		if (wr->head >= wr->end)
			wr->head = wr->start;
	}
}

void				sv_cl_write(t_env *e, t_fd *cl)
{
	if (cl->wr.tail && (*cl->wr.tail == '\n' || *cl->wr.tail == '\r'))
	{
		sv_clean_buf(&cl->wr);
		if (*cl->wr.head == '/')
			sv_cmd_client(e, cl);
		else if (cl->wr.head != cl->wr.tail && cl->chan)
			sv_sendto_chan(cl);
		if (cl->wr.tail)
			*cl->wr.tail = '\0';
		cl->wr.head = cl->wr.tail;
		if (!cl->leaved)
			sv_cl_prompt(cl);
		if (e->verb)
			sv_aff_wr(cl);
	}
}
