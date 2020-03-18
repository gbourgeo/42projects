/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:19:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:22:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** PASSWORD (PASS) : MOT DE PASSE
** PASS
** 230
** 202
** 530
** 500, 501, 503, 421
** 332
*/

int				sv_pass(char **cmds, t_client *cl)
{
	t_server	*sv;
	t_user		*member;

	sv = &g_serv;
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cl->login.user)
		return (sv_response(cl, "503 Undefined USER"));
	if (!(member = sv_getuserbyname(sv->users, cl->login.user))
	|| (!ft_strequ(member->pass, cmds[1])))
		return (sv_response(cl, "530 Loggin incorrect"));
	cl->login.logged = 1;
	cl->login.member = member;
	cl->home = sv_client_home(member->name, sv->users, sv);
	return (sv_response(cl, "230 User %s logged in", member->name));
}

/*
** PASS <SP> <mot de passe> <CRLF>
*/

int				sv_pass_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"The argument field is a Telnet string specifying the user's",
		"password.  This command must be immediately preceded by the",
		"user name command, and, for some sites, completes the user's",
		"identification for access control.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
