/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/25 01:45:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sv_main.h"

static void		print_params(t_opt *opts, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("\n\t\x1B[1m-", 2);
		ft_putchar_fd(opts[i].name.c, 2);
		if (opts[i].name.str)
		{
			ft_putstr_fd("\x1B[0m, \x1B[1m-", 2);
			ft_putstr_fd(opts[i].name.str, 2);
		}
		ft_putstr_fd("\x1B[0m", 2);
		if (opts[i].param)
		{
			ft_putstr_fd(" ", 2);
			ft_putstr_fd(opts[i].param, 2);
		}
		if (opts[i].name.str || opts[i].param)
			ft_putstr_fd("\x1B[0m\n\t", 2);
		ft_putchar_fd('\t', 2);
		ft_putendl_fd(opts[i].description, 2);
		i++;
	}
}

static void		print_usage(const char *progname, const char *progpath,
t_opt *opts, int size)
{
	ft_putstr_fd("\n\x1B[1mNAME\x1B[0m\n\t", 2);
	ft_putstr_fd(progname, 2);
	ft_putendl_fd(" - FTP server", 2);
	ft_putstr_fd("\n\x1B[1mUSAGE\n\t", 2);
	ft_putstr_fd(progpath, 2);
	ft_putstr_fd("\x1B[0m [\x1B[4mOPTIONS\x1B[0m]... ", 2);
	ft_putendl_fd("\x1B[4mPORT\x1B[0m", 2);
	ft_putstr_fd("\n\x1B[1mDESCRIPTION\x1B[0m\n", 2);
	print_params(opts, size);
	ft_putendl_fd("\n\t\x1B[1mport\x1B[0m\tPort to listen to.", 2);
	ft_putendl_fd("\n\x1B[1mAUTHOR\x1B[0m\n\tWritten by Gilles Bourgeois.", 2);
}

int				main(int ac, char **av, char **environ)
{
	t_server	*sv;
	int			errnb[2];
	static t_opt	opts[] = {
		PRM_4, PRM_6, PRM_D, PRM_H, PRM_I, PRM_P, PRM_U,
	};

	ac = sizeof(opts) / sizeof(opts[0]);
	sv = &g_serv;
	errnb[0] = IS_OK;
	errnb[1] = IS_OK;
	signal(SIGINT, sv_signals_hdlr);
	if ((errnb[0] = ft_init(sv, sizeof(*sv), environ, av[0])) == IS_OK)
		if ((errnb[0] = sv_params_get(av, opts, ac, sv)) == IS_OK)
			if ((errnb[0] = sv_user_file(sv)) == IS_OK)
				if ((errnb[0] = sv_get_addrinfo(sv)) == IS_OK)
					errnb[1] = sv_server_loop(sv);
	sv_server_end(sv);
	if (errnb[0] != IS_OK)
		if (ft_error(errnb[0], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath, opts, ac);
	if (SV_CHECK(sv->options, sv_interactive) && errnb[1] != IS_OK)
		if (ft_error(errnb[1], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath, opts, ac);
	return (errnb[0] + errnb[1]);
}
