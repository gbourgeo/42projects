/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:46:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/24 05:21:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_quit(char **cmds, t_client *cl, t_server *sv)
{
	if (cmds[1])
		return (sv_cmd_err("too much parameters", cmds[0], cl, sv));
	return (ERR_DISCONNECT);
}
