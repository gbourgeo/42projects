/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_stou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:51:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:55:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** STOU
** 125, 150
**   (110)
**   226, 250
**   425, 426, 451, 551, 552
** 532, 450, 452, 553
** 500, 501, 421, 530
*/

int					sv_stou(char **cmds, t_client *cl)
{
	return (sv_response(cl, "502 %s unimplemented command", cmds[0]));
}

/*
** STOU <CRLF>
*/

int					sv_stou_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command behaves like STOR except that the resultant",
		"file is to be created in the current directory under a name",
		"unique to that directory.  The 250 Transfer Started response",
		"must include the name generated.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
