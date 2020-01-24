/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_stou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:51:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 17:55:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_stou(t_client *cl, t_server *sv)
{
	(void)cl;
	(void)sv;
	return (IS_OK);
}

int					sv_stou_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Store 'Unique' file\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
