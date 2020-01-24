/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:19:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 21:22:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** PASSWORD (PASS) : MOT DE PASSE
*/

int				sv_pass(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*member;

	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (FT_CHECK(sv->options, sv_user_mode))
	{
		if (!(member = sv_getuserbyname(sv->users, cl->login.user))
		|| (!ft_strequ(member->pass, cmds[1])))
			return (sv_cmd_err("Invalid username/password", cmds[0], cl, sv));
		cl->login.logged = 1;
		cl->login.member = member;
	}
	return (sv_cmd_ok("Password received", cl, sv));
}

int				sv_pass_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Password to give\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
