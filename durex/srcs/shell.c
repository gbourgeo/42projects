/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 05:54:57 by root              #+#    #+#             */
/*   Updated: 2018/08/21 09:31:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int mystrlen(const char *s1);

int			spawnShell(int *fd)
{
	fd[0] = posix_openpt(O_RDWR);
	if (fd[0] >= 0) {
		if (!grantpt(fd[0])) {
			if (!unlockpt(fd[0])) {
				char *pts = ptsname(fd[0]);
				if (pts) {
					fd[1] = open(pts, O_RDWR);
					if (fd[1] >= 0) {
						return 1;
					}
				}
			}
		}
		close(fd[0]);
	}
	return 0;
}
