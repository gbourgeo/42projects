/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 00:27:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/17 14:35:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sv_main.h"

static void			sv_server_killed(int sig)
{
	if (sig == SIGTERM)
		sv_error("Server Killed By SIGTERM", &e);
	if (sig == SIGINT)
		sv_error("Server Killed By SIGINT", &e);
	if (sig == SIGBUS)
		sv_error("Server Killed By SIGBUS", &e);
	sv_error("Server Killed By A Signal xD", &e);
}

void				sv_signals(void)
{
	signal(SIGWINCH, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGINT, sv_server_killed);
	signal(SIGTERM, sv_server_killed);
	signal(SIGBUS, sv_server_killed);
	signal(SIGUSR1, SIG_IGN);
}
