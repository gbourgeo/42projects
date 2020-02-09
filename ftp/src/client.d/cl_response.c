/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:17:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/09 04:44:21 by gbourgeo         ###   ########.fr       */
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
	while (str[i])
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

static int			cl_response_parse(t_server *sv, t_client *cl)
{
	char			addr[INET6_ADDRSTRLEN];
	char			*port;
	int				errnb;

	errnb = IS_OK;
	if (ft_isdigit(sv->response[0]) && ft_isdigit(sv->response[1])
	&& ft_isdigit(sv->response[2]) && sv->response[3] == ' ')
	{
		if (sv->response[0] > '2')
			return (cl_close_data(sv, 0, cl));
		if (ft_atoi(sv->response) == 227)
		{
			if (!(port = cl_addrcpy(addr, sv->response + 5, cl->version)))
				errnb = ERR_MALLOC;
			else if ((errnb = cl_get_addrinfo(&sv->fd_data, addr, port, cl)) == IS_OK)
				errnb = cl_server_write(sv->cmd, ft_strlen(sv->cmd), &cl->server,
				cl);
			ft_bzero(sv->cmd, sizeof(sv->cmd));
			ft_strdel(&port);
		}
		sv->wait_response--;
	}
	ft_strcpy(sv->response, sv->response + ft_strlen(sv->response) + 1);
	return (errnb);
}

int					cl_response(t_server *sv, t_client *cl)
{
	int				i;
	int				errnb;

	i = 0;
	errnb = IS_OK;
	while (sv->response[i] && errnb == IS_OK)
		if (sv->response[i] == '\n')
		{
			sv->response[i] = '\0';
			if (sv->wait_response <= 0)
				errnb = cl_close_data(&cl->server, 0, cl);
			else
				errnb = cl_response_parse(&cl->server, cl);
			i = 0;
		}
		else
			i++;
	return (errnb);
}
