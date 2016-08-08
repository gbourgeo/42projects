/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/30 14:43:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_prompt(t_client *cl)
{
	ft_putstr(cl->name);
	ft_putstr(" \e[32m>\e[0m");
}

void			cl_loop(t_client *cl)
{
	int			max;

	while (42)
	{
		if (cl->sock == -1)
			cl_prompt(cl);
		FD_ZERO(&cl->fds);
		if (cl->sock > -1)
			FD_SET(cl->sock, &cl->fds);
		FD_SET(STDIN_FILENO, &cl->fds);
		max = (cl->sock > STDIN_FILENO) ? cl->sock : STDIN_FILENO;
		if (select(max + 1, &cl->fds, NULL, NULL, NULL) == -1)
			cl_error("Client: select() failed.", cl);
		if (cl->sock > -1 && FD_ISSET(cl->sock, &cl->fds))
			read_server(cl);
		if (FD_ISSET(STDIN_FILENO, &cl->fds))
			read_client(cl);
	}
}
