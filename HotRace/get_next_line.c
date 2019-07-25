/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 23:26:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 13:13:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				get_next_line(int const fd, char ** line)
{
	static size_t	i = 0;
	static char		*tmp = NULL;

	if (fd < 0 || line == NULL)
		return (-1);
	else if (tmp == NULL)
	{
		if (!(tmp = ft_memalloc(1)) || !(tmp = create_tmp(fd, tmp)))
			return (-1);
	}
	if (tmp[i] != '\0')
	{
		if ((*line = fill_line(tmp, &i)) == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

char			*fill_line(char *tmp, size_t *i)
{
	size_t			j;
	char			*lines;

	j = 0;
	while (tmp[*i + j] != '\n' && tmp[*i + j] != '\0')
		++j;
	lines = (char*)malloc(sizeof(char) * j);
	j = 0;
	while (tmp[*i + j] != '\n' && tmp[*i + j] != '\0')
	{
		lines[j] = tmp[*i + j];
		++j;
	}
	lines[j] = '\0';
	*i += (j + 1);
	return (lines);
}

char			*create_tmp(int const fd, char *fd_tmp)
{
	int				ret;
	int				len;
	char			buf[BUFF_SIZE + 1];

	ret = 0;
	len = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		fd_tmp = ft_strjoin(fd_tmp, buf);
		len += ret;
	}
	fd_tmp[len] = '\0';
	return (fd_tmp);
}
