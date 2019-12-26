/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 01:32:32 by gbourgeo         ###   ########.fr       */
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
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	if (cl->errnb[0] > 0)
		printf("Client "COLOR_BOLD""COLOR_RED"%d"COLOR_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[0]));
	if (cl->errnb[1] > 0)
		printf("Client "COLOR_BOLD""COLOR_RED"%d"COLOR_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[1]));
	if (cl->errnb[2] > 0)
		printf("Client "COLOR_BOLD""COLOR_RED"%d"COLOR_RESET": %s\n",
		cl->fd, ft_get_error(cl->errnb[2]));
}

t_client		*sv_client_end(t_client *cl, t_server *sv)
{
	t_client	*ret;

	print_info(cl, sv);
	if (cl->data.pid > 0)
		kill(cl->data.pid, SIGKILL);
	if (cl->data.fd > 0)
		close(cl->data.fd);
	if (cl->data.socket > 0)
		close(cl->data.socket);
	ft_strdel(&cl->data.file);
	if (cl->pid_ls > 0)
		kill(cl->pid_ls, SIGKILL);
	close(cl->fd);
	ft_strdel(&cl->pwd);
	ft_strdel(&cl->oldpwd);
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
