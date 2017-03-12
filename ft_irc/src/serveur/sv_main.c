/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:09:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/resource.h>
#include <signal.h>
#include <time.h>

static void			ft_usage(char *prog_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(" [-v] [port]", 2);
	ft_putstr_fd("Usage:  -v\tInteractive server.\n", 2);
	exit(EXIT_FAILURE);
}

static void			sv_verbose(char **av, t_env *e)
{
	int				i;
	int				j;

	i = 1;
	e->verb = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][j] == 'v')
					e->verb = 1;
				else
					return (ft_usage(av[0]));
				j++;
			}
		}
		i++;
	}
}

static void			sv_init_env(t_env *e)
{
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		sv_error("ERROR: Getrlimit(RLIMIT_NOFILE)", e);
	if (MAX_CLIENT > rlp.rlim_cur)
		sv_error("MAX_CLIENT > rlim_cur. Check MAX_CLIENT and reduce it.", e);
	e->users = get_users_list();
/* 	e->members = 0; */
/* 	e->fds = NULL; */
/* 	e->chan = NULL; */
}

static void			sv_signals(void)
{
	signal(SIGWINCH, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGINT, sv_quit);
	signal(SIGTERM, sv_quit);
	signal(SIGBUS, sv_quit);
	signal(SIGUSR1, SIG_IGN);
}

int					main(int ac, char **av)
{
	time_t			date;

	if (ac < 2 || ac > 3)
		ft_usage(av[0]);
	ft_memset(&e, 0, sizeof(e));
	sv_verbose(av, &e);
	sv_init_env(&e);
	sv_signals();
	sv_init_server(av, &e);
	date = time(NULL);
	e.creation = ctime(&date);
	sv_loop(&e);
	return (0);
}
