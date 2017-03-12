/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 05:18:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/11 21:52:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_aff_rd(t_fd *cl)
{
	write(1, "\nClient ", 8);
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
		return (sv_cl_end(NULL, e, cl));
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
