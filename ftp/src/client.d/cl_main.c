/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 17:01:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include <errno.h>
#include "cl_main.h"
#include "cl_struct.h"

static void			print_params(t_opt *opts, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		dprintf(STDERR_FILENO, "\n\t"FTP_BOLD"-%c", opts[i].c);
		if (opts[i].str)
			dprintf(STDERR_FILENO, FTP_RESET", "FTP_BOLD"-%s"FTP_RESET,
			opts[i].str);
		if (opts[i].param)
			dprintf(STDERR_FILENO, " %s", opts[i].param);
		if (opts[i].str || opts[i].param)
			dprintf(STDERR_FILENO, FTP_RESET"\n\t");
		dprintf(STDERR_FILENO, FTP_RESET"\t%s\n", opts[i].description);
		i++;
	}
}

static void			print_usage(const char *progname, const char *progpath)
{
	dprintf(STDERR_FILENO, "\n"FTP_BOLD"NAME"FTP_RESET"\n\t");
	dprintf(STDERR_FILENO, "%s - ftp client\n\n", progname);
	dprintf(STDERR_FILENO, FTP_BOLD"USAGE\n\t%s"FTP_RESET, progpath);
	dprintf(STDERR_FILENO, " ["FTP_UNDERLINED"OPTIONS"FTP_RESET"]... ");
	dprintf(STDERR_FILENO, FTP_UNDERLINED"ADDR"FTP_RESET" ");
	dprintf(STDERR_FILENO, FTP_UNDERLINED"PORT"FTP_RESET"\n\n");
	dprintf(STDERR_FILENO, FTP_BOLD"DESCRIPTION"FTP_RESET"\n\t");
	dprintf(STDERR_FILENO, "Start a File Transfert Protocol client.\n");
	print_params(cl_params(0), (size_t)cl_params(1));
	dprintf(STDERR_FILENO, "\n\t"FTP_BOLD"addr"FTP_RESET);
	dprintf(STDERR_FILENO, "\tAddress to connect to.\n\n");
	dprintf(STDERR_FILENO, "\n\t"FTP_BOLD"port"FTP_RESET);
	dprintf(STDERR_FILENO, "\tPort to connect to.\n");
	dprintf(STDERR_FILENO, FTP_BOLD"AUTHOR"FTP_RESET"\n\t");
	dprintf(STDERR_FILENO, "Written by Gilles Bourgeois\n");
}

int					main(int ac, char **av, char **environ)
{
	t_client	*cl;
	int			errnb;

	(void)ac;
	cl = &g_cl;
	errno = 0;
	if ((errnb = ft_init(cl, sizeof(*cl), environ, av[0])) == IS_OK)
		if ((errnb = cl_init(environ, &cl->info.env)) == IS_OK)
			if ((errnb = cl_params_get(av, cl)) == IS_OK)
				if ((errnb = cl_client_signals(cl)) == IS_OK)
					if ((errnb = cl_history_init(cl)) == IS_OK)
						if ((errnb = cl_ncurses_init(cl)) == IS_OK)
							errnb = cl_client_loop(cl);
	cl_client_end(cl);
	if (errnb != IS_OK)
		if (ft_error(errnb, &cl->info) == 2)
			print_usage(cl->info.progname, cl->info.progpath);
	return (errnb);
}
