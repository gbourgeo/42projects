/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 02:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/21 17:54:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void		sv_signals_hdlr(int sig)
{
	t_server	*serv;

	(void)sig;
	serv = &g_serv;
	ft_error(ERR_SIGNAL, &serv->info);
	sv_server_close(sv_v4, (int[2]){-1, -1}, serv);
	sv_server_close(sv_v6, (int[2]){-1, -1}, serv);
	sv_free_env(&serv->info.env);
	sv_free_user(&serv->users);
	exit(EXIT_FAILURE);
}
