/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 18:53:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static void		sv_send_error(int errnb[2], t_client *cl, t_server *sv)
{
	const char	*err;

	err = (errnb[0] >= 0) ? ft_get_error(errnb[0]) : NULL;
	if (err)
	{
		send(cl->fd, err, ft_strlen(err), 0);
		send(cl->fd, "\n", 1, 0);
		if (sv->interactive)
			ft_putendl(err);
	}
	err = (errnb[1] >= 0) ? ft_get_error(errnb[1]) : NULL;
	if (err)
	{
		send(cl->fd, err, ft_strlen(err), 0);
		send(cl->fd, "\n", 1, 0);
		if (sv->interactive)
			ft_putendl(err);
	}
}

void			sv_server_close(int version, int errnb[2], t_server *sv)
{
	t_client	*cl;

	if (version != v4 && version != v6)
		return ;
	cl = sv->clients;
	while (cl)
	{
		if (cl->version == version)
		{
			sv_send_error(errnb, cl, sv);
			cl = sv_client_end(cl, sv);
		}
		else
			cl = cl->next;
	}
	close(sv->ip[version]);
	sv->ip[version] = -1;
}
