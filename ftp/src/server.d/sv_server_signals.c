/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 02:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/21 23:57:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
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
	dprintf(STDERR_FILENO, "\n"COLOR_RED"********************"COLOR_RESET);
	dprintf(STDERR_FILENO, " Signal "COLOR_BOLD""COLOR_BLUE);
	if (sig > 0 && sig < (int)(sizeof(signame) / sizeof(signame[0])))
		dprintf(STDERR_FILENO, "%s", signame[sig]);
	else
		dprintf(STDERR_FILENO, "%d", sig);
	dprintf(STDERR_FILENO, COLOR_RESET" received ");
	dprintf(STDERR_FILENO, COLOR_RED"********************"COLOR_RESET"\n");
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
