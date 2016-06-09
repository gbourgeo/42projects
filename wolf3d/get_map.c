/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 17:05:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/27 19:01:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**map_error(char *mess, int fd, char **map)
{
	int			i;

	i = 0;
	ft_putendl_fd(mess, 2);
	ft_putendl_fd("Exiting...", 2);
	while (map && map[i])
		free(map[i++]);
	if (map)
		free(map);
	if (fd)
		close(fd);
	return (NULL);
}

static char		*special_copy(char *map, char *line, int len)
{
	int			i;
	int			j;

	i = ft_strlen(line);
	j = 0;
	ft_putstr(line);
	while (i++ < len + 1)
		ft_putchar(' ');
	i = -1;
	while (i++ < len)
	{
		if (line[j] != '\0')
		{
			if (line[j] <= ' ' || line[j] >= 127)
				map[i] = '1';
			else
				map[i] = line[j];
			j++;
		}
		else
			map[i] = '1';
	}
	map[i] = '\0';
	ft_putendl(map);
	return (map);
}

static char		**get_map_by_fd(int fd, char *av, t_env *e)
{
	char		**map;
	char		*line;
	int			ret;
	int			i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (map_error("Open() error.", 0, NULL));
	map = (char **)malloc(sizeof(*map) * (e->map_h + 1));
	while (map && (ret = get_next_line(fd, &line)) > 0)
	{
		map[i] = (char *)malloc(sizeof(**map) * (e->map_w + 1));
		if (map[i] == NULL || line == NULL)
			return (map_error("An error occured (malloc() ?).", fd, map));
		map[i] = special_copy(map[i], line, e->map_w);
		free(line);
		i++;
	}
	map[i] = NULL;
	if (ret != 0)
		return (map_error("An error occured with get_next_line().", fd, map));
	close(fd);
	return (map);
}

static char		**get_map_stats(char *av, int fd, t_env *e)
{
	char		*line;
	int			ret;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ret = ft_strlen(line);
		if (e->map_w < ret)
			e->map_w = ret;
		if (e->map_w > 4096)
			return (map_error("Map Width is too High (Over 4096).", fd, NULL));
		if (++e->map_h > 4096)
			return (map_error("Map Height is too High (Over 4096).", fd, NULL));
		free(line);
	}
	if (ret != 0)
		return (map_error("An error occured with get_next_line().", fd, NULL));
	if (e->map_w < 3)
		return (map_error("Map Width is too Low (Limit is 3).", fd, NULL));
	if (e->map_h < 3)
		return (map_error("Map Height is too Low (Limit is 3).", fd, NULL));
	if (close(fd) != 0)
		return (map_error("Closing File Error.", 0, NULL));
	return (get_map_by_fd(0, av, e));
}

char			**get_map(char *av, t_env *e)
{
	int			fd;

	fd = 0;
	if (av)
	{
		ft_putendl("Analysing your map...");
		fd = open(av, O_RDONLY);
		if (fd == -1)
		{
			perror(av);
			return (NULL);
		}
		return (get_map_stats(av, fd, e));
	}
	ft_putendl_fd("No map given. ABORT !!!!!!", 2);
	return (NULL);
}
