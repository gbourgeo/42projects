/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_timeout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 02:08:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:08:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

t_client			*sv_client_timeout(t_client *cl, t_server *sv)
{
	ft_close(&cl->data.fd);
	cl->errnb[2] = sv_cmd_err("Connection timeout", "transfert", cl, sv);
	return (cl);
}
