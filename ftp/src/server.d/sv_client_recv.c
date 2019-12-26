/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:25:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "sv_main.h"

static int		sv_client_commands(char **cmd, t_client *cl, t_server *sv)
{
	t_command	*commands;
	int			i;
	int			size;

	commands = sv_commands(0);
	i = 0;
	size = sv_getcommandsright(cl->user.rights);
	if (!cmd[0] || !cmd[0][0])
		return (IS_OK);
	while (i < size)
		if (!ft_strcmp(commands[i].name, cmd[0]))
		{
			sv_change_working_directory(cl->home, cl->pwd);
			if (commands[i].func == sv_help)
				return (commands[i].func((char **)commands, cl, sv));
			return (commands[i].func(cmd, cl, sv));
		}
		else
			i++;
	return (sv_cmd_err(ft_get_error(ERR_COMMAND), cmd[0], cl, sv));
}

static void		print_info(char *buff, int size, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client "COLOR_YELLOW"%d"COLOR_RESET" :\"", cl->fd);
	fflush(stdout);
	write(1, buff, size);
	printf("\"\n");
}

static int		sv_buffcpy(t_client *cl, t_server *sv)
{
	char		buff[CMD_BUFF_SIZE + 1];
	char		**cmd;
	int			i;

	i = 0;
	while (cl->rd.head != cl->rd.tail)
	{
		buff[i++] = *cl->rd.head++;
		if (cl->rd.head >= cl->rd.buff + CMD_BUFF_SIZE)
			cl->rd.head = cl->rd.buff;
	}
	if (++cl->rd.head >= cl->rd.buff + CMD_BUFF_SIZE)
		cl->rd.head = cl->rd.buff;
	buff[i] = '\0';
	print_info(buff, i, cl, sv);
	if ((cmd = ft_split_whitespaces(buff)) == NULL)
		return (ERR_MALLOC);
	i = sv_client_commands(cmd, cl, sv);
	ft_tabdel(&cmd);
	return (i);
}

int				sv_client_recv(t_client *cl, t_server *sv)
{
	int		ret;
	int		errnb;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (sv_recv_error(ret));
	while (ret--)
	{
		if (*cl->rd.tail == '\n')
		{
			if ((errnb = sv_buffcpy(cl, sv)) != IS_OK)
				return (errnb);
		}
		if (++cl->rd.tail >= cl->rd.buff + CMD_BUFF_SIZE)
			cl->rd.tail = cl->rd.buff;
		if (--cl->rd.len == 0)
			cl->rd.len = (cl->rd.head > cl->rd.tail) ?
			cl->rd.head - cl->rd.tail :
			cl->rd.buff + CMD_BUFF_SIZE - cl->rd.tail;
	}
	return (IS_OK);
}
