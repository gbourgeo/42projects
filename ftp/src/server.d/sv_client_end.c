/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 22:23:14 by gbourgeo         ###   ########.fr       */
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
	int			i;

	i = 0;
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	while (i < (int)(sizeof(cl->errnb) / sizeof(cl->errnb[0])))
	{
		if (cl->errnb[i] > 0)
			printf("Client "FTP_BOLD""FTP_RED"%d"FTP_RESET": %s (%d)\n",
			cl->fd, ft_get_error(cl->errnb[i]), i);
		i++;
	}
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
