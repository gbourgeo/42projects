/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 17:58:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/06 06:55:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_receive_file(char *file, t_envi *cl)
{
	int			ffd;

	ft_putstr("\033[4;34mReceiving\033[0m: ");
	ft_putstr(file);
	if ((ffd = open(file, O_WRONLY | O_CREAT | O_TRUNC, cl->info.st_mode)) < 0)
		return (file_error("\2 ERROR: open() error.\0", cl, CLIENT, 1));
	send(cl->fd, " ", 1, 0);
	while ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0 && !*cl->buff)
	{
		send(cl->fd, " ", 1, 0);
		if ((cl->rec = recv(cl->fd, cl->data, DATA_SIZE, 0)) <= 0)
			break ;
		if ((cl->rec = write(ffd, cl->data, cl->rec)) <= 0)
			return (file_error("\2 ERROR: write() error.\0", cl, CLIENT, 1));
		send(cl->fd, " ", 1, 0);
	}
	close(ffd);
	if (cl->rec == 0)
		cl_end("Server: disconnected", cl);
	if (cl->rec == -1)
		return (file_error("\2 ERROR: recv() failed.\0", cl, CLIENT, 1));
	if (ft_strncmp(cl->buff, "OK", 2) != 0)
		return (file_error(cl->buff, cl, CLIENT, 0));
	ft_putendl(" \033[32mOK\033[0m");
	return (0);
}

int				cl_receive_dir_files(t_envi *cl)
{
	int			ret;

	send(cl->fd, " ", 1, 0);
	while ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0 && *cl->buff)
	{
		cl->buff[cl->rec] = '\0';
		if (*cl->buff == '\2')
			return (file_error(cl->buff, cl, CLIENT, 0));
		send(cl->fd, " ", 1, 0);
		if ((cl->rec = recv(cl->fd, &cl->info, sizeof(cl->info), 0)) <= 0)
			break ;
		ret = (S_ISDIR(cl->info.st_mode)) ?
			cl_get_dir(ft_strdup(cl->buff), cl) : cl_receive_file(cl->buff, cl);
		if (ret)
			break ;
		send(cl->fd, " ", 1, 0);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	else if (cl->rec == -1)
		return (file_error("\2 ERROR: recv(dir_file) fail\0", cl, CLIENT, 1));
	return (ret);
}

int				cl_get_dir(char *dir, t_envi *cl)
{
	ft_putstr("\033[4;33mCreating\033[0m  : ");
	ft_putstr(dir);
	if (mkdir(dir, cl->info.st_mode) == -1)
		ft_putstr(" (exist)");
	ft_putchar('\n');
	cl->rec = cl_receive_dir_files(cl);
	ft_putstr("\033[4;33mLeaving\033[0m  : ");
	ft_putendl(dir);
	if (dir)
		free(dir);
	return (cl->rec);
}

int				cl_get(char **cmds, t_envi *cl)
{
	char		*file;

	if (!cmds || !cmds[1])
		return (cl_get_help(cl));
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	if ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		if (cl->buff[0])
			return (file_error(cl->buff, cl, CLIENT, 0));
		send(cl->fd, " info", 5, 0);
		cl->rec = recv(cl->fd, &cl->info, sizeof(cl->info), 0);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	else if (cl->rec == -1)
		return (file_error("\2 ERROR: recv() fail.\0", cl, CLIENT, 1));
	if ((file = ft_strrchr(cmds[1], '/')) == NULL)
		file = cmds[1];
	else
		file += 1;
	if (S_ISDIR(cl->info.st_mode))
		return (cl_get_dir(ft_strdup(file), cl));
	return (cl_receive_file(file, cl));
}
