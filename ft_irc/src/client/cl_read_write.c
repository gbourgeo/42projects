/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 22:53:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 16:30:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

static void			read_client_command(t_client *cl)
{
	char			**cmds;
	int				i;
	static t_cmd	com[] = { { "/away", cl_void }, {"/connect", cl_connect },
							{ "/help", cl_help }, { "/join", cl_void },
							{ "/leave", cl_void }, { "/list", cl_void },
							{ "/msg", cl_void }, { "/nick", cl_nick },
							{ "/quit", cl_quit }, { "/topic", cl_void },
							{ "/who", cl_void }, { NULL, cl_void } };

	i = 0;
	if ((cmds = ft_split_whitespaces(cl->read)) == NULL)
		cl_error("Client: splitting command failed\n", cl);
	while (com[i].name && ft_strcmp(com[i].name, cmds[0]))
		i++;
	if (!com[i].name && cl->sock == -1)
		ft_putendl("\e[31mCommand unavailable\e[0m");
	if (cl->sock == -1)
		com[i].fct(cmds, cl);
	ft_free(&cmds);
}

void				read_client(t_client *cl)
{
	int				ret;

	ret = read(STDIN_FILENO, cl->read, BUFF);
	if (ret < 0)
		cl_error("Client: read() error.", cl);
	else if (ret == 0)
		cl_error("Disconnected.", cl);
	cl->read[ret] = '\0';
	if (cl->sock == -1)
		read_client_command(cl);
	else if (send(cl->sock, cl->read, ret, 0) < 0)
		cl_error("Client: send() error.", cl);
}

void				read_server(t_client *cl)
{
	int				ret;

	ret = recv(cl->sock, cl->write, BUFF, 0);
	if (ret == -1)
		cl_error("Client: read_server: recv() failed", cl);
	if (ret == 0)
		cl_error("Connection closed by foreign host.", cl);
	write(1, cl->write, ret);
	if (*cl->read == '/')
		read_client_command(cl);
}
