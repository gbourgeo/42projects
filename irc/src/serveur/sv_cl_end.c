/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:03:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 15:28:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_cl_end(char **cmds, t_env *e, size_t i)
{
	send(e->fds[i].fd, "Disconnected.\n", 14, 0);
	close(e->fds[i].fd);
	FD_CLR(e->fds[i].fd, &e->fd_read);
	FD_CLR(e->fds[i].fd, &e->fd_write);
	sv_leave_chan(e, i);
	ft_memset(&e->fds[i], 0, sizeof(*e->fds));
	e->members--;
	if (e->verb)
	{
		ft_putstr("\n\e[31mClient #\e[0m");
		ft_putnbr(i);
		ft_putendl("\e[31m left the server.\e[0m");
	}
	(void)cmds;
}
