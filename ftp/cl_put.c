/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 17:56:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/06 09:23:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static int			cl_send_file(int ffd, t_envi *cl, char *file)
{
	int				ret;

	write(1, "\033[4mSending\033[0m : ", 19);
	ft_putstr(file);
	while ((ret = read(ffd, cl->data, DATA_SIZE)) > 0)
	{
		send(cl->fd, "\0", 1, 0);
		if (recv(cl->fd, cl->buff, BUFF_SIZE, 0) <= 0)
			cl_end("Server: disconnected", cl);
		if (cl->buff[0])
			break ;
		send(cl->fd, cl->data, ret, 0);
		if (recv(cl->fd, cl->buff, BUFF_SIZE, 0) <= 0)
			cl_end("Server: disconnected", cl);
		if (cl->buff[0])
			break ;
	}
	if (ret == -1)
		return (file_error("ERROR: read() failed", cl, CLIENT, ffd));
	else if (cl->buff[0])
		return (file_error(cl->buff, cl, CLIENT, 0));
	send(cl->fd, "OK", 2, 0);
	ft_putendl(" \033[32mOK\033[0m");
	return (ret);
}

static int			cl_send_dir_files(DIR *ret, t_envi *cl, char *path, int fd)
{
	struct dirent	*dir;

	while ((dir = readdir(ret)) && cl->rec == 0)
	{
		if (ft_strlen(path) + ft_strlen(dir->d_name) >= BUFF_SIZE)
			cl->rec = file_error("\2ERROR: file name too long.", cl, CLIENT, 1);
		else if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			ft_strcpy(cl->buff, path);
			ft_strcat(cl->buff, dir->d_name);
			if ((fd = open(cl->buff, O_RDONLY)) >= 0 &&
				fstat(fd, &cl->info) >= 0)
			{
				cl->rec = cl_check_server(fd, cl, ft_strdup(cl->buff));
				if (recv(cl->fd, cl->buff, BUFF_SIZE, 0) <= 0)
					cl_end("...", cl);
			}
			else
				cl->rec = file_error("\2ERROR: Can't open file", cl, CLIENT, 1);
			if (fd != -1)
				close(fd);
		}
	}
	free(path);
	return (cl->rec);
}

static int			cl_handle_dir(int ffd, t_envi *cl, char *directory)
{
	DIR				*ret;

	close(ffd);
	write(1, "\033[4;33mEntering\033[0m: ", 22);
	ft_putstr(directory);
	if ((ret = opendir(directory)) == NULL)
		cl->rec = file_error("\2 ERROR: Permission Denied", cl, CLIENT, 1);
	else
	{
		ft_putchar('\n');
		cl->rec = 0;
		cl->rec = cl_send_dir_files(ret, cl, ft_strjoin(directory, "/"), -1);
		closedir(ret);
	}
	send(cl->fd, "\0", 1, 0);
	write(1, "\033[4;33mLeaving\033[0m : ", 22);
	ft_putendl(directory);
	return (cl->rec);
}

int					cl_check_server(int ffd, t_envi *cl, char *file)
{
	int				ret;

	ret = 1;
	send(cl->fd, cl->buff, BUFF_SIZE, 0);
	if ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0 && !*cl->buff)
	{
		send(cl->fd, &cl->info, sizeof(cl->info), 0);
		cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	else if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	else if (*cl->buff)
		ret = file_error(cl->buff, cl, CLIENT, 0);
	else if (S_ISDIR(cl->info.st_mode))
		ret = cl_handle_dir(ffd, cl, file);
	else
		ret = cl_send_file(ffd, cl, file);
	if (file)
		free(file);
	return (ret);
}

int					cl_put(char **cmds, t_envi *cl)
{
	int				ffd;
	char			*file;

	if (!cmds[1])
		return (cl_put_help(cl));
	if ((file = ft_strrchr(cmds[1], '/')) == NULL)
		file = cmds[1];
	if ((ffd = open(cmds[1], O_RDONLY)) == -1)
		return (file_error("ERROR: Can't open file.", cl, CLIENT, 0));
	if (fstat(ffd, &cl->info) == -1)
		cl->rec = file_error("ERROR: can't get file stats", cl, CLIENT, 0);
	else
		cl->rec = cl_check_server(ffd, cl, ft_strdup(file));
	close(ffd);
	return (cl->rec);
}
