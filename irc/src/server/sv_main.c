/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/10 07:54:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/resource.h>
#include <signal.h>
#include <time.h>

static void			ft_usage(char ill, char *prog_name)
{
	ft_putstr_fd(prog_name, 2);
	if (ill)
	{
		ft_putstr_fd(": Illegal option -- [", 2);
		ft_putchar_fd(ill, 2);
		ft_putstr_fd("]\n", 2);
	}
	else
		ft_putstr_fd(": Missing parameter\n", 2);
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(" [-v] <port>", 2);
	ft_putstr_fd("\t-v\t\tInteractive server.\n", 2);
	ft_putstr_fd("\t\t\tIt will print info about the server activity.\n", 2);
	ft_putstr_fd("\t<port>\t\tThe port that will receive connections.\n", 2);
	exit(EXIT_FAILURE);
}

static void			get_opt(char **av, int *i, t_env *e)
{
	int				j;

	j = 1;
	while (av[*i][j])
	{
		if (av[*i][j] == 'v')
			e->verb = 1;
		else
			ft_usage(av[*i][j], av[0]);
		j++;
	}
}

static void			sv_getopt(char **av, t_env *e)
{
	int				i;

	i = 1;
	e->verb = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			get_opt(av, &i, e);
		else if (!*e->port)
			ft_strncpy(e->port, av[i], PORT_LEN);
		i++;
	}
	if (!*e->port)
		ft_usage(0, av[0]);
}

static void			sv_init_env(t_env *e)
{
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		sv_error("ERROR: Getrlimit(RLIMIT_NOFILE)", e);
	if (MAX_CLIENT > rlp.rlim_cur)
		sv_error("MAX_CLIENT > rlim_cur. Check MAX_CLIENT and reduce it.", e);
	ft_memset(&e->conf, 0, sizeof(e->conf));
	get_conf_file(e);
	ft_strcpy(e->userid, "1234AAAAA");
}

int					main(int ac, char **av)
{
	time_t			date;

	if (ac < 2 || ac > 5)
		ft_usage(0, av[0]);
	ft_memset(&e, 0, sizeof(e));
	sv_getopt(av, &e);
	sv_init_env(&e);
	sv_init_server(&e);
	sv_signals();
	date = time(NULL);
	e.creation = ctime(&date);
	sv_loop(&e);
	return (0);
}
