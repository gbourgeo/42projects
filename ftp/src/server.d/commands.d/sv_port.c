/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_port.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:30:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 19:40:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** DATA PORT (PORT) PORT DU CANAL DE DONNEES
** Example: PORT h1,h2,h3,h4,p1,p2
*/

int					sv_port(char **cmds, t_client *cl, t_server *sv)
{
	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	sv_assign_ptr(&cl->data.port, &cmds[1], cmds);
	return (sv_cmd_ok("Data port changed", cl, sv));
}
