/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 02:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 22:33:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include "sv_main.h"

static void		sv_signals_hdlr(int sig)
{
	t_server	*serv;

	serv = &g_serv;
	print_signal_info(sig, FT_CHECK(serv->options, sv_interactive));
	if (serv->sig[sig] == SIG_ERR)
		return ;
	sv_server_end(serv, 1);
	exit(EXIT_FAILURE);
}

int				sv_init_sig(t_server *sv)
{
	int		i;

	i = 0;
	while (i < NSIG)
		sv->sig[i++] = SIG_ERR;
	sv->sig[SIGINT] = signal(SIGINT, sv_signals_hdlr);
	return (IS_OK);
}
