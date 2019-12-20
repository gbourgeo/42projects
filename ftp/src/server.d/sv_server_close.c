/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:13:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 21:16:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static void		sv_send_error_msg(int errnb[2], t_client *cl, t_server *sv)
{
	if (errnb[0] >= 0)
	{
		ft_strcpy(cl->wr.buff, sv->info.progname);
		ft_strcat(cl->wr.buff, ": ");
		ft_strcat(cl->wr.buff, ft_get_error(errnb[0]));
		ft_strcat(cl->wr.buff, "\n");
		send(cl->fd, cl->wr.buff, ft_strlen(cl->wr.buff),
			MSG_DONTWAIT | MSG_NOSIGNAL);
	}
	if (errnb[1] >= 0)
	{
		ft_strcpy(cl->wr.buff, sv->info.progname);
		ft_strcat(cl->wr.buff, ": ");
		ft_strcat(cl->wr.buff, ft_get_error(errnb[1]));
		ft_strcat(cl->wr.buff, "\n");
		send(cl->fd, cl->wr.buff, ft_strlen(cl->wr.buff),
			MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}

static void		print_fatal_error(int version, int errnb[2])
{
	const char	*err;

	if (errnb[0] > 0)
	{
		err = ft_get_error(errnb[0]);
		ft_putstr_fd("\x1B[31mFATAL\x1B[0m: ", 2);
		ft_putendl_fd(err, 2);
	}
	if (errnb[1] > 0)
	{
		err = ft_get_error(errnb[1]);
		ft_putstr_fd("\x1B[31mFATAL\x1B[0m: ", 2);
		ft_putendl_fd(err, 2);
	}
	ft_putstr_fd("\x1B[31mFATAL\x1B[0m: Closing Ip v", 2);
	ft_putnbr_fd((version == sv_v4) ? 4 : 6, 2);
	ft_putstr_fd("...\n", 2);
}

void			sv_server_close(int version, int errnb[2], t_server *sv)
{
	t_client	*cl;

	if ((version != sv_v4 && version != sv_v6) || sv->ip[version] <= 0)
		return ;
	if (SV_CHECK(sv->options, sv_interactive))
		print_fatal_error(version, errnb);
	cl = sv->clients;
	while (cl)
	{
		if (cl->version == version)
		{
			sv_send_error_msg(errnb, cl, sv);
			cl = sv_client_end(cl, sv);
		}
		else
			cl = cl->next;
	}
	close(sv->ip[version]);
	sv->ip[version] = -1;
}
