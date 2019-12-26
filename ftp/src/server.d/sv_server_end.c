/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:53:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:42:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_server_end(t_server *sv, int sendmsg)
{
	int		i;

	i = 0;
	sv_server_close(sv_v4, sendmsg, sv);
	sv_server_close(sv_v6, sendmsg, sv);
	sv_free_env(&sv->info.env);
	sv_free_user(&sv->users);
	while (i < NSIG)
	{
		if (sv->sig[i] != SIG_ERR)
			signal(i, sv->sig[i]);
		i++;
	}
}
