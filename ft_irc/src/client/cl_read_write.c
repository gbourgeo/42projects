/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 22:53:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 04:43:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

static char			*ft_strtoupper(char *str)
{
	while (str && *str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
	return (str);
}

static void			read_command(t_client *cl)
{
	char			**args;
	char			*save;
	int				i;
	static t_cmd	cmd[] = { CONNECT, HELP, NICK, PASS, QUIT, USER, END };

	i = 0;
	if ((args = ft_split_whitespaces(cl->read)) == NULL)
		cl_error("Client: split failed\n", cl);
	save = ft_strdup(args[0]);
	ft_strtoupper(save);
	while (cmd[i].name && ft_strcmp(cmd[i].name, save))
		i++;
	cmd[i].fct(args, cl);
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
		cl_error("Connection closed by foreign host.", cl);
	write(STDOUT_FILENO, cl->write, ret);
}
