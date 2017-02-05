/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 22:54:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/05 01:32:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>

static t_hist	*fill_history(int fd, t_hist *new)
{
	char		*cmd;
	size_t		len;

	while (get_next_line(fd, &cmd) > 0)
	{
		len = ft_strlen(cmd);
		while (new->cmd_size <= len)
			new->cmd_size += CMD_SIZE;
		if ((new->cmd = (char *)malloc(new->cmd_size)) == NULL)
			break ;
		ft_strncpy(new->cmd, cmd, new->cmd_size);
		if ((new->prev = (t_hist *)malloc(sizeof(*new))) == NULL)
			break ;
		ft_memset(new->prev, 0, sizeof(*new));
		new->prev->next = new;
		new = new->prev;
	}
	new->cmd = ft_strnew(CMD_SIZE);
	new->cmd_size = CMD_SIZE;
	return (new);
}

t_hist			*retreive_history(void)
{
	int			fd;
	t_hist		*new;

	if ((fd = open(e.histpath, O_RDONLY)) == -1)
		return (NULL);
	if ((new = (t_hist *)malloc(sizeof(*new))))
	{
		ft_memset(new, 0, sizeof(*new));
		new = fill_history(fd, new);
	}
	close(fd);
	return (new);
}

void			update_history(void)
{
	int			flag;
	int			fd;
	t_hist		*tmp;

	flag = O_WRONLY | O_CREAT | O_APPEND | O_TRUNC;
	if ((fd = open(e.histpath, flag, 0644)) == -1)
		return ;
	tmp = e.hist;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->cmd && *tmp->cmd)
			ft_putendl_fd(tmp->cmd, fd);
		tmp = tmp->prev;
	}
}
