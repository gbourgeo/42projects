/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 05:18:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 19:01:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_aff_rd(int i, char *rd)
{
	write(1, "\nClient ", 8);
	ft_putnbr(i);
	write(1, " rd: ", 5);
	write(1, rd, BUFF);
}

void			sv_cl_read(t_env *e, int i)
{
	int			ret;

	ret = recv(e->fds[i].fd, e->fds[i].rd.tail, 1, 0);
	if (ret <= 0)
		return (sv_cl_end(NULL, e, i));
	*e->fds[i].wr.tail = *e->fds[i].rd.tail;
	if (*e->fds[i].wr.tail != '\n')
	{
		e->fds[i].wr.tail++;
		e->fds[i].rd.tail++;
	}
	else
		*e->fds[i].rd.tail = '\0';
	if (e->fds[i].rd.tail >= e->fds[i].rd.end)
		e->fds[i].rd.tail = e->fds[i].rd.start;
	if (e->fds[i].wr.tail >= e->fds[i].wr.end)
		e->fds[i].wr.tail = e->fds[i].wr.start;
	if (e->verb)
		sv_aff_rd(i, e->fds[i].rd.start);
}
