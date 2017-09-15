/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:52:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/15 18:54:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_strcpy(char *s1, char *s2)
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

char		*get_map(int fd, char *old)
{
	char	buff[512];
	int		ret;
	int		i;
	char	*map;

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
