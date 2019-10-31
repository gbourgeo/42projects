/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 16:36:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sv_main.h"

static void		print_usage(const char *progpath)
{
	ft_putstr_fd("\nUsage: ", 2);
	ft_putstr_fd(progpath, 2);
	ft_putendl_fd(" [-i46d] [-p [path]] [port]", 2);
	ft_putendl_fd("\t-i\t\tInteractive server.", 2);
	ft_putendl_fd("\t-4\t\tIp version 4 only.", 2);
	ft_putendl_fd("\t-6\t\tIp version 6 only.", 2);
	ft_putendl_fd("\t-d\t\tCreate a directory for all registered users.", 2);
	ft_putendl_fd("\t-p [path]\tServer working path.", 2);
	ft_putendl_fd("\tport\t\tPort to listen to.", 2);
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
			print_usage(sv->info.progpath);
	if (SV_CHECK(sv->options, sv_interactive) && errnb[1] != IS_OK)
		if (ft_error(errnb[1], &sv->info) == 2)
			print_usage(sv->info.progpath);
	return (errnb[1]);
}
