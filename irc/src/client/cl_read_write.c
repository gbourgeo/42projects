/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/01 22:53:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/28 02:05:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

static void		read_client_command(t_client *cl)
{
	char		**cmds;
	int			i;
	static void	(*fct[])(char **, t_client *) = { CL_FUNCT1, CL_FUNCT2 };
	static char	*name[] = { COMMANDS1, COMMANDS2 };

	i = 0;
	if ((cmds = ft_split_whitespaces(cl->read)) == NULL)
		cl_error("Client: splitting command failed\n", cl);
	i = 0;
	while (name[i] && ft_strcmp(name[i], cmds[0]))
		i++;
	if (!name[i] && cl->sock == -1)
		ft_putendl("\e[31mCommand unavailable\e[0m");
	fct[i](cmds, cl);
	ft_free(&cmds);
}

void			read_client(t_client *cl)
{
	int			ret;

	ret = read(STDIN_FILENO, cl->read, BUFF);
	if (ret < 0)
		cl_error("Client: read() error.", cl);
	else if (ret == 0)
		cl_error("Disconected from server.", cl);
	cl->read[ret] = '\0';
	if (cl->sock > -1 && send(cl->sock, cl->read, ret, 0) < 0)
		cl_error("Client: send() error.", cl);
	if (*cl->read == '/')
		read_client_command(cl);
	if (cl->sock == -1 || *cl->read != '/')
		ft_strclr(cl->read);
}

void			read_server(t_client *cl)
{
	int			ret;

	ret = recv(cl->sock, cl->wr.tail, 1, 0);
	if (ret == -1)
		cl_error("Client: recv(read_server) failed", cl);
	if (ret == 0)
		cl_error("Connection closed by foreign host.", cl);
	write(1, cl->wr.tail, ret);
	if (*cl->read == '/')
		read_client_command(cl);
	cl->wr.tail++;
	if (cl->wr.tail >= cl->wr.end)
		cl->wr.tail = cl->wr.start;
	cl->wr.head++;
	if (cl->wr.head >= cl->wr.end)
		cl->wr.head = cl->wr.start;
	*cl->read = '/';
}
