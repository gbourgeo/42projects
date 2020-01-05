/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 06:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 23:29:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_sig_hdlr(int sig)
{
	t_client	*cl;

	cl = &client;
	print_signal_info(sig, FT_CHECK(cl->options, cl_interactive));
	if (sig < 0 || sig > NSIG || cl->sig[sig] == SIG_ERR)
		return ;
	cl_client_end(cl);
	exit(EXIT_FAILURE);
}

int				cl_client_signals(t_client *cl)
{
	int			i;

	i = 0;
	while (i < NSIG)
		cl->sig[i++] = SIG_ERR;
	cl->sig[SIGINT] = signal(SIGINT, cl_sig_hdlr);
	return (IS_OK);
}
