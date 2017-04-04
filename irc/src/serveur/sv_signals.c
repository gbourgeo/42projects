/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 00:27:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 04:38:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_server_killed(int sig)
{
	if (sig == SIGTERM)
		sv_error("Server Killed By SIGTERM", &e);
	if (sig == SIGINT)
		sv_error("Server Killed By SIGINT", &e);
	if (sig == SIGBUS)
		sv_error("Server Killed By SIGBUS", &e);
	sv_error("Server Killed By A Signal xD", &e);
}
