/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/02 18:41:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>
#include <fcntl.h>

int				main(int ac, char **av)
{
	t_client	cl;

	(void)ac;
	ft_memset(&cl, 0, sizeof(cl));
	cl.sock = -1;
	if (BUFF <= END_CHECK_LEN || BUFF <= ft_strlen(END_CHECK))
		return (1);
	if (!av[1] || !av[2] || cl_getaddrinfo(av[1], av[2], &cl))
	{
		ft_putendl("Usage: ./client [address] [port]");
		ft_putendl("\e[34mYou can type /help for a list of commands.\e[0m");
	}
	cl_loop(&cl);
	return (0);
}
