/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 21:30:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** USER NAME (USER) : NOM D'UTILISATEUR
** USER
** 230
** 530
** 500, 501, 421
** 331, 332
*/

int				sv_user(char **cmds, t_client *cl)
{
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 closing connection"));
	if (!cmds[1])
		return (sv_response(cl, "501 Missing parameter"));
	if (cl->login.logged)
		return (sv_response(cl, "230 User logged in"));
	sv_free_login(&cl->login, &g_serv);
	sv_assign_ptr(&cl->login.user, cmds[1], cmds);
	return (sv_response(cl, "331 Please specify the password", cmds[1]));
}

int				sv_user_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command send helpful information regarding its ",
		"implementation status over the control connection to the user.",
		"The command may take an argument (e.g., any command name) and",
		"return more specific information as a response. HELP is allowed",
		"before entering a USER command. The server may use this reply",
		"to specify site-dependent parameters, e.g., in response to",
		"HELP SITE.", NULL
	};

	return (sv_print_help(cl, cmd, "[<commandname>]", help));
}
