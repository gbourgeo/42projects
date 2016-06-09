/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 03:15:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 12:24:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char			*ft_ptsname(int fd)
{
	static char		name[128];

	if (ioctl(fd, TIOCPTYGNAME, name) < 0)
		return (NULL);
	return (name);
}

static int			ft_open_fds(t_env *e, int *fd_m, int *fd_s)
{
	*fd_m = open("/dev/ptmx", O_RDWR | O_NOCTTY);
	if (*fd_m == -1)
		return (ft_error(0, "failed to open: /dev/ptmx", e));
	ioctl(*fd_m, TIOCPTYGRANT);
	ioctl(*fd_m, TIOCPTYUNLK);
	*fd_s = open(ft_ptsname(*fd_m), O_RDWR | O_NOCTTY);
	if (*fd_s == -1)
		return (ft_error(0, "failed to open the slave tty", e));
	return (0);
}

static void			ft_write_on(int fd_m, fd_set *set, t_env *e)
{
	char			buf[255];
	char			buf_s[255];
	int				ret;
	int				ret_s;

	ft_memset(buf, 0, 255);
	if (FD_ISSET(0, set))
	{
		ret = read(0, buf, 255);
		if (ret > 0)
			write(fd_m, buf, ret);
		if (e->opt[opt_k] && buf[ret - 1] != '\n')
			write(e->fd, buf, ret);
	}
	ft_memset(buf_s, 0, 255);
	if (FD_ISSET(fd_m, set))
	{
		ret_s = read(fd_m, buf_s, 255);
		if (ret_s > 0)
		{
			write(1, buf_s, ret_s);
			write(e->fd, buf_s, ret_s);
		}
	}
}

static void			ft_connect(t_env *e, int fd_m, fd_set *set, pid_t pid)
{
	int				ret;
	struct winsize	win;

	while (waitpid(pid, &ret, WNOHANG) != pid)
	{
		ioctl(0, TIOCGWINSZ, &win);
		ioctl(fd_m, TIOCSWINSZ, &win);
		FD_SET(0, set);
		FD_SET(fd_m, set);
		select(fd_m + 1, set, NULL, NULL, NULL);
		ft_write_on(fd_m, set, e);
	}
}

int					ft_fork(t_env *e)
{
	int				fd_m;
	int				fd_s;
	pid_t			pid;
	fd_set			set;

	if (ft_open_fds(e, &fd_m, &fd_s) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
		return (ft_execve(e, fd_m, fd_s));
	if (ft_new_term_attr(e))
		return (1);
	close(fd_s);
	FD_ZERO(&set);
	ft_connect(e, fd_m, &set, pid);
	close(fd_m);
	ft_restore_term_attr(e);
	return (0);
}
