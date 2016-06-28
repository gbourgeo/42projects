/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:53:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/resource.h>
#include <signal.h>

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
	size_t			i;

	i = 0;
	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		sv_error("ERROR: Getrlimit(RLIMIT_NOFILE)", e);
	e->members = 0;
	e->maxfd = (MAX_CLIENT < rlp.rlim_cur) ? MAX_CLIENT : rlp.rlim_cur;
	while (i <= e->maxfd)
		ft_memset(&e->fds[i++], 0, sizeof(*e->fds));
	e->chan = (t_chan *)malloc(sizeof(*e->chan));
	if (e->chan == NULL)
		sv_error("ERROR: malloc() of chan", e);
	ft_strncpy(e->chan->name, "Global", CHAN_SIZE + 1);
	e->chan->users = 1;
	e->chan->next = NULL;
}

int					main(int ac, char **av)
{
	t_env			e;

	if (ac < 2 || ac > 3)
		ft_usage(av[0]);
	sv_verbose(av, &e);
	sv_init_env(&e);
	signal(SIGPIPE, SIG_IGN);
	if (av[1][0] != '-')
		sv_getaddrinfo(av[1], &e, 1);
	else
		sv_getaddrinfo(av[2], &e, 1);
	e.fds[0].type = FD_SERVER;
	ft_strcpy(e.fds[0].name, "** GOD **");
	e.fds[0].fct_read = sv_accept;
	e.fds[0].fct_write = NULL;
	sv_loop(&e);
	return (0);
}
