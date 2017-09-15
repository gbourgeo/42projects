/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:45:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/15 18:26:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

static void print_map(char **tab)
{
	int i;
	int j;

	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
			write(1, &tab[j][i++], 1);
		write(1, "\n", 1);
		j++;
	}
}

static void change_map(char **tab, int *found)
{
	int		i;
	int		j;

	j = 0;
	while (j <= found[2])
	{
		i = 0;
		while (i <= found[2])
		{
			tab[found[1] + j][found[0] + i] = 'X';
			i++;
		}
		j++;
	}
}

static int search_o(char **tab, int x, int y, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= len)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		i++;
	}
	i = len;
	while (j <= len)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		j++;
	}
	j = len;
	while (i >= 0)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		i--;
	}
	i = 0;
	while (j >= 0)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		j--;
	}
	return 1;
}

static void	resolve(char **tab)
{
	int		found[3]; // [0]:x [1]:y [2]:length
	int		x;
	int		y;
	int		len;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			len = 0;
			while (tab[y + len] && tab[y][x + len])
			{
				if (search_o(tab, x, y, len) == 0)
					break;
				if (len > found[2])
				{
					found[0] = x;
					found[1] = y;
					found[2] = len;
				}
				len++;
			}
			x++;
		}
		y++;
	}
	change_map(tab, found);
}

static char **get_tab(char *map)
{
	char	**tab;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			len++;
		i++;
	}
	if ((tab = malloc(sizeof(*tab) * (len + 1))) == NULL)
		return NULL;
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			map[i] = '\0';
			if (j == 0)
				len = i;
			tab[j++] = &map[i - len];
		}
		i++;
	}
	tab[j] = NULL;
	return tab;
}

static int ft_strcpy(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return i;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return i;
}

static char *get_map(int fd, char *old)
{
	char buff[512];
	int ret;
	int i;
	char *map;

	map = NULL;
	i = 0;
	while ((ret = read(fd, buff, 511)) > 0)
	{
		buff[ret] = '\0';
		old = map;
		if ((map = malloc(i + ret + 1)) == NULL)
			continue ;
		i = ft_strcpy(map, old);
		ft_strcpy(&map[i], buff);
		if (old)
			free(old);
	}
	return map;
}

int main(int ac, char ** av)
{
	int fd;
	char *map;
	char **tab;

	if (ac != 2)
		return 1;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return 1;
	if ((map = get_map(fd, NULL)) == NULL)
		return 1;
	close(fd);
	if ((tab = get_tab(map)) == NULL)
		return 1;
	resolve(tab);
	print_map(tab);
	return 0;
}
