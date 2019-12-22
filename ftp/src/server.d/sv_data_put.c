/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_data_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:15:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 16:58:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		print_info(const char *s, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: %s\n", cl->fd, s);
}

int				sv_data_put(t_client *cl, t_server *sv)
{
	int		errnb;

	errnb = ERR_MALLOC;
	print_info("Successfully connected to DATA port", cl, sv);
	return (errnb);
}
