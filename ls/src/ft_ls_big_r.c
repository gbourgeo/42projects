/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_big_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 00:58:08 by gilles            #+#    #+#             */
/*   Updated: 2015/04/14 12:29:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		*find_path(char *dir, char *name)
{
	char		*path;

	if (dir[ft_strlen(dir) - 1] == '/')
		path = ft_strjoin(dir, name);
	else
	{
		path = ft_strnew(ft_strlen(dir) + ft_strlen(name) + 2);
		if (path == NULL)
			return (NULL);
		path = ft_strcpy(path, dir);
		path = ft_strcat(path, "/");
		path = ft_strcat(path, name);
	}
	return (path);
}

void			ft_ls_big_r(t_dir *dir, t_opt *options)
{
	t_file		*tmp;
	char		*path;

	tmp = dir->file;
	while (!options->r && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == DT_DIR &&
			ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, "..") &&
			(*tmp->name != '.' || options->a))
		{
			path = find_path(dir->name, tmp->name);
			if (path == NULL)
				options->ret = -1;
			else
				options->ret = ft_get_dir(path, options);
			if (path)
				free(path);
		}
		tmp = !options->r ? tmp->prev : tmp->next;
	}
	options->nb_dir++;
}
