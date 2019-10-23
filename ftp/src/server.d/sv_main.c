/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 18:52:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sv_main.h"

int			main(int ac, char **av)
{
	t_server	*sv;
	int			errnb[2];

	(void)ac;
	sv = &serv;
	errnb[0] = IS_OK;
	errnb[1] = IS_OK;
	signal(SIGINT, sv_signals_hdlr);
	if ((errnb[0] = ft_init(sv, sizeof(*sv), SERVER, av[0])) == IS_OK)
		if ((errnb[0] = sv_params(av, sv)) == IS_OK)
			if ((errnb[0] = sv_getaddrinfo(sv)) == IS_OK)
				errnb[1] = sv_loop(sv);
	sv_server_close(v4, (int[2]){0, -1}, sv);
	sv_server_close(v6, (int[2]){0, -1}, sv);
	sv_free_env(&sv->info.env);
	if (errnb[0] != IS_OK)
		ft_error(errnb[0], &sv->info);
	if (sv->interactive && errnb[1] != IS_OK)
		ft_error(errnb[1], &sv->info);
	return (0);
}
