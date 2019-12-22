/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 00:51:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 1
#endif
#include <sys/types.h>
#include <unistd.h>
#include "sv_main.h"

t_client		*sv_client_end(t_client *cl, t_server *sv)
{
	t_client	*ret;

	if (SV_CHECK(sv->options, sv_interactive))
		printf("Client "COLOR_YELLOW"%d"COLOR_RESET": disconnect.\n", cl->fd);
	if (cl->pid > 0)
		kill(cl->pid, SIGKILL);
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
