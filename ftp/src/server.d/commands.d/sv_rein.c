/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rein.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:19:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:24:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** REIN
** 120
**  220
** 220
** 421
** 500, 502
*/

int					sv_rein(char **cmds, t_client *cl)
{
	int		err;

	if (cl->data.pid > 0)
		return (sv_response(cl, "120 service not available yet"));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (cmds[1])
		return (sv_response(cl, "500 syntax error"));
	if ((err = sv_client_init(cl, &g_serv)) != IS_OK)
		return (sv_response(cl, "500 internal error (%s)", ft_get_error(err)));
	return (sv_response(cl, "220 client reinitialised"));
}

/*
** REIN <CRLF>
*/

int					sv_rein_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command terminates a USER, flushing all I/O and account",
		"information, except to allow any transfer in progress to be",
		"completed.  All parameters are reset to the default settings",
		"and the control connection is left open.  This is identical",
		"to the state in which a user finds himself immediately after",
		"the control connection is opened.  A USER command may be",
		"expected to follow.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
