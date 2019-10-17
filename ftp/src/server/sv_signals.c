/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 02:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 00:47:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void		sv_signals_hdlr(int sig)
{
	(void)sig;
	sv_server_close(v4, (int[2]){0, -1}, &serv);
	sv_server_close(v6, (int[2]){0, -1}, &serv);
	ft_error(ERR_SIGNAL, &serv.info);
	sv_free_env(&serv.info.env);
	exit(EXIT_FAILURE);
}
