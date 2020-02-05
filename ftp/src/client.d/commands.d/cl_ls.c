/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 19:24:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include "cl_main.h"

int				cl_ls(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	i = 1;
	(void)buf;
	ft_strcpy(cl->server.cmd, "NLST"); // Change to LIST when implemented on server
	while (cmd[i])
	{
		ft_strncat(cl->server.cmd, " ", CMD_BUFF_SIZE);
		ft_strncat(cl->server.cmd, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(cl->server.cmd, "\n", CMD_BUFF_SIZE);
	if ((errnb = cl_server_write("PASV\n", 5, &cl->server, cl)) != IS_OK)
		return (errnb);
	cl->server.wait_response = 1;
	cl->server.fct = cl_ls_next;
	return (errnb);
}

int					cl_ls_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}

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

int					cl_ls_next(t_server *sv, t_client *cl)
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
	sv->get_data = 1;
	sv->wait_response = 1;
	ft_bzero(sv->response, sizeof(sv->response));
	ft_bzero(sv->cmd, sizeof(sv->cmd));
	sv->fct = cl_ls_end;
	free(port);
	return (errnb);
}

int					cl_ls_end(t_server *sv, t_client *cl)
{
	wprintw(cl->ncu.listwin, "%s\n", sv->response);
	wrefresh(cl->ncu.listwin);
	ft_close(&sv->fd_data);
	sv->get_data = 0;
	sv->wait_response = 0;
	ft_bzero(sv->response, sizeof(sv->response));
	ft_bzero(sv->cmd, sizeof(sv->cmd));
	sv->fct = NULL;
	return (IS_OK);
}
