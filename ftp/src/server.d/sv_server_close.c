/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 03:44:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include "sv_main.h"

static void		print_info(int version, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Closing IPv"COLOR_GREEN"%s"COLOR_RESET"...\n",
	(version == sv_v4) ? "4" : "6");
}

static void		send_err(int errnb, t_client *cl)
{
	const char	*error;

	error = ft_get_error(errnb);
	if (send(cl->fd, "Server: ", 8, MSG_DONTWAIT | MSG_NOSIGNAL) > 0)
		if (send(cl->fd, error, ft_strlen(error), MSG_DONTWAIT | MSG_NOSIGNAL) > 0)
			send(cl->fd, "\n", 1, MSG_DONTWAIT | MSG_NOSIGNAL);
}

void			sv_server_close(int version, t_server *sv)
{
	t_client	*cl;

	if ((version != sv_v4 && version != sv_v6) || sv->ip[version] <= 0)
		return ;
	print_info(version, sv);
	cl = sv->clients;
	while (cl)
	{
		if (cl->version == version)
		{
			send_err(sv->errnb[version], cl);
			cl = sv_client_end(cl, sv);
		}
		else
			cl = cl->next;
	}
	close(sv->ip[version]);
	sv->ip[version] = -1;
}
