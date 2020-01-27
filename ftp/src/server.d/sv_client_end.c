/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 19:39:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 1
#endif
#include <sys/types.h>
#include <unistd.h>
#include "sv_main.h"

static void		print_info(t_client *cl, t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	if (cl->errnb[0] > 0)
		printf("Client "FTP_BOLD""FTP_RED"%d"FTP_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[0]));
	if (cl->errnb[1] > 0)
		printf("Client "FTP_BOLD""FTP_RED"%d"FTP_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[1]));
	if (cl->errnb[2] > 0)
		printf("Client "FTP_BOLD""FTP_RED"%d"FTP_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[2]));
	if (cl->errnb[3] > 0)
		printf("Client "FTP_BOLD""FTP_RED"%d"FTP_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[3]));
}

t_client		*sv_client_end(t_client *cl, t_server *sv)
{
	t_client	*ret;

	if (cl->data.pid > 0)
		return (cl->next);
	print_info(cl, sv);
	ft_close(&cl->fd);
	ft_strdel(&cl->pwd);
	ft_strdel(&cl->oldpwd);
	sv_free_login(&cl->login, NULL);
	sv_free_data(&cl->data);
	if (cl->prev)
		cl->prev->next = cl->next;
	else
		sv->clients = cl->next;
	if (cl->next)
		cl->next->prev = cl->prev;
	ret = cl->next;
	free(cl);
	sv->connected--;
	return (ret);
}
