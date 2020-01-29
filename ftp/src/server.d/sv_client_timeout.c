/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_timeout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 02:08:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 16:51:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

t_client			*sv_client_timeout(t_client *cl)
{
	ft_close(&cl->data.pasv_fd);
	cl->errnb[2] = sv_response(cl, "520 connection timeout");
	return (cl);
}
