/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 03:08:00 by gbourgeo         ###   ########.fr       */
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
		send(cl->fd, sv->info.progname, ft_strlen(sv->info.progname), 0);
		send(cl->fd, ": ", 2, 0);
		send(cl->fd, err, ft_strlen(err), 0);
		send(cl->fd, "\n", 1, 0);
	}
	err = (errnb[1] >= 0) ? ft_get_error(errnb[1]) : NULL;
	if (err)
	{
		send(cl->fd, sv->info.progname, ft_strlen(sv->info.progname), 0);
		send(cl->fd, ": ", 2, 0);
		send(cl->fd, err, ft_strlen(err), 0);
		send(cl->fd, "\n", 1, 0);
	}
}

static void		print_fatal_error(int version, int errnb[2])
{
	const char	*err;

	if (errnb[0] > 0)
	{
		err = ft_get_error(errnb[0]);
		ft_putstr_fd("FATAL: ", 2);
		ft_putendl_fd(err, 2);
	}
	if (errnb[1] > 0)
	{
		err = ft_get_error(errnb[1]);
		ft_putstr_fd("FATAL: ", 2);
		ft_putendl_fd(err, 2);
	}
	ft_putstr_fd("FATAL: Closing Ip v", 2);
	ft_putnbr_fd((version == v4) ? 4 : 6, 2);
	ft_putchar_fd('\n', 2);
}

void			sv_server_close(int version, int errnb[2], t_server *sv)
{
	t_client	*cl;

	if ((version != v4 && version != v6) || sv->ip[version] <= 0)
		return ;
	if (sv->interactive)
		print_fatal_error(version, errnb);
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
