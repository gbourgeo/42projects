// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/07 22:26:13 by gbourgeo          #+#    #+#             //
//   Updated: 2017/09/11 06:26:44 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Main.hpp"
#include "Daemon.hpp"
#include <stdio.h>
#include <unistd.h> //exit close
#include <stdlib.h> //free
#include <sys/time.h> //getrlimit
#include <sys/resource.h>
#include <sys/types.h> //umask
#include <sys/stat.h>
#include <string.h> //strlen
#include <signal.h>

static int	ft_error(int err, const char *str)
{
	std::cerr << "Matt_daemon: ";
	if (err)
		perror(str);
	else
		std::cerr << str << std::endl;
	return 1;
}

static void	closeFileDescriptors(void)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		ft_error(1, "getrlimit");
	while (i < lim.rlim_max)
		close(i++);
}

static void	resetSignalHandlers(sigset_t *oldmask)
{
	size_t		i;
	sigset_t	newmask;

	i = 0;
	while (i < _NSIG)
		signal(i++, SIG_DFL);
	sigfillset(&newmask);
	if (sigprocmask(SIG_SETMASK, &newmask, oldmask) < 0)
		ft_error(1, "signals");
}

static void	sanitizeEnvironnement(void)
{
	extern char **environ;

	for (int i = 0; environ && environ[i]; i++)
		memset(environ[i], 0, strlen(environ[i]));
}

int				main(void)
{
	sigset_t		oldmask;
	pid_t			pid;
	
	if (setuid(getuid()) == -1)
		return ft_error(1, "setuid");
	closeFileDescriptors();
	resetSignalHandlers(&oldmask);
	sanitizeEnvironnement();
	pid = fork();
	if (pid < 0)
		ft_error(1, "fork");
	if (pid == 0)
	{
		if (setsid() < 0)
			ft_error(1, "setsid");
		pid = fork();
		if (pid < 0)
			ft_error(1, "2nd fork");
		if (pid == 0)
			LaunchServer();
		exit(0);
	}
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		ft_error(1, "signals");
	exit(0);
}
