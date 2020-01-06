/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:17:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/06 19:45:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef __linux__
#  define _POSIX_C_SOURCE 200809L
# endif
#include <unistd.h>
#include "common.h"

void		print_signal_info(int sig, int interactive)
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

	if (!interactive)
		return ;
	dprintf(STDERR_FILENO, "\n"FTP_RED"********************"FTP_RESET);
	dprintf(STDERR_FILENO, " Signal "FTP_BOLD""FTP_BLUE);
	if (sig > 0 && sig < (int)(sizeof(signame) / sizeof(signame[0])))
		dprintf(STDERR_FILENO, "%s", signame[sig]);
	else
		dprintf(STDERR_FILENO, "%d", sig);
	dprintf(STDERR_FILENO, FTP_RESET" received ");
	dprintf(STDERR_FILENO, FTP_RED"********************"FTP_RESET"\n");
}
