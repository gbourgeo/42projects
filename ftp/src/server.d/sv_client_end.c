/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 22:47:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_client		*sv_client_end(t_client *cl, t_server *sv)
{
	t_client	*ret;

	close(cl->fd);
	if (cl->pwd)
		free(cl->pwd);
	if (cl->oldpwd)
		free(cl->oldpwd);
	if (cl->prev)
		cl->prev->next = cl->next;
	else
		sv->clients = cl->next;
	if (cl->next)
		cl->next->prev = cl->next;
	ret = cl->next;
	free(cl);
	return (ret);
}
