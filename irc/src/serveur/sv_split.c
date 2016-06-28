/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 23:26:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:12:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdlib.h>

static int	tab_lines(t_buf *s)
{
	int		lines;
	char	*str;

	lines = 0;
	str = s->head;
	while (str != s->tail)
	{
		if (*str != ' ' && (*str < 9 || *str > 13))
		{
			lines += 1;
			while (*str != ' ' && (*str < 9 || *str > 13) && str != s->tail)
			{
				if (str >= s->end)
					str = s->start;
				else
					str++;
			}
		}
		else
			str++;
	}
	return (lines);
}

static int	line_len(char *str, t_buf *buf)
{
	int		i;

	i = 0;
	while (*str != ' ' && (*str < 9 || *str > 13) && str != buf->tail)
	{
		if (str >= buf->end)
			str = buf->start;
		else
		{
			i += 1;
			str++;
		}
	}
	return (i);
}

static char	*fill_tab(char *str, t_buf *buf)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = line_len(str, buf);
	copy = NULL;
	if (str == NULL)
		return (NULL);
	if ((copy = (char*)malloc(sizeof(copy) * (j + 1))) == NULL)
		return (NULL);
	while (i < j)
	{
		if (str >= buf->end)
			str = buf->start;
		copy[i++] = *str;
		str++;
	}
	copy[i] = '\0';
	return (copy);
}

char		**sv_split(t_buf *buf)
{
	int		j;
	char	*tmp;
	char	**tab;

	j = 0;
	if (buf == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(*tab) * (tab_lines(buf) + 1))) == NULL)
		return (NULL);
	tmp = buf->head;
	while (tmp != buf->tail)
	{
		if (*tmp != ' ' && (*tmp < 9 || *tmp > 11))
		{
			if ((tab[j++] = fill_tab(tmp, buf)) == NULL)
				break ;
			while (*tmp != ' ' && (*tmp < 9 || *tmp > 11) && tmp != buf->tail)
				tmp = (tmp >= buf->end) ? buf->start : tmp + 1;
		}
		else
			tmp++;
	}
	tab[j] = 0;
	return (tab);
}
