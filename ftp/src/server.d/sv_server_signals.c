/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 02:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 22:38:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_init_sig(t_server *sv)
{
	int		i;

	i = 0;
	while (i < NSIG)
		sv->sig[i++] = SIG_ERR;
	sv->sig[SIGINT] = signal(SIGINT, sv_signals_hdlr);
	return (IS_OK);
}

static void	print_info(int sig, t_server *sv)
{
	static char	*signame[] = {
		NULL, "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT",
		"SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2",
		"SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT",
		"SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU",
		"SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR",
		"SIGSYS", "SIGRTMIN", "SIGRTMIN+1", "SIGRTMIN+2", "SIGRTMIN+3",
		"SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8",
		"SIGRTMIN+9", "SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12",
		"SIGRTMIN+13", "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14",
		"SIGRTMAX-13", "SIGRTMAX-12", "SIGRTMAX-11", "SIGRTMAX-10",
		"SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7", "SIGRTMAX-6", "SIGRTMAX-5",
		"SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2", "SIGRTMAX-1", "SIGRTMAX",
	};

	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	ft_putstr_fd("\n\x1B[31m********************\x1B[0m Signal \x1B[1;33m", 2);
	if (sig > 0 && sig < (int)(sizeof(signame) / sizeof(signame[0])))
			ft_putstr_fd(signame[sig], 2);
	else
			ft_putstr_fd("UNKNOWN", 2);
	ft_putstr_fd("\x1B[0m received \x1B[31m********************\x1B[0m\n", 2);
}

void		sv_signals_hdlr(int sig)
{
	t_server	*serv;

	serv = &g_serv;
	print_info(sig, serv);
	if (serv->sig[sig] == SIG_ERR)
		return ;
	sv_server_end(serv);
	exit(EXIT_FAILURE);
}
