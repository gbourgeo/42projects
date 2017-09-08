// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/07 22:26:13 by gbourgeo          #+#    #+#             //
//   Updated: 2017/09/08 04:10:06 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Main.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_error(int err, const char *str)
{
	if (err)
		perror(str);
	else
		printf("%s\n", str);
	exit(1);
}

#include <sys/time.h>
#include <sys/resource.h>

static void	closeFileDescriptors(char *prog)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		ft_error(1, prog);
	while (i < lim.rlim_max)
		close(i++);
}

#include <signal.h>

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

static void	sanitizeEnvironnement(char **environ)
{
	char	*name;
	int		len;
	int		lastlen;

	name = NULL;
	len = 0;
	lastlen = 0;
	while (environ != NULL && environ[0] != NULL)
	{
		len = 0;
		while (environ[0][len] != '\0' && environ[0][len] != '=')
			len++;
		if (environ[0][len] != '=')
			ft_error(0, "Environnement variable corrupted.");
		if (len > lastlen)
		{
			if (name)
				free(name);
			if ((name = (char *)malloc(len + 1)) == NULL)
				ft_error(0, "Malloc failed.");
			lastlen = len;
		}
		name[len] = '\0';
		while (--len >= 0)
			name[len] = environ[0][len];
		if (unsetenv(name) == -1)
			ft_error(0, "Unable to delete environnement variable");
	}
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	configDaemon(void)
{
	int		fd;

	if ((fd = open("/dev/null", O_RDWR)) < 0)
		ft_error(1, "open");
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);
	umask(0);
	if (chdir("/") < 0)
		ft_error(1, "chdir");
	fd = open("/var", O_DIRECTORY);
	if (fd < 0 && mkdir("/var", 0755) < 0)
		ft_error(1, "mkdir /var");
	else
		close(fd);
	fd = open("/var/log", O_DIRECTORY);
	if (fd < 0 && mkdir("/var/log", 0755) < 0)
		ft_error(1, "mkdir /var/log");
	else
		close(fd);
	fd = open("/var/log/matt_daemon", O_DIRECTORY);
	if (fd < 0 && mkdir("/var/log/matt_daemon", 0755) < 0)
		ft_error(1, "mkdir /var/log/matt_daemon");
	else
		close(fd);
	fd = open("/var/log/matt_daemon/matt_daemon.log", O_CREAT | O_APPEND | O_WRONLY, 0600);
	if (fd < 0)
		ft_error(1, "open matt_daemon.log");
	return (fd);
}

#include <time.h>
#include <string.h>

static void myItoa(int nb, int size, char *p)
{
	while (size-- > 0)
	{
		p[size] = nb % 10 + '0';
		nb = nb / 10;
	}
}

static void	writeLogFile(int logfd, const char *type, const char *info)
{
	struct tm	*tm;
	time_t		tim;
	char		p[4];

	tim = time(NULL);
	tm = localtime(&tim);
	// logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << tm->tm_year;
	// logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	// logfd << "] [ " << type << " ] - Matt_daemon: " << info << std::endl;
	write(logfd, "[", 1);
	myItoa(tm->tm_mday, 2, p);
	write(logfd, p, 2);
	
	write(logfd, "/", 1);
	myItoa(tm->tm_mon, 2, p);
	write(logfd, p, 2);
	
	write(logfd, "/", 1);
	myItoa(1900 + tm->tm_year, 4, p);
	write(logfd, p, 4);
	
	write(logfd, "-", 1);
	myItoa(tm->tm_hour, 2, p);
	write(logfd, p, 2);
	
	write(logfd, ":", 1);
	myItoa(tm->tm_min, 2, p);
	write(logfd, p, 2);
	
	write(logfd, ":", 1);
	myItoa(tm->tm_sec, 2, p);
	write(logfd, p, 2);

	write(logfd, "] [ ", 4);
	write(logfd, type, strlen(type));
	write(logfd, " ] - Matt_daemon: ", 18);
	write(logfd, info, strlen(info));
	write(logfd, "\n", 1);
}

static void	forkDaemon(sigset_t *oldmask)
{
	pid_t		pid;
	int			logfd;

	pid = fork();
	if (pid == 0)
	{
		if (setsid() == -1)
			ft_error(1, "setsid");
		pid = fork();
		if (pid < 0)
			ft_error(1, "2nd fork");
		else if (pid == 0)
		{
			logfd = configDaemon();
			writeLogFile(logfd, "INFO", "Server created.");
			close(logfd);
			exit(1);
		}
		exit(0);
	}
	if (sigprocmask(SIG_SETMASK, oldmask, NULL) < 0)
		ft_error(1, "signals");
	if (pid < 0)
		ft_error(1, "fork");
}

int			main(int ac, char **av, char **env)
{
	sigset_t	oldmask;
	
	(void)ac;
	if (setuid(getuid()) == -1)
		ft_error(1, av[0]);
	closeFileDescriptors(av[0]);
	resetSignalHandlers(&oldmask);
	sanitizeEnvironnement(env);
	forkDaemon(&oldmask);
	return (0);
}
