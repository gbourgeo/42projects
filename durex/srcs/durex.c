/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/07/13 00:14:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "durex.h"

static void			closeFileDescriptors(void)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		return ;
	while (i < lim.rlim_max)
		close(i++);
}

static void			sanitizeEnvironment(void)
{
	extern char		**environ;

	for (int i = 0; environ && environ[i]; i++)
		memset(environ[i], 0, strlen(environ[i]));
}

static int			daemonize()
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return 1;
	if (pid > 0)
		quitClearlyDaemon();

	if (setsid() < 0)
		return 1;
	pid = fork();
	if (pid < 0)
		return 1;
	if (pid > 0)
		quitClearlyDaemon();

	fd = 0;
	while (fd < NSIG)
		signal(fd++, daemonSigHandler);

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		return 1;
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	close(fd);
	umask(0);
	if (chdir("/") < 0)
		return 1;
	sleep(1);
}

int					durex()
{
	if (setuid(getuid()) == -1)
		return 0;
	closeFileDescriptors();
	sanitizeEnvironment();
	e.lock = open(DUREX_LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (e.lock < 0)
		return 0;
	if (flock(e.lock, LOCK_EX | LOCK_NB))
		return 0;
	e.child = 0;
	if (daemonize())
		return 0;
	e.child = 1;

	quitClearlyDaemon();
	return 0;
}
