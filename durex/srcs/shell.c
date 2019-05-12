/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 04:24:37 by root              #+#    #+#             */
/*   Updated: 2019/05/12 16:49:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fork, pid_t */
#include <unistd.h>
/* posix_openpt */
#include <stdlib.h>
#include <fcntl.h>

void		clientShell(int fds);
void		serverLog(int ts, const char *message, ...);

int			spawnShell(int cl_fd)
{
	int		fdm;
	int		fds;
	pid_t	pid;

	fdm = posix_openpt(O_RDWR);
	if (fdm >= 0) {
		if (!grantpt(fdm)) {
			if (!unlockpt(fdm)) {
				fds = open(ptsname(fdm), O_RDWR);
				if (fds >= 0) {
					pid = fork();
					if (pid == 0) {
						close(fdm);
						clientShell(fds);
						exit(0);
					} else if (pid > 0) {
						close(fds);
						serverLog(1, "[INFO] - %d: %s created (%d)\n", cl_fd, ptsname(fdm), pid);
						return (fdm);
					}
					serverLog(1, "[ERRO] - %d: Failed to fork new shell\n", cl_fd);
					close(fds);
				}
			}
		}
		close(fdm);
	}
	return (-1);
}
