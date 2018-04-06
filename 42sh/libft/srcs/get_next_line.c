/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 23:26:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 06:25:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_free(t_gnl *tmp, t_gnl **gnl)
{
	if (tmp->copy)
		free(tmp->copy);
	tmp->copy = NULL;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	else
		*gnl = tmp->next;
	free(tmp);
	tmp = NULL;
}

static int	analyse_line(char **line, t_gnl *tmp, t_gnl **gnl)
{
	char	*pt;

	pt = ft_strjoin(tmp->copy, *line);
	if (tmp->copy)
		free(tmp->copy);
	tmp->copy = pt;
	if ((pt = ft_strchr(tmp->copy, '\n')) == NULL)
		return (0);
	*pt = '\0';
	free(*line);
	*line = ft_strdup(tmp->copy);
	if (*(pt + 1))
	{
		pt = ft_strdup(pt + 1);
		free(tmp->copy);
		tmp->copy = pt;
	}
	else
		gnl_free(tmp, gnl);
	return (1);
}

static int	create_line(int const fd, char **line, t_gnl *tmp, t_gnl **gnl)
{
	int				ret;

	ret = 0;
	if ((*line = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (tmp->copy && (analyse_line(line, tmp, gnl)) == 1)
		return (1);
	while ((ret = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if ((analyse_line(line, tmp, gnl)) == 1)
			return (1);
		ft_bzero(*line, BUFF_SIZE + 1);
	}
	free(*line);
	*line = ft_strdup(tmp->copy);
	gnl_free(tmp, gnl);
	return ((*line) ? 1 : 0);
}

static int	check_struct(int const fd, char **line, t_gnl **gnl)
{
	t_gnl			*tmp;

	tmp = *gnl;
	while (tmp->fd != fd && tmp->next)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return ((create_line(fd, line, tmp, gnl)));
	if ((tmp->next = malloc(sizeof(*tmp))) == NULL)
		return (-1);
	tmp->next->fd = fd;
	tmp->next->copy = NULL;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	return ((create_line(fd, line, tmp->next, gnl)));
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl		*gnl = NULL;

	if (fd >= 0 && line != NULL && BUFF_SIZE > 0)
	{
		if (gnl == NULL)
		{
			gnl = malloc(sizeof(*gnl));
			if (gnl == NULL)
				return (-1);
			gnl->fd = fd;
			gnl->copy = NULL;
			gnl->next = NULL;
			gnl->prev = NULL;
			return ((create_line(fd, line, gnl, &gnl)));
		}
		return (check_struct(fd, line, &gnl));
	}
	return (-1);
}
