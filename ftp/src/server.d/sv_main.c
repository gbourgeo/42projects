/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 00:16:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include "sv_main.h"

static void		print_params(t_opt *opts, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		dprintf(STDERR_FILENO, "\n\t"COLOR_BOLD"-%c", opts[i].name.c);
		if (opts[i].name.str)
			dprintf(STDERR_FILENO, COLOR_RESET", "COLOR_BOLD"-%s"COLOR_RESET,
			opts[i].name.str);
		if (opts[i].param)
			dprintf(STDERR_FILENO, " %s", opts[i].param);
		if (opts[i].name.str || opts[i].param)
			dprintf(STDERR_FILENO, COLOR_RESET"\n\t");
		dprintf(STDERR_FILENO, COLOR_RESET"\t%s\n", opts[i].description);
		i++;
	}
}

static void		print_usage(const char *progname, const char *progpath)
{
	dprintf(STDERR_FILENO, "\n"COLOR_BOLD"NAME"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "%s - ftp server\n\n", progname);
	dprintf(STDERR_FILENO, COLOR_BOLD"USAGE\n\t%s"COLOR_RESET, progpath);
	dprintf(STDERR_FILENO, " ["COLOR_UNDERLINED"OPTIONS"COLOR_RESET"]... ");
	dprintf(STDERR_FILENO, COLOR_UNDERLINED"PORT"COLOR_RESET"\n\n");
	dprintf(STDERR_FILENO, COLOR_BOLD"DESCRIPTION"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "Start a File Transfert Protocol server.\n");
	print_params(sv_params(0, 0), (size_t)sv_params(1, 0));
	dprintf(STDERR_FILENO, "\n\t"COLOR_BOLD"port"COLOR_RESET);
	dprintf(STDERR_FILENO, "\tPort to listen to.\n\n");
	dprintf(STDERR_FILENO, COLOR_BOLD"AUTHOR"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "Written by Gilles Bourgeois\n");
}

int				main(int ac, char **av, char **environ)
{
	t_server		*sv;
	int				errnb[2];

	(void)ac;
	sv = &g_serv;
	errnb[0] = IS_OK;
	errnb[1] = IS_OK;
	if ((errnb[0] = ft_init(sv, sizeof(*sv), environ, av[0])) == IS_OK)
		if ((errnb[0] = sv_init_sig(sv)) == IS_OK)
			if ((errnb[0] = sv_params_get(av, sv)) == IS_OK)
				if ((errnb[0] = sv_user_file(sv)) == IS_OK)
					if ((errnb[0] = sv_get_addrinfo(sv)) == IS_OK)
						errnb[1] = sv_server_loop(sv);
	if (errnb[0] != IS_OK)
		if (ft_error(errnb[0], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath);
	if (SV_CHECK(sv->options, sv_interactive) && errnb[1] != IS_OK)
		if (ft_error(errnb[1], &sv->info) == 2)
			print_usage(sv->info.progname, sv->info.progpath);
	sv_server_end(sv);
	return (errnb[0] + errnb[1]);
}
