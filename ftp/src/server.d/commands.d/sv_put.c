/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 19:43:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		put_err(const char *str, char *cmd, t_client *cl, t_server *sv)
{
	int		errnb;

	if ((errnb = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((errnb = sv_client_write(": ", cl)) == IS_OK)
			if ((errnb = sv_client_write(cmd, cl)) == IS_OK)
				if ((errnb = sv_client_write(": ", cl)) == IS_OK)
					if ((errnb = sv_client_write(str, cl)) == IS_OK)
						if ((errnb = sv_client_write("\n", cl)) == IS_OK)
							errnb = sv_client_write(ERR_OUTPUT, cl);
	return (errnb);
}

int				sv_put(char **cmds, t_client *cl, t_server *sv)
{
	(void)cmds;
	(void)cl;
	(void)sv;
	return (put_err("Not implemented yet.", cmds[0], cl, sv));
}
