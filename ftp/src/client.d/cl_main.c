/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 23:38:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef __linux__
#  define _POSIX_C_SOURCE 200809L
# endif
#include <unistd.h>
#include "cl_main.h"

static void		print_params(t_opt *opts, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		dprintf(STDERR_FILENO, "\n\t"COLOR_BOLD"-%c", opts[i].c);
		if (opts[i].str)
			dprintf(STDERR_FILENO, COLOR_RESET", "COLOR_BOLD"-%s"COLOR_RESET,
			opts[i].str);
		if (opts[i].param)
			dprintf(STDERR_FILENO, " %s", opts[i].param);
		if (opts[i].str || opts[i].param)
			dprintf(STDERR_FILENO, COLOR_RESET"\n\t");
		dprintf(STDERR_FILENO, COLOR_RESET"\t%s\n", opts[i].description);
		i++;
	}
}

static void			print_usage(const char *progname, const char *progpath)
{
	dprintf(STDERR_FILENO, "\n"COLOR_BOLD"NAME"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "%s - ftp client\n\n", progname);
	dprintf(STDERR_FILENO, COLOR_BOLD"USAGE\n\t%s"COLOR_RESET, progpath);
	dprintf(STDERR_FILENO, " ["COLOR_UNDERLINED"OPTIONS"COLOR_RESET"]... ");
	dprintf(STDERR_FILENO, COLOR_UNDERLINED"PORT"COLOR_RESET" ");
	dprintf(STDERR_FILENO, COLOR_UNDERLINED"ADDR"COLOR_RESET"\n\n");
	dprintf(STDERR_FILENO, COLOR_BOLD"DESCRIPTION"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "Start a File Transfert Protocol client.\n");
	print_params(cl_params(0), (size_t)cl_params(1));
	dprintf(STDERR_FILENO, "\n\t"COLOR_BOLD"port"COLOR_RESET);
	dprintf(STDERR_FILENO, "\tPort to connect to.\n");
	dprintf(STDERR_FILENO, "\n\t"COLOR_BOLD"addr"COLOR_RESET);
	dprintf(STDERR_FILENO, "\tAddress to connect to.\n\n");
	dprintf(STDERR_FILENO, COLOR_BOLD"AUTHOR"COLOR_RESET"\n\t");
	dprintf(STDERR_FILENO, "Written by Gilles Bourgeois\n");
}

int					main(int ac, char **av, char **environ)
{
	t_client	*cl;
	int			errnb;

	(void)ac;
	cl = &client;
	if ((errnb = ft_init(cl, sizeof(*cl), environ, av[0])) == IS_OK)
		if ((errnb = cl_client_signals(cl)) == IS_OK)
			if ((errnb = cl_params_get(av, cl)) == IS_OK)
				if ((errnb = cl_get_addrinfo(cl)) == IS_OK)
					printf("OK\n");
				// errnb = cl_client_loop(cl);
	if (errnb != IS_OK)
		if (ft_error(errnb, &cl->info) == 2)
			print_usage(cl->info.progname, cl->info.progpath);
	cl_client_end(cl);
	return (errnb);
}
