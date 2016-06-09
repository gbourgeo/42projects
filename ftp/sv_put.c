/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/07 11:01:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		sv_receive_file(int ffd, t_envi *e)
{
	send(e->fd, "\0", 1, 0);
	while ((e->rec = recv(e->fd, e->buff, BUFF_SIZE, 0)) > 0 && !e->buff[0])
	{
		send(e->fd, "\0", 1, 0);
		if ((e->rec = recv(e->fd, e->data, DATA_SIZE, 0)) <= 0)
			break ;
		if (write(ffd, e->data, e->rec) == -1)
			return (file_error("\2 ERROR: server: write() fail", e, SERVER, 1));
		send(e->fd, "\0", 1, 0);
	}
	if (e->rec <= 0)
		sv_client_end(NULL, e);
	e->buff[e->rec] = '\0';
	return (0);
}

int				sv_handle_file(char *file, t_envi *e)
{
	int			ret;
	int			ffd;

	if (e->success)
	{
		write(1, "Receiving: ", 11);
		ft_putstr(file);
	}
	if ((ffd = open(file, O_WRONLY | O_CREAT | O_TRUNC, e->info.st_mode)) < 0)
		return (file_error(" ERROR: server : can't open file", e, SERVER, 1));
	ret = sv_receive_file(ffd, e);
	close(ffd);
	if (!ret && e->success)
	{
		write(1, " ", 1);
		ft_putendl(e->buff);
	}
	return (ret);
}

static int		sv_receive_dir_files(t_envi *e)
{
	int			ret;

	ret = 1;
	send(e->fd, "\0", 1, 0);
	while ((e->rec = recv(e->fd, e->buff, BUFF_SIZE, 0)) > 0 && *e->buff)
	{
		e->buff[e->rec] = '\0';
		if (*e->buff == '\2')
			return (file_error(e->buff, e, SERVER, 0));
		send(e->fd, "\0", 1, 0);
		if ((e->rec = recv(e->fd, &e->info, sizeof(e->info), 0)) <= 0)
			break ;
		ret = (S_ISDIR(e->info.st_mode)) ? sv_handle_dir(e->buff, e) :
			sv_handle_file(e->buff, e);
		send(e->fd, "\0", 1, 0);
	}
	if (e->rec <= 0)
		sv_client_end(NULL, e);
	return (ret);
}

int				sv_handle_dir(char *dir, t_envi *e)
{
	if (e->success)
	{
		ft_putstr("\033[4;33mCreating\033[0m  : ");
		ft_putstr(dir);
	}
	if (mkdir(dir, e->info.st_mode) == -1)
		write(1, " (exist)", 8);
	ft_putchar('\n');
	e->rec = sv_receive_dir_files(e);
	if (e->success)
	{
		ft_putstr("\033[4;33mLeaving\033[0m  : ");
		ft_putendl(dir);
	}
	return (e->rec);
}

int				sv_put(char **cmds, t_envi *e)
{
	char		*file;

	send(e->fd, "\0", 1, 0);
	if ((e->rec = recv(e->fd, &e->info, sizeof(e->info), 0)) == 0)
		sv_client_end(NULL, e);
	if ((file = ft_strrchr(cmds[1], '/')) == NULL)
		file = cmds[1];
	if (S_ISDIR(e->info.st_mode))
		return (sv_handle_dir(file, e));
	return (sv_handle_file(file, e));
}
