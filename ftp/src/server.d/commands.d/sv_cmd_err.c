/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cmd_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 02:11:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 17:02:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_cmd_err(const char *str, const char *cmd, t_client *cl,
t_server *sv)
{
	int		ret;

	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": ", cl)) == IS_OK)
			if ((ret = sv_client_write(cmd, cl)) == IS_OK)
				if ((ret = sv_client_write(": ", cl)) == IS_OK)
					if ((ret = sv_client_write(str, cl)) == IS_OK)
						if ((ret = sv_client_write(".\n", cl)) == IS_OK)
							ret = sv_client_write(ERR_OUTPUT, cl);
	return (ret);
}
