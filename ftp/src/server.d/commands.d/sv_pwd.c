/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:04:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:22:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_pwd(char **cmds, t_client *cl, t_server *sv)
{
	int			ret;

	(void)cmds;
	(void)sv;
	if ((ret = sv_client_write(cl->pwd, cl)) != IS_OK
	|| (ret = sv_client_write("\n", cl)) != IS_OK)
		return (ret);
	return (sv_cmd_ok("Printed working directory", cl, sv));
}

int				sv_pwd_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Print Working Directory\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
