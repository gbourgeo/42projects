/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_timeout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 02:08:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/25 02:19:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

t_client			*sv_client_timeout(t_client *cl, t_server *sv)
{
	close(cl->data.fd);
	cl->data.fd = -1;
	cl->errnb[2] = sv_cmd_err("Connection timeout", "transfert", cl, sv);
	if (SV_CHECK(sv->options, sv_interactive))
		printf("Client "COLOR_RED"%d"COLOR_RESET": Transfert timeout\n",
		cl->fd);
	return (cl);
}
