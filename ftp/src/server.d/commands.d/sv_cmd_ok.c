/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cmd_ok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 00:38:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 00:41:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_cmd_ok(const char *str, t_client *cl, t_server *sv)
{
	int		errnb;

	if ((errnb = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((errnb = sv_client_write(": ", cl)) == IS_OK)
			if ((errnb = sv_client_write(str, cl)) == IS_OK)
				if ((errnb = sv_client_write(".\n", cl)) == IS_OK)
					errnb = sv_client_write(OK_OUTPUT, cl);
	return (errnb);
}
