/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 22:32:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 08:19:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		illegal_option(char ill, char **av)
{
	ft_putstr_fd(*av, 2);
	ft_putstr_fd(": illegal option --", 2);
	ft_putchar_fd(ill, 2);
	ft_putstr_fd("\nusage: ", 2);
	ft_putstr_fd(*av, 2);
	ft_putstr_fd(" [-", 2);
	ft_putstr_fd(OPTIONS, 2);
	ft_putendl_fd("] [-t time] [file [command ...]]", 2);
	return (-1);
}

static int		check_args(t_env *e, char **av)
{
	int			i;
	int			j;
	char		*tmp;

	i = 1;
	ft_memset(e->opt, '\0', opt_len);
	while (av[i] && *av[i] == '-')
	{
		j = 1;
		while (av[i][j] != '\0')
		{
			tmp = ft_strchr(OPTIONS, av[i][j]);
			if (tmp == NULL)
				return (illegal_option(av[i][j], av));
			e->opt[opt_len - ft_strlen(tmp)] = 1;
			j++;
		}
		i++;
	}
	return (i);
}

static char		*check_env(char **environ)
{
	int			i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], "SHELL=", 6) == 0)
			return (environ[i] + 6);
		i++;
	}
	return ("/bin/sh");
}

int				main(int ac, char **av, char **environ)
{
	t_env		e;

	e.prog = av[0];
	ac = check_args(&e, av);
	if (ac == -1)
		return (1);
	e.shell = check_env(environ);
	e.cmd = (av[ac] == NULL || av[ac + 1] == NULL) ? NULL : &av[ac + 1];
	e.file = (av[ac] == NULL) ? "typescript" : av[ac];
	e.environ = ft_copy_env(environ, e.file, 0);
	e.oflag = O_WRONLY | O_CREAT;
	e.oflag |= (e.opt[opt_a] == 0) ? O_TRUNC : O_APPEND;
	e.fd = open(e.file, e.oflag, 0644);
	if (e.fd == -1)
		return (ft_error(1, "Can't open file ", &e));
	if (ft_start_script(&e))
		return (1);
	close(e.fd);
	ft_free_env(&e);
	return (0);
}
