/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 22:54:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/15 04:12:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>

static t_hist	*fill_history(int fd, t_hist *new)
{
	char		*cmd;

	cmd = NULL;
	while (get_next_line(fd, &cmd) > 0)
	{
		if (new == NULL)
		{
			new = hist_new(cmd, ft_strlen(cmd), NULL);
			if (new == NULL)
				return (new);
		}
		else
		{
			new->prev = hist_new(cmd, ft_strlen(cmd), new);
			if (new->prev == NULL)
				return (new);
			new = new->prev;
		}
		if (cmd)
			free(cmd);
		cmd = NULL;
	}
	return (new);
}

t_hist			*retreive_history(void)
{
	int			fd;
	t_hist		*new;

	if ((fd = open(data.histpath, O_RDONLY)) == -1)
		return (NULL);
	new = fill_history(fd, NULL);
	close(fd);
	return (new);
}

void			update_history(void)
{
	int			flag;
	int			fd;
	t_hist		*tmp;

	flag = O_WRONLY | O_CREAT | O_APPEND | O_TRUNC;
	if ((fd = open(data.histpath, flag, 0644)) == -1)
		return ;
	tmp = data.hist;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->prev)
	{
		if (tmp->cmd && *tmp->cmd)
			ft_putendl_fd(tmp->cmd, fd);
		tmp = tmp->prev;
	}
	close(fd);
}
