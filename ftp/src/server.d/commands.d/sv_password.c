/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_password.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:19:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 18:35:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** PASSWORD (PASS) : MOT DE PASSE
*/

int				sv_password(char **cmds, t_client *cl, t_server *sv)
{
	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	sv_assign_ptr(&cl->login.password, &cmds[1], cmds);
	return (sv_cmd_ok("Received password", cl, sv));
}
