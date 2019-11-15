/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 15:03:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sv_main.h"

static void		print_usage(const char *progname, const char *progpath)
{
	ft_putstr_fd("\n\x1B[1mNAME\x1B[0m\n\t", 2);
	ft_putstr_fd(progname, 2);
	ft_putendl_fd(" - FTP server", 2);
	ft_putstr_fd("\n\x1B[1mUSAGE\n\t", 2);
	ft_putstr_fd(progpath, 2);
	ft_putendl_fd("\x1B[0m [\x1B[4mOPTION\x1B[0m]... [\x1B[4mPORT\x1B[0m]", 2);
	ft_putstr_fd("\n\x1B[1mDESCRIPTION\x1B[0m\n", 2);
	ft_putendl_fd("\n\t\x1B[1m-4\x1B[0m\tServer allows IpV4 only.", 2);
	ft_putendl_fd("\n\t\x1B[1m-6\x1B[0m\tServer allows IpV6 only.", 2);
	ft_putendl_fd("\n\t\x1B[1m-d\x1B[0m\tServer creates personal directory "
	"for registered users.", 2);
	ft_putendl_fd("\n\t\x1B[1m-h\x1B[0m\tPrint help and exit.", 2);
	ft_putendl_fd("\n\t\x1B[1m-i\x1B[0m\tInteractive server."
	" Prints information on STDOUT.", 2);
	ft_putendl_fd("\n\t\x1B[1m-p\x1B[0m [path]\n\t\tServer working path.", 2);
	ft_putendl_fd("\n\t\x1B[1mport\x1B[0m\tPort to listen to.", 2);
	ft_putendl_fd("\n\x1B[1mAUTHOR\x1B[0m\n\tWritten by Gilles Bourgeois.", 2);
}

int				main(int ac, char **av, char **environ)
{
	t_server	*sv;
	int			errnb[2];

	(void)ac;
	sv = &g_serv;
	errnb[0] = IS_OK;
	errnb[1] = IS_OK;
	signal(SIGINT, sv_signals_hdlr);
	if ((errnb[0] = ft_init(sv, sizeof(*sv), environ, av[0])) == IS_OK)
		if ((errnb[0] = sv_params_get(av, sv)) == IS_OK)
			if ((errnb[0] = sv_user_get(sv)) == IS_OK)
				if ((errnb[0] = sv_get_addrinfo(sv)) == IS_OK)
					errnb[1] = sv_server_loop(sv);
	sv_server_close(sv_v4, (int[2]){-1, -1}, sv);
	sv_server_close(sv_v6, (int[2]){-1, -1}, sv);
	sv_free_env(&sv->info.env);
	sv_free_user(&sv->users);
	if (errnb[0] != IS_OK)
		if (ft_error(errnb[0], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath);
	if (SV_CHECK(sv->options, sv_interactive) && errnb[1] != IS_OK)
		if (ft_error(errnb[1], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath);
	return (errnb[0] + errnb[1]);
}
