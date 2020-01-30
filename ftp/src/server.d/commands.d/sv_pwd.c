/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:04:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/28 22:59:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** PWD
** 257
** 500, 501, 502, 421, 550
*/

int				sv_pwd(char **cmds, t_client *cl)
{
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 Closing connection"));
	if (cmds[1])
		return (sv_response(cl, "500 Syntax error"));
	return (sv_response(cl, "257 \"%s\" is the current directory", cl->pwd));
}

/*
** PWD  <CRLF>
*/

int				sv_pwd_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the name of the current working",
		"directory to be returned in the reply.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
