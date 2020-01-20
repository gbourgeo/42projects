/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 21:07:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** USER NAME (USER) : NOM D'UTILISATEUR
*/

int				sv_user(char **cmds, t_client *cl, t_server *sv)
{
	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	sv_free_login(&cl->login, sv);
	sv_assign_ptr(&cl->login.user, cmds[1], cmds);
	return (sv_cmd_ok("User name OK", cl, sv));
}

int				sv_user_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": User information\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
