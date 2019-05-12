/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:38:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 09:43:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <signal.h>
#include "shell_env.h"
#include <fcntl.h>
#include <unistd.h>
#include "ft_dprintf.h"

void			init_fd(t_s_env *e)
{
	char	*tty_name;
	int		fd;

	if (e->interactive)
	{
		tty_name = ttyname(STDIN_FILENO);
		fd = open(tty_name, O_RDWR);
	}
	else
		fd = STDIN_FILENO;
	e->fd = fd;
}

void			init_job(t_s_env *e)
{
	if (e->interactive)
	{
		while (tcgetpgrp(STDIN_FILENO) != (e->pgid = getpgrp()))
			kill(-e->pgid, SIGTTIN);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		e->pgid = getpid();
		if (setpgid(e->pgid, e->pgid) < 0)
		{
			ft_dprintf(2, "%s: setpgid error\n", e->progname);
			exit(1);
		}
		ioctl(STDIN_FILENO, TIOCSPGRP, &e->pid);
	}
}
