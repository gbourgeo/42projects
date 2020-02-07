/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:17:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/07 20:24:04 by gbourgeo         ###   ########.fr       */
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

	if (sv->fd_data > 0)
		return (ERR_CONNECT_TO);
	if (!ft_isdigit(sv->response[0]) || sv->response[0] != '2'
	|| !ft_isdigit(sv->response[1]) || !ft_isdigit(sv->response[2])
	|| sv->response[3] != ' '
	|| !(port = cl_addrcpy(addr, sv->response + 5, cl->version)))
		return (IS_OK);
	if ((errnb = cl_get_addrinfo(&sv->fd_data, addr, port, cl)) == IS_OK)
		errnb = cl_server_write(sv->cmd, ft_strlen(sv->cmd), &cl->server, cl);
	sv->wait_response = 2;
	ft_bzero(sv->response, sizeof(sv->response));
	ft_bzero(sv->cmd, sizeof(sv->cmd));
	free(port);
	return (errnb);
}

int				cl_response(t_server *sv, t_client *cl)
{
	int			i;

	i = 0;
	while (sv->response[i])
		if (sv->response[i] == '\n')
		{
			sv->response[i] = '\0';
			wprintw(cl->ncu.listwin, "%s\n", sv->response);
			wrefresh(cl->ncu.listwin);
			if (!sv->fct)
				return (IS_OK);
			if (sv->wait_response == 2)
				return (sv->fct(&cl->server));
			return (cl_response_parse(&cl->server, cl));
		}
		else
			i++;
	return (IS_OK);
}
