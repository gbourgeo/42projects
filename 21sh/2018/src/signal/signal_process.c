/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:40:12 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 16:53:25 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "signal_intern.h"

static void	sig_p_stop(int sig)
{
	static int s_pid = 0;

	if (sig < 0)
		s_pid = sig;
	else if (sig != 0)
	{
		if (s_pid < 0)
			kill(s_pid, SIGTSTP);
	}
}

static void	sig_p_sigint(int sig)
{
	static int s_pid = 0;

	if (sig < 0)
		s_pid = sig;
	else if (sig != 0)
	{
		if (s_pid < 0)
			kill(s_pid, SIGINT);
	}
}

static void	sig_p_quit(int sig)
{
	static int s_pid = 0;

	if (sig < 0)
		s_pid = sig;
	else if (sig != 0)
	{
		if (s_pid < 0)
			kill(s_pid, SIGQUIT);
	}
}

int			sig_to_pgid(int pgid)
{
	sig_p_sigint(-pgid);
	sig_p_stop(-pgid);
	sig_p_quit(-pgid);
	if (pgid != 0)
	{
		if (signal(SIGINT, sig_p_sigint) == SIG_ERR)
			return (1);
		if (signal(SIGTSTP, sig_p_stop) == SIG_ERR)
			return (1);
		if (signal(SIGQUIT, sig_p_quit) == SIG_ERR)
			return (1);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			return (1);
		if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
			return (1);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (1);
	}
	return (0);
}
