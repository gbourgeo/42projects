/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 22:53:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 03:33:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

static void			read_command(t_client *cl)
{
	char			**args;
	int				i;
	static t_cmd	cmd[] = { CONNECT, HELP, NICK, PASS, QUIT, USER, END };

	i = 0;
	if (*cl->read == '\n')
		return ;
	if ((args = ft_split_whitespaces(cl->read)) == NULL)
		cl_error("Client: split failed\n", cl);
	if (*args && **args)
	{
		while (cmd[i].name && sv_strcmp(cmd[i].name, args[0]))
			i++;
		cmd[i].fct(args, cl);
	}
	ft_free(&args);
}

void				read_client(t_client *cl)
{
	int				ret;

	ret = read(STDIN_FILENO, cl->read, BUFF);
	if (ret < 0)
		cl_error("Client: read() error.", cl);
	if (ret == 0)
		cl_error("Disconnected.", cl);
	cl->read[ret] = '\0';
	if (cl->sock == -1)
		read_command(cl);
	else if (send(cl->sock, cl->read, ret, 0) < 0)
		cl_error("Client: send() error.", cl);
	ft_strclr(cl->read);
}

void				read_server(t_client *cl)
{
	int				ret;

	ret = recv(cl->sock, cl->write, BUFF, 0);
	if (ret == -1)
		cl_error("Client: read_server: recv() failed", cl);
	if (ret == 0)
	{
		ft_putendl("Connection closed by foreign host.");
		close(cl->sock);
		cl->sock = -1;
	}
	write(STDOUT_FILENO, cl->write, ret);
}
