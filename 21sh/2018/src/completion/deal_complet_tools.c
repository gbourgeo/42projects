/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/11 16:47:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_lib.h"
#include "put.h"

char	*replace_tilde(const char *path, const char *replace)
{
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(path)
						+ ft_strlen(replace) + 1))))
		return (NULL);
	k = -1;
	while (path[++k] != '~')
		str[k] = path[k];
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	j = 1;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
}

int		search_to_tmp(char *buff)
{
	int		i;

	i = -1;
	if (!buff)
		return (0);
	while (buff[++i])
		if (buff[i] == '~' || buff[i] == '/')
			return (1);
		else if (buff[i] == '*')
			return (0);
	return (0);
}

int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return (1);
	return (0);
}

int		str_chrglob(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '*' || str[i] == '[' || str[i] == '?')
				&& (i == 0 || str[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

void	free_select(t_slct *select)
{
	if (!select)
		return ;
	if (select->next)
	{
		free_select(select->next);
		select->next = NULL;
	}
	if (select->down)
	{
		free_select(select->down);
		select->down = NULL;
	}
	if (select)
	{
		free(select);
		select = NULL;
	}
}
