/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 21:59:05 by gbourgeo         ###   ########.fr       */
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
	{
		ft_putstr("Client \x1B[33m");
		ft_putnbr(cl->fd);
		ft_putendl("\x1B[0m: disconnected.");
	}
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
