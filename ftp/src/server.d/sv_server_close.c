/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 19:50:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include "sv_main.h"

static void		print_info(int version, t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Closing IPv"FTP_GREEN"%s"FTP_RESET"...\n",
	(version == sv_v4) ? "4" : "6");
}

static void		send_err(int errnb, t_client *cl, t_server *sv)
{
	const char	*error;
	char		*msg;
	int			len;

	error = ft_get_error(errnb);
	len = ft_strlen(sv->info.progname) + ft_strlen(error) + 4;
	if (!(msg = malloc(len)))
		return ;
	ft_strcpy(msg, sv->info.progname);
	ft_strcat(msg, ": ");
	ft_strcat(msg, error);
	ft_strcat(msg, "\n");
	send(cl->fd, msg, len, MSG_DONTWAIT | MSG_NOSIGNAL);
	free(msg);
}

void			sv_server_close(int version, int sendmsg, t_server *sv)
{
	t_client	*cl;

	if ((version != sv_v4 && version != sv_v6) || sv->ip[version] <= 0)
		return ;
	if (sendmsg)
		print_info(version, sv);
	cl = sv->clients;
	while (cl)
	{
		if (cl->version == version)
		{
			if (sendmsg)
				send_err(sv->errnb[version], cl, sv);
			cl = sv_client_end(cl, sv);
		}
		else
			cl = cl->next;
	}
	close(sv->ip[version]);
	sv->ip[version] = -1;
}
