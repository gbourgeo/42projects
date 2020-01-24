/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rein.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:19:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 20:07:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_rein(char **cmds, t_client *cl, t_server *sv)
{
	(void)cmds;
	sv_free_login(&cl->login, sv);
	return (sv_cmd_ok("Reinitialized user", cl, sv));
}

int					sv_rein_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Reinitialise client\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
