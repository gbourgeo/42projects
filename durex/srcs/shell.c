/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 04:24:37 by root              #+#    #+#             */
/*   Updated: 2018/08/28 05:47:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fork, pid_t */
#include <unistd.h>
/* posix_openpt */
#include <stdlib.h>
#include <fcntl.h>

void		clientShell(int fds);
void		serverLog(const char *message, ...);

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
						serverLog("[INFO] - %d: %s created (%d)", cl_fd, ptsname(fdm), pid);
						return (fdm);
					}
					serverLog("[ERRO] - %d: Failed to fork new shell", cl_fd);
					close(fds);
				}
			}
		}
		close(fdm);
	}
	return (-1);
}
