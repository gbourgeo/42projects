/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 07:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/14 03:48:42 by gbourgeo         ###   ########.fr       */
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
	size_t		len;

	i = 0;
	len = ft_strlen(str);
	while (e->fds && i < MAX_CLIENT)
	{
		if (e->fds[i].type == FD_CLIENT)
			send(e->fds[i].fd, str, len, 0);
		close(e->fds[i].fd);
		ft_memset(&e->fds[i], 0, sizeof(e->fds[i]));
		i++;
	}
	if (e->fds)
		free(e->fds);
	if (e->chan)
		sv_free_chan(&e->chan);
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	close(e->ipv4);
	close(e->ipv6);
	if (e->verb)
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
