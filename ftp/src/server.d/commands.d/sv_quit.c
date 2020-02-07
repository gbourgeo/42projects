/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:46:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/07 20:45:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** QUIT
** 221
** 500
*/

int				sv_quit(char **cmds, t_client *cl)
{
	if (cmds[1])
		return (sv_response(cl, "500 syntax error"));
	cl->errnb[4] = ERR_DISCONNECT;
	return (sv_response(cl, "221 closing connection"));
}

/*
** QUIT <CRLF>
*/

int				sv_quit_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command terminates a USER and if file transfer is not",
		"in progress, the server closes the control connection.  If",
		"file transfer is in progress, the connection will remain",
		"open for result response and the server will then close it.",
		"If the user-process is transferring files for several USERs",
		"but does not wish to close and then reopen connections for",
		"each, then the REIN command should be used instead of QUIT.",
		"",
		"An unexpected close on the control connection will cause the",
		"server to take the effective action of an abort (ABOR) and a",
		"logout (QUIT).", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
