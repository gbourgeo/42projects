/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 23:26:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 14:31:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	create_line(int const fd, char **line);
static int	check_copy(char **line, char **copy);
static int	analyse_line(char **line, char **copy);

int			get_next_line(int const fd, char ** line)
{
	if (fd >= 0 && line != NULL && BUFF_SIZE >= 0)
		return ((create_line(fd, line)));
	return (-1);
}

static int	create_line(int const fd, char **line)
{
	static char		*copy;
	int				ret;

	ret = 0;
	if ((*line = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (copy != NULL)
	{
		if ((check_copy(line, &copy)) == 1)
			return (1);
	}
	else
		copy = ft_strnew(1);
	while ((ret = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if ((analyse_line(line, &copy)) == 1)
			return (1);
	}
	return (ret);
}

static int	check_copy(char **line, char **copy)
{
	char	*pt;
	size_t	cp;
	size_t	p;

	pt = ft_strchr(*copy, '\n');
	cp = ft_strlen(*copy);
	if (pt != NULL)
	{
		p = ft_strlen(pt);
		*line = ft_strsub(*copy, 0, (cp - p));
		*copy = ft_strsub(*copy, (cp - p + 1), (p - 1));
		return (1);
	}
	return (0);
}

static int	analyse_line(char **line, char **copy)
{
	char	*pt;
	size_t	c;
	size_t	p;

	pt = ft_strchr(*line, '\n');
	c = 0;
	p = 0;
	if (pt != NULL)
	{
		*copy = ft_strjoin(*copy, *line);
		pt = ft_strchr(*copy, '\n');
		c = ft_strlen(*copy);
		p = ft_strlen(pt);
		*line = ft_strsub(*copy, 0, (c - p));
		*copy = ft_strsub(*copy, (c - p + 1), (p - 1));
		return (1);
	}
	*copy = ft_strjoin(*copy, *line);
	return (0);
}
