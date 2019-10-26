/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 00:27:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

t_client		*sv_client_end(t_client *cl, t_server *sv)
{
	t_client	*ret;

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
	return (ret);
}
