/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 07:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/21 03:51:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_free_chan(t_chan **chan)
{
	if ((*chan)->next)
		sv_free_chan(&(*chan)->next);
	ft_memset(*chan, 0, sizeof(**chan));
	free(*chan);
	*chan = NULL;
}

void			sv_error(char *str, t_env *e)
{
	size_t		i;

	i = 1;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			send(e->fds[i].fd, str, ft_strlen(str), 0);
			close(e->fds[i].fd);
			ft_memset(&e->fds[i], 0, sizeof(e->fds[i]));
		}
		i++;
	}
	sv_free_chan(&e->chan);
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	if (e->verb)
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
