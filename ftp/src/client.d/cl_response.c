/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:17:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 17:12:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include "cl_main.h"

static char			*cl_addrcpy(char addr[], char str[], int version)
{
	int				i;
	unsigned short	port;
	char			*nb1;
	char			*nb2;

	i = 0;
	while (str[i] && i < INET6_ADDRSTRLEN)
	{
		if (str[i] == ',')
			addr[i] = (version == 0) ? '.' : ':';
		else
			addr[i] = str[i];
		i++;
	}
	addr[i] = '\0';
	if (!(nb2 = ft_strrchr(addr, (version == 0) ? '.' : ':')))
		return (NULL);
	*nb2++ = '\0';
	if (!(nb1 = ft_strrchr(addr, (version == 0) ? '.' : ':')))
		return (NULL);
	*nb1++ = '\0';
	port = ft_atoi(nb1) << 8;
	port = port + ft_atoi(nb2);
	return (ft_itoa(port));
}

static int			cl_connect_back(t_server *sv, t_client *cl)
{
	char		addr[INET6_ADDRSTRLEN + 1];
	char		*port;
	int			errnb;

	if (!(port = cl_addrcpy(addr, sv->response + 5, cl->version)))
		errnb = ERR_MALLOC;
	else if ((errnb = cl_get_addrinfo(&sv->fd_data, addr, port, cl)) == IS_OK)
		errnb = cl_server_write(sv->cmd, &cl->server, cl);
	if (!cl->precmd)
		ft_bzero(sv->response, sizeof(sv->response));
	ft_strdel(&port);
	return (errnb);
}

int					cl_response(t_server *sv, t_client *cl)
{
	int				errnb;

	errnb = IS_OK;
	if (!ft_strchr(sv->response, '\n') || !is_valid_response(sv->response))
		return (IS_OK);
	if (sv->response[0] > '2')
	{
		cl_server_close_data(sv);
		return (IS_OK);
	}
	if (ft_atoi(sv->response) == 227)
		errnb = cl_connect_back(sv, cl);
	sv->wait_response--;
	return (errnb);
}
