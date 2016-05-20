/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 16:09:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/02/07 16:34:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_map	*real_get_map(int fd)
{
	int			ret;
	t_map		*map;
	t_map		*tmp;

	if ((tmp = (t_map*)malloc(sizeof(*tmp))) == NULL)
		return (NULL);
	map = tmp;
	while ((ret = get_next_line(fd, &tmp->line) > 0))
	{
		if ((tmp->next = (t_map*)malloc(sizeof(*tmp))) == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	close(fd);
	if (!ret)
		return (map);
	ft_free_map(&map);
	return (NULL);
}

t_map			*get_map(const char *av)
{
	int			fd;

	if ((fd = open(av, O_RDONLY)) == -1)
		perror(av);
	else
		return (real_get_map(fd));
	return (NULL);
}
